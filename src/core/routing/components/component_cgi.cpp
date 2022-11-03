#include "../../instance.hpp"
#include "../../../http/proto/cgi_msg.hpp"
#include "../../../http/handler/cgi_handler.hpp"

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


        class cgi_call {
            /*
             * Arguments given to us
             */
            routing_component_cgi&        cgi;
            webserv::http::cgi_message&   cgi_msg;
            cgi_fork_task&                task;

            /*
             * Our own locals
             */
            webserv::pal::fork::wait_set  ws;
            webserv::pal::fs::easypipe    cgi_in;
            webserv::pal::fs::easypipe    cgi_out;


        public:
            cgi_call(routing_component_cgi& _cgi, webserv::http::cgi_message& _cgi_msg, cgi_fork_task& _task) : cgi(_cgi), cgi_msg(_cgi_msg), task(_task) {

            }

            void setup_task_env() {
                for (webserv::http::fields::const_iterator it = cgi_msg.get_fields().begin(); it != cgi_msg.get_fields().end(); ++it)
                    task.add_env(it->first + "=" + it->second);
            }

            bool open_pipes() {
                if (!webserv::pal::fork::safe_pipe(&cgi_in.in, &cgi_in.out)) { // TODO: Is there a better notation instead of '&(pointer->int)' -> Yes, convert to references
                    return false;
                }
                if (!webserv::pal::fork::safe_pipe(&cgi_out.in, &cgi_out.out)) {
                    webserv::pal::fs::close(cgi_in.in);
                    webserv::pal::fs::close(cgi_in.out);
                    return false;
                }
                return true;
            }

            bool fork_task() {
                /*
                 * Add the file descriptors to be closed on fork()
                 */
                task.close_on_fork(cgi_in.in);
                task.close_on_fork(cgi_out.out);

                /*
                 * Communicate input and output to task
                 */
                task.io_to(cgi_in.out, cgi_out.in);
                cgi_msg.put_fields_into_task(task);

                /*
                 * Fork off!
                 */
                return task.perform(ws);
            }

            void pause_http_handler() { // TODO: Return a bool, let the error handling be done by the driver
                webserv::http::cgi_handler* handler = cgi.get_instance().pass_cgi(cgi_out.out);

                if (handler != NULL) {
                    handler->set_http_handler(&cgi.get_http_handler());
                    cgi.get_http_handler().fall_asleep();
                } else {
                    service_unavailable_503(cgi.get_response());  // TODO: Avoid the "return" in look_up: Call response->write() and give it a chance to write it out by itself
                    cgi.get_response().write(*(cgi.get_http_handler().get_connection()));
                }
            }

            void write_message() {
                webserv::util::ofdflow ofd(cgi_in.in);
                std::ostream o(&ofd);
                cgi_msg.write_on(o, cgi_out.out);
            }

            void close_pipes() {
                webserv::pal::fs::close(cgi_in.in);
                webserv::pal::fs::close(cgi_in.out);
                webserv::pal::fs::close(cgi_out.in);
            }
            
            void run() {
                setup_task_env();

                if (!(open_pipes() && fork_task())) {
                    internal_server_error_500(cgi.get_response());
                    cgi.get_response().write(*cgi.get_http_handler().get_connection());
                    return;
                }

                pause_http_handler();
                write_message();
                close_pipes();
            }
        };


        routing_component_cgi::routing_component_cgi(routing& routing) : routing_component(routing) {
            
        }

        void routing_component_cgi::handle_cgi(cgi_route& route) {
            std::string cgi_path = get_instance().get_fs().translate_cgi(route.get_file_target()).to_absolute_string();

            webserv::http::cgi_message cgi_msg(get_request(), get_instance(), cgi_path);

            webserv::pal::cpp::optional<std::string> executor = route.get_executor();
            cgi_fork_task task(executor.enabled() ? executor.value() : cgi_path);
            if (executor.enabled()) task.add_arg(cgi_path);

            cgi_call call(*this, cgi_msg, task);
            
            call.run();
        }

    }
}
