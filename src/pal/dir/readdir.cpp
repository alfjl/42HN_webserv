#include <dirent.h>

#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace dir {

            std::vector<std::string> read_directory(const std::string& path) {
                std::vector<std::string> files;
                DIR*                     dir_ptr;
                struct dirent*           entry;
                
                dir_ptr = opendir(path.c_str());
                // if (!dir_ptr) {
                //     // throw exception? Or how to handle the error?
                // }
                if (dir_ptr) {
                    while ((entry = readdir(dir_ptr)) != NULL) {
                        if (!(entry->d_name == ".") && !(entry->d_name == "..")) {
                            files.push_back(entry->d_name);
                        }
                    }
                }

                closedir(dir_ptr);

                return files;
            }


        } // namespace dir
    } // namespace pal
} // namespace webserv
