#include "oflow.hpp"

#include "../pal/fs/fs.hpp"
#include "connection.hpp"

namespace webserv {
    namespace util {

        oflow::oflow(connection& _con) : con(_con) {

        }

        std::streamsize oflow::xsputn(const char * s, std::streamsize n)
        {
            for (std::streamsize i = 0; i < n; i++) {
                con.get_output().push_char(s[i]);
            }
            return n;
        }

        oflow::int_type oflow::overflow(int_type c) {
            if (c == traits_type::eof())
                con.close();
            else {
                char_type ch = traits_type::to_char_type(c);
                return xsputn(&ch, 1) == 1 ? c : traits_type::eof();
            }
            return c;
        }


        ofdflow::ofdflow(int fd) : _fd(fd) {

        }

        std::streamsize ofdflow::xsputn(const char * s, std::streamsize n)
        {
            // TODO: ERROR HANDLING
            write(_fd, s, n);
            return n;
        }

        oflow::int_type ofdflow::overflow(int_type c) {
            if (c == traits_type::eof())
                webserv::pal::fs::close(_fd);
            else {
                char_type ch = traits_type::to_char_type(c);
                return xsputn(&ch, 1) == 1 ? c : traits_type::eof();
            }
            return c;
        }
    }
}