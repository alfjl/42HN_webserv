#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Status: 200 OK\r\n");
    printf("Transfer-Encoding: chunked\r\n");
    printf("\r\n");
    unsigned int count = 0;
    int c = getchar();
    while (c >= 0) {
        count++;
        printf("1\r\n%c\r\n", (char) c);
        c = getchar();
    }
    printf("0\r\n\r\n");
    fprintf(stderr, "Done with %u bytes\n", count);
    return 0;
}
