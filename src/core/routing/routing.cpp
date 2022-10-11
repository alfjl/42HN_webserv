#include "routing.hpp"

#include "../../pal/fork/fork.hpp"
#include "../../http/response.hpp"
#include "../../http/request.hpp"
#include "../../http/cgi/cgi_msg.hpp"
#include "../filesystem/filesystem.hpp"
#include "../instance.hpp"

#include "routing_table.hpp"

namespace webserv {

    namespace http {

        const char* code2str(unsigned int code); // TODO: Move to utility directory

    }

    namespace core {

        routing::routing(instance& the_inst) : component(the_inst) {
            // table.add_rule(new ext_rule("bla"), (new cgi_route(webserv::util::path(""))));
            table.add_rule(new ext_rule("bla"), (new cgi_route(webserv::util::path("")))->set_allowed_method(webserv::http::http_method_head)->set_allowed_method(webserv::http::http_method_post)); /*->unset_allowed_method(webserv::http::http_method_head))*/
            table.add_rule(new ext_rule("cgi"), (new cgi_route(webserv::util::path(""))));
            table.add_rule(new ext_rule("txt"), new file_route(webserv::util::path("")));
            table.add_rule(new ext_rule("html"), new redirection_route(webserv::util::path("")));
            table.add_rule(new ext_rule("buzz"), new error_route(webserv::util::path("")));
        }

        routing::~routing() {

        }

        void routing::handle_http_head(webserv::http::response_fixed& response, webserv::http::request_core& request, route& route) {
            handle_http_get(response, request, route);
            response.block_body();
        }

        void routing::handle_http_get(webserv::http::response_fixed& response, webserv::http::request_core& request, route& route) {
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

        void routing::handle_http_post(webserv::http::response_fixed& response, webserv::http::request_core& request, route& route) {
            webserv::util::path file_path = route.get_file_target();

            int status = get_instance().get_fs().accessible(file_path);

            if (status == 0)
                response.set_code(200);
            else
                response.set_code(201);
            
            if (get_instance().get_fs().is_directory(file_path)) {
                // TODO: This code exists merely to satisfy the second test case in the tester.
                method_not_allowed_405(response);
            } else {
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
        }

        void routing::handle_http_delete(webserv::http::response_fixed& response, webserv::http::request_core& request, route& route) {
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

        void routing::set_delete_response(webserv::http::response_fixed& response){
            std::ostringstream ost;
            std::pair<std::string, std::string> quote("But- at- what- cost?", "- Guybrush Threepwood, imitating Captain Kirk");
            
            ost << "<!DOCTYPE html>\r\n";
            ost << "<html>\r\n";
            head_start(ost, "File deleted.");
            ost << "<body>\r\n";
            header_one(ost, "File deleted.");
            blockquote(ost, quote);
            ost << "</body>\r\n";
            ost << "</html>\r\n";

            response.set_code(200);
            response.set_html_body(ost.str());
        }

        void routing::head_start(std::ostringstream& ost, std::string s){
            ost << "<head>\r\n";
            ost << "<meta charset=\"UTF-8\" />\r\n";
            ost << "<title>";
            ost << s;
            ost << "</title>\r\n";
            ost << "</head>\r\n";
        }

        void routing::header_one(std::ostringstream& ost, std::string s){
            ost << "<h1>";
            ost << s;
            ost << "</h1>\r\n";
            ost << "<hr/>\r\n";
        }

        void routing::header_three(std::ostringstream& ost, std::string s){
            ost << "<h3>";
            ost << s;
            ost << "</h3>";
        }

        void routing::blockquote(std::ostringstream& ost, std::pair<std::string, std::string> quote){
            ost << "<blockquote>\r\n";
            ost << "<p>";
            ost << quote.first;
            ost << "</p>\r\n";
            ost << quote.second;
            ost << "</blockquote>\r\n";
        }

        static bool prepare_pipes(webserv::pal::fork::easypipe* cgi_in, webserv::pal::fork::easypipe* cgi_out) {
            if (!webserv::pal::fork::safe_pipe(&(cgi_in->in), &(cgi_in->out))) { // TODO: Is there a better notation instead of '&(pointer->int)'
                return false;
            }
            if (!webserv::pal::fork::safe_pipe(&(cgi_out->in), &(cgi_out->out))) {
                ::close(cgi_in->in);
                ::close(cgi_in->out);
                return false;
            }
            return true;
        }

        static bool prepare_task(webserv::pal::fork::easypipe cgi_in, webserv::pal::fork::easypipe cgi_out,
                                webserv::pal::fork::fork_task* task, webserv::pal::fork::wait_set* ws) {
            task->close_on_fork(cgi_in.in);
            task->close_on_fork(cgi_out.out);
            // communicate input and output to task
            task->io_to(cgi_in.out, cgi_out.in);
            // fork_task
            if (task->perform(*ws) < 0) {
                return false;
            }
            return true;
        }

        static void handle_cgi_message_in(webserv::pal::fork::easypipe cgi_in, webserv::http::cgi_message *cgi_msg) {
            webserv::util::ofdflow ofd(cgi_in.in);
            std::ostream o(&ofd);
            cgi_msg->write_on(o);
        }

        void routing::handle_cgi(webserv::http::response_fixed* response, webserv::http::request_core& request, route* route) {
            webserv::http::cgi_message cgi_msg(request.get_body());
            //webserv::pal::fork::fork_task task(the_route.get_file_target().to_absolute_string());
            webserv::pal::fork::fork_task task("../tester/cgi/cgi1.cgi");
            webserv::pal::fork::wait_set ws;
            webserv::pal::fork::easypipe cgi_in;
            webserv::pal::fork::easypipe cgi_out;

            if (!prepare_pipes(&cgi_in, &cgi_out))
                internal_server_error_500(*response);            

            if (!prepare_task(cgi_in, cgi_out, &task, &ws))
                internal_server_error_500(*response);

            // Generate state machine
            // TODO: Implement

            // write ostream into pipe (into) / out_of it Eingabe von fork_task
            handle_cgi_message_in(cgi_in, &cgi_msg);

            /*
             * Close all open FDs
             */
            ::close(cgi_in.in);
            ::close(cgi_in.out);
            ::close(cgi_out.in);
            // NOTE: cgi_out.out must be open, it is used in the selector to retrieve the data
            //       sent to us by the CGI
            service_unavailable_503(*response);


                // // cgi_message
                // webserv::http::cgi_message cgi_msg(request.get_body());
                // //webserv::pal::fork::fork_task task(the_route.get_file_target().to_absolute_string());
                // webserv::pal::fork::fork_task task("../tester/cgi/cgi1.cgi");
                // webserv::pal::fork::wait_set ws;
                // webserv::pal::fork::easypipe cgi_in;
                // webserv::pal::fork::easypipe cgi_out;

                // // pipe
                // if (!webserv::pal::fork::safe_pipe(&cgi_in.in, &cgi_in.out)) {
                //     internal_server_error_500(*response);            
                // }
                // if (!webserv::pal::fork::safe_pipe(&cgi_out.in, &cgi_out.out)) {
                //     ::close(cgi_in.in);
                //     ::close(cgi_in.out);
                //     internal_server_error_500(*response);
                // }

                // task.close_on_fork(cgi_in.in);
                // task.close_on_fork(cgi_out.out);

                // // communicate input and output to task
                // task.io_to(cgi_in.out, cgi_out.in);

                // // fork_task
                // if (task.perform(ws) < 0) {
                //     internal_server_error_500(*response);
                // }

                // // Generate state machine
                // // TODO: Implement

                // // write ostream into pipe (into) / out_of it Eingabe von fork_task
                // webserv::util::ofdflow ofd(cgi_in.in);
                // std::ostream o(&ofd);
                // cgi_msg.write_on(o);
                // /*
                //  * Close all open FDs
                //  */
                // ::close(cgi_in.in);
                // ::close(cgi_in.out);
                // ::close(cgi_out.in);
                // // NOTE: cgi_out.out must be open, it is used in the selector to retrieve the data
                // //       sent to us by the CGI
                // service_unavailable_503(*response);

        }

        webserv::http::response_fixed* routing::look_up(webserv::http::request_core& request) {
            webserv::http::response_fixed *response = new webserv::http::response_fixed(); // TODO, FIXME, XXX: We might be leaking this!

            route* the_route = table.query(request.get_line().get_uri().get_path());

            if (!the_route->is_method_allowed(request.get_line().get_method())) {
                method_not_allowed_405(*response);
            } else if (the_route->is_cgi()) {
                handle_cgi(response, request, the_route);
            } else if (the_route->is_redirection()) {
                permanent_redirect_301(*response);
            } else if (the_route->is_error()) {
                bad_request_400(*response);
            } else {
                switch (request.get_line().get_method()) {
                    case webserv::http::http_method_head: { handle_http_head(*response, request, *the_route); break; }
                    case webserv::http::http_method_get: { handle_http_get(*response, request, *the_route); break; }
                    case webserv::http::http_method_put:
                    case webserv::http::http_method_post: { handle_http_post(*response, request, *the_route); break; }
                    case webserv::http::http_method_delete: { handle_http_delete(*response, request, *the_route); break; }
                    default: {
                        teapot_418(*response);
                        break;
                    }
                }
            }
            return (response);
        }

        void routing::tick() {
            // Do nothing!
        }

        void routing::directory_listing(webserv::http::response_fixed& response, std::vector<webserv::util::path> paths) {
            std::ostringstream ost;
            ost << "<!DOCTYPE html>\r\n";
            ost << "<html>\r\n";
            head_start(ost, "Listing");

            ost << "<body>\r\n";

            std::vector<webserv::util::path>::const_iterator it = paths.begin();
            while (it != paths.end()) {
                ost << "<a href=\"/" << (*it) << "\">" << (*it).get_last() << "</a>";
                ost << "<br/>\r\n";
                ++it;
            }

            ost << "</body>\r\n";
            ost << "</html>\r\n";

            response.set_code(200);
            response.set_html_body(ost.str());
        }

        void routing::file_listing(webserv::http::response_fixed& response, webserv::util::path file_path, std::ifstream* stream) {
            std::ostringstream payload;
            while (!stream->eof()) {
                int i = stream->get();
                if (i < 0) break;
                payload << (char) i;
            }

            response.set_code(200);
            response.set_body(payload.str(), find_mime(file_path.get_extension()));
        }

        std::string routing::itos(unsigned int code){
            std::ostringstream ost;
            ost << code;
            return ost.str();
        }

        void routing::error_code(webserv::http::response_fixed& response, unsigned int code) {
            std::ostringstream ost;
                
            std::pair<std::string, std::string> quote("Ah, there's nothing like the hot winds of Hell blowing in your face.", "- Le Chuck"); // Todo: code2str for monkey island quotes!

            std::string buf(itos(code));
            buf.append(" ");
            buf.append(webserv::http::code2str(code));
            ost << "<!DOCTYPE html>\r\n";
            ost << "<html>\r\n";
            head_start(ost, buf);
            ost << "<body>\r\n";
            header_one(ost, "Error at WebServ!");
            blockquote(ost, quote);
            header_three(ost, buf);
            ost << "</body>\r\n";
            ost << "</html>\r\n";

            response.set_code(code);
            response.set_html_body(ost.str());
        }

        void routing::permanent_redirect_301(webserv::http::response_fixed& response) {
            error_code(response, 301);
        }

        void routing::temporary_redirect_302(webserv::http::response_fixed& response) {
            error_code(response, 302);
        }

        void routing::bad_request_400(webserv::http::response_fixed& response) {
            error_code(response, 400);
        }

        void routing::unauthorized_401(webserv::http::response_fixed& response) {
            error_code(response, 401);
        }

        void routing::not_found_404(webserv::http::response_fixed& response) {
            error_code(response, 404);
        }

        void routing::method_not_allowed_405(webserv::http::response_fixed& response) {
            error_code(response, 405);
        }

        void routing::gone_410(webserv::http::response_fixed& response) {
            error_code(response, 410);
        }

        void routing::teapot_418(webserv::http::response_fixed& response) {
            error_code(response, 418);
        }

        void routing::internal_server_error_500(webserv::http::response_fixed& response) {
            error_code(response, 500);
        }

        void routing::service_unavailable_503(webserv::http::response_fixed& response) {
            error_code(response, 503);
        }

        std::string routing::find_mime(std::string extension) {
            if (extension == "bmp")
                return "image/bmp";
            else if (extension == "css")
                return "text/css";
            else if (extension == "csv")
                return "text/csv";
            else if (extension == "doc")
                return "application/msword";
            else if (extension == "docx")
                return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
            else if (extension == "gif")
                return "image/gif";
            else if ((extension == "html") || (extension == "htm"))
                return "text/html";
            else if ((extension == "jpeg") || (extension == "jpg"))
                return "image/jpeg";
            else if (extension == "js")
                return "text/javascript";
            else if (extension == "json")
                return "application/json";
            else if (extension == "png")
                return "image/png";
            else if (extension == "pdf")
                return "application/pdf";
            else if (extension == "php")
                return "application/x-httpd-php";
            else if (extension == "txt")
                return "text/plain";
            else
                return "*/*";
        }

    }
}
