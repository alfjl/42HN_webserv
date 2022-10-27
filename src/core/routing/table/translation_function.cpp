#include "translation_function.hpp"

#include "route.hpp"

#include "../../../util/path.hpp"

namespace webserv {
    namespace core {

        translation_function::translation_function() {

        }

        translation_function::~translation_function() {

        }


        bool zero_translation_function::convert(match_info& meta) {
            meta.wildcard_path = webserv::util::path();
            return true;
        }


        bool relative_translation_function::convert(match_info& meta) {
            (void) meta;
            return true;
        }


    }
}
