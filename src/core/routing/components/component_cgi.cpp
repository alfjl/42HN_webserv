#include "../../instance.hpp"
#include "../../../http/proto/cgi_msg.hpp"
#include "../../../http/handler/cgi_handler.hpp"

#include "../cgi/cgi.hpp"
#include "../pages/pages.hpp"

#include "component_cgi.hpp"


namespace webserv {
    namespace core {
        class cgi_fork_task : public webserv::pal::fork::fork_task {
        public:
            cgi_fork_task(std::string executable) : fork_task(executable) {

            }

        protected:
            void on_failure() {
                webserv::http::response_fixed  response;
                response.enable_cgi_mode();
                internal_server_error_500(response);
                response.write(std::cout);
                std::flush(std::cout);
            }
        };

        /*
         * Wraps the fork() and execve() calls,
         * and takes care of closing the correct file descriptors
         */
        static bool run_task(webserv::pal::fs::easypipe      cgi_in,
                             webserv::pal::fs::easypipe      cgi_out,
                             webserv::pal::fork::fork_task&  task,
                             webserv::pal::fork::wait_set&   ws,
                             webserv::http::cgi_message&     cgi) {
            /*
             * Add the file descriptors to be closed on fork()
             */
            task.close_on_fork(cgi_in.in);
            task.close_on_fork(cgi_out.out);

            /*
             * Communicate input and output to task
             */
            task.io_to(cgi_in.out, cgi_out.in);
            cgi.put_fields_into_task(task);

            /*
             * Fork off!
             */
            return task.perform(ws);
        }

        /*
         * Opens 2 pipes. One for the input into the cgi,
         * and one for the output of the cgi 
         */
        static bool prepare_pipes(webserv::pal::fs::easypipe* cgi_in, webserv::pal::fs::easypipe* cgi_out) {
            if (!webserv::pal::fork::safe_pipe(&(cgi_in->in), &(cgi_in->out))) { // TODO: Is there a better notation instead of '&(pointer->int)'
                return false;
            }
            if (!webserv::pal::fork::safe_pipe(&(cgi_out->in), &(cgi_out->out))) {
                webserv::pal::fs::close(cgi_in->in);
                webserv::pal::fs::close(cgi_in->out);
                return false;
            }
            return true;
        }

        static void put_http_handler_to_sleep(routing_component_cgi& cgi, webserv::pal::fs::easypipe& cgi_out) {
            webserv::http::cgi_handler* handler = cgi.get_instance().pass_cgi(cgi_out.out);

            if (handler != NULL) {
                handler->set_http_handler(&cgi.get_http_handler());
                cgi.get_http_handler().fall_asleep();
            } else {
                service_unavailable_503(cgi.get_response());  // TODO: Avoid the "return" in look_up: Call response->write() and give it a chance to write it out by itself
                cgi.get_response().write(*(cgi.get_http_handler().get_connection()));
            }
        }

        /*
         * Attaches the input of cgi_in to an ostream,
         * and writes the cgi message_body to this stream 
         */
        static void handle_cgi_message_in(webserv::pal::fs::easypipe cgi_in, webserv::pal::fs::easypipe cgi_out, webserv::http::cgi_message& cgi_msg) {
            webserv::util::ofdflow ofd(cgi_in.in);
            std::ostream o(&ofd);
            cgi_msg.write_on(o, cgi_out.out);
        }

        static void handle_cgi_pipes(webserv::core::routing_component_cgi& cgi, webserv::core::cgi_fork_task& task, webserv::http::cgi_message& cgi_msg) {
            webserv::pal::fork::wait_set  ws;
            webserv::pal::fs::easypipe    cgi_in;
            webserv::pal::fs::easypipe    cgi_out;

            /*
             * Open 2 pipes. One for input to cgi and one for output of cgi.
             * Then run the task.
             */
            if (!(prepare_pipes(&cgi_in, &cgi_out) && run_task(cgi_in, cgi_out, task, ws, cgi_msg))) {
                internal_server_error_500(cgi.get_response());
                cgi.get_response().write(*cgi.get_http_handler().get_connection());
                return;
            }

            /*
             * Since the CGI must run, we put the HTTP handler to sleep. 
             * It will be woken up by the terminating CGI handler.
             */
            put_http_handler_to_sleep(cgi, cgi_out);

            /*
             * Attach ostream to pipe (cgi_in.in) / cgi_in.out stays input of fork_task.
             */
            handle_cgi_message_in(cgi_in, cgi_out, cgi_msg);

            /*
             * Close all open FDs.
             */
            webserv::pal::fs::close(cgi_in.in);
            webserv::pal::fs::close(cgi_in.out);
            webserv::pal::fs::close(cgi_out.in);
        }


        routing_component_cgi::routing_component_cgi(routing& routing) : routing_component(routing) {
            
        }

        void routing_component_cgi::handle_cgi(cgi_route& route) {
            std::string cgi_path = get_instance().get_fs().translate_cgi(route.get_file_target()).to_absolute_string();

            webserv::http::cgi_message cgi_msg(get_request(), get_instance(), cgi_path);

            webserv::pal::cpp::optional<std::string> executor = route.get_executor();
            cgi_fork_task task(executor.enabled() ? executor.value() : cgi_path);
            if (executor.enabled()) task.add_arg(cgi_path);

            for (webserv::http::fields::const_iterator it = cgi_msg.get_fields().begin(); it != cgi_msg.get_fields().end(); ++it)
                task.add_env(it->first + "=" + it->second);

            handle_cgi_pipes(*this, task, cgi_msg);
        }

    }
}
