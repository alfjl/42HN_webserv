#include "oflow.hpp"


namespace webserv {
    namespace util {

        oflow::oflow(connection& _con) : con(_con) {

        }

        oflow::int_type oflow::overflow(int_type c) {
            if (c == traits_type::eof())
                con.close();
            else {
                con.get_output().push_char(traits_type::to_char_type(c));
            }
        }

    }
}