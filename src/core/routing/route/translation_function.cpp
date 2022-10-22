#include "translation_function.hpp"

#include "route.hpp"

#include "../../../util/path.hpp"

namespace webserv {
    namespace core {

        basic_translation_function::basic_translation_function() {

        }

        basic_translation_function::~basic_translation_function() {

        }


        bool zero_translation_function::convert(match_info& meta) {
            return true;
        }


        bool relative_translation_function::convert(match_info& meta) {
            meta.wildcard_path = webserv::util::path();
            return true;
        }


    }
}
