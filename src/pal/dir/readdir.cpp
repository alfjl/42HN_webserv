#include "../../defs.hpp"

namespace webserv {
    namespace pal {
        namespace dir {

            std::vector<std::string> read_directory(std::string path) {
                std::vector<std::string> files;
                DIR*                     dir_ptr;
                struct dirent*           entry;
                
                dir_ptr = opendir(path.c_str());
                if (dir_ptr != NULL) {
                    while ((entry = readdir(dir_ptr)) != NULL) {
                        if ((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)) {
                            files.push_back(entry->d_name);
                        }
                    }
                    closedir(dir_ptr);
                }

                return files;
            }

            bool is_directory(std::string entry) {
                struct stat s;

                if (stat(entry.c_str(), &s) == 0) {
                    return ((s.st_mode & S_IFDIR) != 0);
                }

                return false;
            }

        } // namespace dir
    } // namespace pal
} // namespace webserv
