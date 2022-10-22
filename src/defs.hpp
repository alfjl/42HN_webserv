#ifndef WEBSERV_DEFS_HPP
#define WEBSERV_DEFS_HPP

extern "C" {
// Standard C
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// Signals
#include <signal.h>
// Processes
#include <sys/wait.h>
// I/O & Files
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
// Networking
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <utility>

// #include "pal/cpp/nullptr.hpp"
#include "pal/cpp/shared_ptr.hpp"
#include "pal/net/socket.hpp"

namespace webserv {
}

#endif
