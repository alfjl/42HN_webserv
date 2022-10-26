#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 220
#define HEIGHT 80

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

void build(bool* a, bool* b, int n, int i, rule_t rule) {
    b[i] = rule(count(a, n, i));
}

void gen(int n, rule_t rule) {
    bool a0[n];
    bool a1[n];

    for (int i = 0; i < n; i++) {
        a0[i] = 0;
        a1[i] = rand() % 2;
    }

    bool* p1 = a0;
    bool* p2 = a1;

    int i = 0;
    while (i < HEIGHT) {
        printf("%x\r\n", WIDTH+2);
        for (int i = 0; i < n; i++) {
            putchar(p1[i] ? '#' : '.');
            build(p2, p1, n, i, rule);
        }
        putchar('\r');
        putchar('\n');
        printf("\r\n");
        //usleep(10000);

        bool* tmp = p1;
        p1 = p2;
        p2 = tmp;
        ++i; // 
    }
}

bool rule_2_4(int count) {
    return (count == 2) || (count == 4);
}

int main(int argc, char** argv) {
    printf("Status: 200 OK\r\n");
    //printf("Content-Length: %u\r\n", HEIGHT * (WIDTH + 2));
    printf("Transfer-Encoding: chunked\r\n");
    printf("\r\n");
    srand(time(NULL));
    gen(WIDTH, rule_2_4);
    printf("0\r\n");
    return 1;
}