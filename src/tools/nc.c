/*
 * This tool is horribly written, and not part of the webserv itself.
 * Please ignore it :D
 *                                         - nijakow
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/select.h>

void try_this(int fd) {
    fd_set set;
    struct timeval  tv;

    FD_ZERO(&set);
    FD_SET(fd, &set);
    FD_SET(STDIN_FILENO, &set);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    select(fd + 1, &set, NULL, NULL, &tv);
    if (FD_ISSET(fd, &set)) {
        char buffer[1024];
        size_t amount = read(fd, buffer, sizeof(buffer));
        if (amount <= 0) exit(0);
        write(STDOUT_FILENO, buffer, amount);
    }
    if (FD_ISSET(STDIN_FILENO, &set)) {
        char buffer[1024];
        size_t amount = read(STDIN_FILENO, buffer, sizeof(buffer));
        bool was_r = false;
        for (size_t i = 0; i < amount; i++) {
            if (!was_r && buffer[i] == '\n') {
                was_r = false;
                char c = '\r';
                write(fd, &c, 1);
            } else if (buffer[i] == '\r') {
                was_r = true;
            } else {
                was_r = false;
            }
            write(fd, &buffer[i], 1);
        }
    }
}

void cat_all(int from, int to) {
    char buffer[1024];

    size_t amount;

    while ((amount = read(from, buffer, sizeof(buffer))) > 0) {
        try_this(to);
        bool was_r = false;
        for (size_t i = 0; i < amount; i++) {
            if (!was_r && buffer[i] == '\n') {
                was_r = false;
                char c = '\r';
                write(to, &c, 1);
            } else if (buffer[i] == '\r') {
                was_r = true;
            } else {
                was_r = false;
            }
            write(to, &buffer[i], 1);
        }
    }
    printf("Over and out\n");
}

int main(int argc, char* argv[]) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(4242);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    connect(sock, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr));
    // cat_all(STDIN_FILENO, STDOUT_FILENO);
    // cat_all(STDIN_FILENO, sock);
    while (1)
        try_this(sock);
    return 0;
}
