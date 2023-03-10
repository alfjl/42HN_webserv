#include "../../instance.hpp"
#include "../../../http/proto/cgi_msg.hpp"
#include "../../../http/handler/cgi_handler.hpp"
#include "../../../http/handler/writing_handler.hpp"

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

            void fail_with_error(unsigned int code) {
                cgi.get_parent().get_component_pages().error_page(code);
                cgi.get_response().write(*(cgi.get_http_handler().get_connection()));
            }

            bool open_pipes() {
                if (!webserv::pal::fork::safe_pipe(&cgi_in.in, &cgi_in.out)) {
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

            bool pause_http_handler() {
                webserv::http::cgi_handler* handler = cgi.get_instance().pass_cgi(cgi_out.out);

                if (handler != NULL) {
                    handler->set_http_handler(&cgi.get_http_handler());
                    cgi.get_http_handler().fall_asleep();
                    return true;
                }
                return false;
            }

            void write_message() {
                cgi.get_instance().pass_writing(cgi_msg.get_message_body(), cgi_in.in);
            }

            void close_pipes() {
                // webserv::pal::fs::close(cgi_in.in);
                webserv::pal::fs::close(cgi_in.out);
                webserv::pal::fs::close(cgi_out.in);
            }
            
            void run() {
                if (!(open_pipes() && fork_task())) {
                    fail_with_error(500);
                    return;
                }

                if (!pause_http_handler()) {
                    fail_with_error(503);
                    return;
                }

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
