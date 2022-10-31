#include "routing.hpp"

#include "pages/pages.hpp"
#include "cgi/cgi.hpp"
#include "../../pal/fork/fork.hpp"
#include "../../pal/fs/fs.hpp"
#include "../../http/handler/http_handler.hpp"
#include "../../http/handler/cgi_handler.hpp"
#include "../../http/proto/cgi_msg.hpp"
#include "../../http/proto/response.hpp"
#include "../../http/proto/request.hpp"
#include "../filesystem/filesystem.hpp"
#include "../instance.hpp"

#include "table/routing_table.hpp"

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

        routing::routing(instance& the_inst) : component(the_inst) {

        }

        routing::~routing() {

        }

        routing_table& routing::get_table() { return table; }

        void routing::error_page(webserv::http::response_fixed& response, webserv::http::request& request, webserv::http::http_handler* the_http_handler, unsigned int code) {
            // TODO, FIXME, XXX: Watch out for recursion!
            route* the_route = table.query_error_page(code);
            if (the_route == NULL) {
                error_code(response, code);
                response.write(*the_http_handler->get_connection());
            } else {
                follow_route(response, request, the_route, the_http_handler);
            }
        }

        void routing::follow_route(webserv::http::response_fixed& response, webserv::http::request& request, route* the_route, webserv::http::http_handler* the_http_handler) {
            int code;

            if (!the_route->is_method_allowed(request.get_line().get_method())) {
                delete the_route;
                error_page(response, request, the_http_handler, 405);
                return;
            } else if (the_route->is_cgi()) { // TODO: Does this always return false?
                handle_cgi(response, request, (cgi_route*) the_route, the_http_handler);
                delete the_route;
                return; // Invisible yield
            } else if (the_route->is_redirection()) {
                temporary_redirect_302(response, the_route->get_file_target());
            } else if (the_route->is_permanent_redirection()) {
                permanent_redirect_301(response, the_route->get_file_target());
            } else if (the_route->is_error(code)) {
                delete the_route;
                error_page(response, request, the_http_handler, code);
                return;
            } else if (the_route->get_max_body().enabled() && request.get_body().size() > the_route->get_max_body().value()) {
                error_page(response, request, the_http_handler, 413);
            } else {
                switch (request.get_line().get_method()) {
                    case webserv::http::http_method_head: { handle_http_head(response, request, *the_route); break; }
                    case webserv::http::http_method_get: { handle_http_get(response, request, *the_route); break; }
                    case webserv::http::http_method_put:
                    case webserv::http::http_method_post: { handle_http_post(response, request, *the_route); break; }
                    case webserv::http::http_method_delete: { handle_http_delete(response, request, *the_route); break; }
                    default: {
                        teapot_418(response);
                        break;
                    }
                }
            }

            delete the_route;
            response.write(*the_http_handler->get_connection());
        }

        void routing::handle_http_head(webserv::http::response_fixed& response, webserv::http::request& request, route& route) {
            handle_http_get(response, request, route);
            response.block_body();
        }

        void routing::handle_http_get(webserv::http::response_fixed& response, webserv::http::request& request, route& route) {
            (void) request;

            webserv::util::path file_path = route.get_file_target();
            std::ifstream stream;

            if (get_instance().get_fs().is_directory(file_path)) {
                directory_listing(response, get_instance().get_fs().read_absolute_path(file_path));
            } else if (get_instance().get_fs().open(file_path, stream)) {
                file_listing(response, file_path, &stream);
            } else {
                not_found_404(response);
            }
        }

        void routing::set_response_code(webserv::util::path file_path, webserv::http::response_fixed& response) {
            int status = get_instance().get_fs().accessible(file_path);

            if (status == 0)
                response.set_code(200);
            else
                response.set_code(201);
        }

        void routing::get_request_body(webserv::util::path file_path, webserv::http::response_fixed& response, webserv::http::request& request) {
             std::ofstream outfile;

            if (get_instance().get_fs().write(file_path/*, std::ios_base::out | std::ios_base::trunc)*/, outfile)) { // TODO: Add flags to write()
                outfile << request.get_body().c_str();

                if (!outfile.good())
                    internal_server_error_500(response); // if file couldn't be opened/constructed TODO: check against nginx/tester
                outfile.close();

                response.set_html_body(request.get_body());
            } else {
                internal_server_error_500(response); // if file couldn't be opened/constructed TODO: check against nginx/tester
            }
        }

        void routing::handle_http_post(webserv::http::response_fixed& response, webserv::http::request& request, route& route) {
            webserv::util::path file_path = route.get_file_target();

            set_response_code(file_path, response);
            
            if (get_instance().get_fs().is_directory(file_path)) {
                // TODO: This code exists merely to satisfy the second test case in the tester.
                method_not_allowed_405(response);
            } else {
                get_request_body(file_path, response, request);
            }
        }

        void routing::handle_http_delete(webserv::http::response_fixed& response, webserv::http::request& request, route& route) {
            (void) request;
            
            webserv::util::path file_path = route.get_file_target();
            std::ifstream stream;

            if (get_instance().get_fs().is_directory(file_path)) {  // TODO: Check against nginx if this is correct behaviour!! Nginx: Allow to delete directories? Allow to recursively delete directories?
                if (!get_instance().get_fs().del(file_path))
                    unauthorized_401(response);
            } else if ((get_instance().get_fs().del(file_path))) {
                set_delete_response(response);
            } else {
                not_found_404(response);
            }
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

        /*
         * Wraps the fork() and execve() calls,
         * and takes care of closing the correct file descriptors
         */
        static bool prepare_task(webserv::pal::fs::easypipe  cgi_in,
                                webserv::pal::fs::easypipe   cgi_out,
                                webserv::pal::fork::fork_task* task,
                                webserv::pal::fork::wait_set*  ws,
                                webserv::http::cgi_message& cgi) {
            task->close_on_fork(cgi_in.in);
            task->close_on_fork(cgi_out.out);
            // communicate input and output to task
            task->io_to(cgi_in.out, cgi_out.in);
            cgi.put_fields_into_task(*task);
            // fork_task
            return task->perform(*ws);
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

        void routing::put_http_handler_to_sleep(webserv::http::response_fixed& response, webserv::http::http_handler* the_http_handler, webserv::pal::fs::easypipe& cgi_out) {
            webserv::http::cgi_handler* handler = get_instance().pass_cgi(cgi_out.out);

            if (handler != NULL) {
                // response.block_all();  // TODO: Not needed anymore
                handler->set_http_handler(the_http_handler);
                the_http_handler->fall_asleep();
            } else {
                service_unavailable_503(response);  // TODO: Avoid the "return" in look_up: Call response->write() and give it a chance to write it out by itself
                // ghettofix
                response.write(*the_http_handler->get_connection());
            }
        }



        // void handle_cgi_pipes(webserv::http::response_fixed& response, webserv::http::http_handler* the_http_handler, webserv::http::cgi_message cgi_msg) {
        //     webserv::pal::fork::wait_set ws;
        //     webserv::pal::fs::easypipe cgi_in;
        //     webserv::pal::fs::easypipe cgi_out;

        //     /*
        //      * Open 2 pipes. One for input to cgi and one for output of cgi
        //      */
        //     if (!prepare_pipes(&cgi_in, &cgi_out))
        //         internal_server_error_500(response);            

        //     /*
        //      *
        //      */
        //     if (!prepare_task(cgi_in, cgi_out, &task, &ws, cgi_msg)) {
        //         internal_server_error_500(response);
        //         response.write(*the_http_handler->get_connection());
        //         return;
        //     }

        //     put_http_handler_to_sleep(response, the_http_handler, cgi_out);

        //     /*
        //      * Attach ostream to pipe (cgi_in.in) / cgi_in.out stays input of fork_task
        //      */
        //     handle_cgi_message_in(cgi_in, cgi_out, cgi_msg);

        //     /*
        //      * Close all open FDs
        //      */
        //     webserv::pal::fs::close(cgi_in.in);
        //     webserv::pal::fs::close(cgi_in.out);
        //     webserv::pal::fs::close(cgi_out.in);
        // }

        /*
         * Hands the request body over to the cgi and accepts the cgi's output as the response body 
         */
        void routing::handle_cgi(webserv::http::response_fixed& response, webserv::http::request& request, cgi_route* the_route, webserv::http::http_handler* the_http_handler) {
            //  std::string cgi_path = get_instance().get_fs().translate_cgi(the_route->get_file_target()).to_absolute_string();

            // webserv::http::cgi_message cgi_msg(request, get_instance(), cgi_path);

            // // TODO: Clean up this code!
            // webserv::pal::cpp::optional<std::string> executor = the_route->get_executor();
            // cgi_fork_task task(executor.enabled() ? executor.value() : cgi_path);
            // if (executor.enabled()) task.add_arg(cgi_path);
            

            // for (webserv::http::fields::const_iterator it = cgi_msg.get_fields().begin(); it != cgi_msg.get_fields().end(); ++it)
            //     task.add_env(it->first + "=" + it->second);

            // // handle_cgi_pipes(response, the_http_handler, cgi_msg);

            // TRY to clean this code up... didn't worked ^^
            
            std::string cgi_path = get_instance().get_fs().translate_cgi(the_route->get_file_target()).to_absolute_string();

            webserv::http::cgi_message cgi_msg(request, get_instance(), cgi_path);

            // TODO: Clean up this code!
            webserv::pal::cpp::optional<std::string> executor = the_route->get_executor();
            cgi_fork_task task(executor.enabled() ? executor.value() : cgi_path);
            if (executor.enabled()) task.add_arg(cgi_path);
            
            webserv::pal::fork::wait_set ws;
            webserv::pal::fs::easypipe cgi_in;
            webserv::pal::fs::easypipe cgi_out;

            for (webserv::http::fields::const_iterator it = cgi_msg.get_fields().begin(); it != cgi_msg.get_fields().end(); ++it)
                task.add_env(it->first + "=" + it->second);

            /*
             * Open 2 pipes. One for input to cgi and one for output of cgi
             */
            if (!prepare_pipes(&cgi_in, &cgi_out))
                internal_server_error_500(response);            

            /*
             *
             */
            if (!prepare_task(cgi_in, cgi_out, &task, &ws, cgi_msg)) {
                internal_server_error_500(response);
                response.write(*the_http_handler->get_connection());
                return;
            }

            put_http_handler_to_sleep(response, the_http_handler, cgi_out);

            /*
             * Attach ostream to pipe (cgi_in.in) / cgi_in.out stays input of fork_task
             */
            handle_cgi_message_in(cgi_in, cgi_out, cgi_msg);

            /*
             * Close all open FDs
             */
            webserv::pal::fs::close(cgi_in.in);
            webserv::pal::fs::close(cgi_in.out);
            webserv::pal::fs::close(cgi_out.in);
        }

        void routing::look_up(webserv::http::request& request, webserv::http::http_handler* the_http_handler) {
            webserv::http::response_fixed response;

            route* the_route = table.query(request.get_line().get_uri().get_path());

            follow_route(response, request, the_route, the_http_handler);
        }

        void routing::tick() {
            // Do nothing!
        }

    }
}
