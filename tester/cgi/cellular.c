#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 220
#define HEIGHT 800

typedef bool (*rule_t)(int c);

int adjust(int n, int min, int max) {
    while (n < min) n += (max - min);
    while (n >= max) n -= (max - min);
    return n;
}

int count(bool* a, int n, int i) {
    int c = 0;

    for (int d = -2; d <= 2; d++)
        c += a[adjust(i + d, 0, n)];
    
    return c;
}

void build(bool* a, bool* b, int n, int i, unsigned char rule) {
    unsigned int conf = 0;
    for (int d = -1; d <= 1; d++)
        conf = (conf << 1) | a[adjust(i + d, 0, n)];
    b[i] = (rule & (1 << conf)) != 0;
}

void gen(int n, unsigned char rule) {
    bool a0[n];
    bool a1[n];

    for (int i = 0; i < n; i++) {
        a0[i] = 0;
        a1[i] = rand() % 2;
    }

    bool* p1 = a0;
    bool* p2 = a1;

    int i = 0;
    bool changes = true;
    while (i < HEIGHT && changes) {
        changes = false;
        printf("%X\r\n", n+2);
        for (int i = 0; i < n; i++) {
            putchar(p1[i] ? '#' : '.');
            build(p2, p1, n, i, rule);
            changes |= p1[i] != p2[i];
        }
        putchar('\r');
        putchar('\n');
        printf("\r\n");
        fflush(stdout);
        usleep(10000);

        bool* tmp = p1;
        p1 = p2;
        p2 = tmp;
        ++i; // 
    }
}

bool rule_2_4(int count) {
    return (count == 2) || (count == 4);
}

bool rule_1_5(int count) {
    return (count == 1) || (count == 5);
}

bool rule_3_4(int count) {
    return (count == 3) || (count == 4);
}

int main(int argc, char** argv) {
    printf("Status: 200 OK\r\n");
    printf("Connection: close\r\n");
    printf("Content-Type: text/plain\r\n");
    printf("Transfer-Encoding: chunked\r\n");
    printf("\r\n");
    srand(time(NULL));
    unsigned char rule = (unsigned char) (rand() % 255);
    printf("5\r\n%03u\r\n\r\n", (unsigned int) rule);
    gen(WIDTH, rule);
    printf("0\r\n\r\n");
    fflush(stdout);
    return 1;
}
