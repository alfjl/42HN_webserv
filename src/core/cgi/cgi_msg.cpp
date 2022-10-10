#include "cgi_msg.hpp"

#include "../../pal/fork/fork.hpp"

namespace webserv {
    namespace core {

    cgi_message::cgi_message(const std::string& message) : _message_body(message) {

    }

    cgi_message::~cgi_message() {

    }


;

        ;



    }


    void cgi_message::write_on(webserv::http::response_fixed& response, webserv::http::request_core& request, route& the_route) {
        std::ostream o << _message_body.c_str();
        int pipe[2], nbytes;
    
        if (safe_pipe(pipe[0], pipe[1])) {

            webserv::pal::fork::fork_task task(the_route.get_file_target().to_absolute_string());
            webserv::pal::fork::wait_set ws;

            task.input_to(pipe[0]);
            task.output_to(pipe[1]);

            if ((task.perform(ws)) > 0) {
                task.output_to.disable();

                close(pipe[0]);
                write(pipe[1], request.get_body(), sizeof(request.get_body()));
        
                ws.wait_for_all();
            } else {
                task.input_to.disable();
                
                close(pipe[1]);

                while ((nbytes = read(pipe[0], response.set_body(), ?MSGSIZE?)) > 0)
                if (nbytes != 0)
                    exit(2);
        
        }
    }
}