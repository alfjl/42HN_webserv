#include <unistd.h>

int main(void) {
    char buffer[1024];
    
    while (1) {
        size_t amount = read(0, buffer, sizeof(buffer));
        if (amount <= 0) break;
        write(1, buffer, amount);
    }

    write(2, "Helloe\n", 7);

    return 0;
}
