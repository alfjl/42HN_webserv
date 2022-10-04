#include "env.hpp"

	// 1. im Pal wrapper um getenv() returns std::string
    // std::string pal::env::getenv(std::string)
    // - NULL-check
    // - .c_str()
    // std::string pal::env::pwd()
    //   return pal::env::getenv("PWD");
    // webserv::util::path filesystem::pwd()
    //    return path(pal::env::pwd())
    // in add_anchor()
    //    "/" + (pwd().cd("../www") + path).get_addr_s()
    // in www folder alle nötigen files reinpacken aus dem tester


namespace webserv {
    namespace pal {
        namespace env {

           std::string getenv(std::string var) {
				char *ptr = std::getenv(var.c_str());
				
				if (ptr == NULL)
					return ("");
				return (std::string(ptr));
		   }

		   webserv::util::path pwd() {
				return (webserv::util::path(getenv("PWD")));
		   }

        }
    }
}
