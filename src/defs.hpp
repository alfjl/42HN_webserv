#ifndef WEBSERV_DEFS_HPP
#define WEBSERV_DEFS_HPP

extern "C" {

#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>

}

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <utility>

#include "pal/cpp/nullptr.hpp"
#include "pal/net/socket.hpp"

namespace webserv {

}

#endif
