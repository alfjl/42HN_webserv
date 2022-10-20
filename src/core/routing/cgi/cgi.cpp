#include "cgi.hpp"

#include "../pages/pages.hpp"
#include "../../../http/response.hpp"

namespace webserv {
    namespace core {

        void head_start(std::ostringstream& ost, std::string s){
            ost << "<head>\r\n";
            ost << "<meta charset=\"UTF-8\" />\r\n";
            ost << "<title>";
            ost << s;
            ost << "</title>\r\n";
            ost << "</head>\r\n";
        }

        void header_one(std::ostringstream& ost, std::string s){
            ost << "<h1>";
            ost << s;
            ost << "</h1>\r\n";
            ost << "<hr/>\r\n";
        }

        void header_three(std::ostringstream& ost, std::string s){
            ost << "<h3>";
            ost << s;
            ost << "</h3>";
        }

        void blockquote(std::ostringstream& ost, std::pair<std::string, std::string> quote){
            ost << "<blockquote>\r\n";
            ost << "<p>";
            ost << quote.first;
            ost << "</p>\r\n";
            ost << quote.second;
            ost << "</blockquote>\r\n";
        }

        void set_delete_response(webserv::http::response_fixed& response){
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

        void print_path(std::ostringstream& ost, std::vector<webserv::util::path> paths) {
            std::vector<webserv::util::path>::const_iterator it = paths.begin();
            while (it != paths.end()) {
                ost << "<a href=\"/" << (*it) << "\">" << (*it).get_last() << "</a>";
                ost << "<br/>\r\n";
                ++it;
            }
        }

        void directory_listing(webserv::http::response_fixed& response, std::vector<webserv::util::path> paths) {
            std::ostringstream ost;
            ost << "<!DOCTYPE html>\r\n";
            ost << "<html>\r\n";
            head_start(ost, "Listing");

            ost << "<body>\r\n";
            print_path(ost, paths); // refactored
            ost << "</body>\r\n";
            ost << "</html>\r\n";

            response.set_code(200);
            response.set_html_body(ost.str());
        }

        void file_listing(webserv::http::response_fixed& response, webserv::util::path file_path, std::ifstream* stream) {
            std::ostringstream payload;
            while (!stream->eof()) {
                int i = stream->get();
                if (i < 0) break;
                payload << (char) i;
            }

            response.set_code(200);
            response.set_body(payload.str(), find_mime(file_path.get_extension()));
        }

	}
}
