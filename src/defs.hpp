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
#include <arpa/inet.h>
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
#include <algorithm>

#include "pal/net/socket.hpp"

#ifndef WEBSERV_NOEXCEPT
#ifdef _NOEXCEPT
# define WEBSERV_NOEXCEPT _NOEXCEPT
#else
# define WEBSERV_NOEXCEPT throw()
#endif
#endif

namespace webserv {
}

#endif
