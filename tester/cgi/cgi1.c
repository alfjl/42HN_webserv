#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp) {
    char buffer[1024];
    
    write(1, "This is the CGI\n", 16);

	for (char** ptr = envp; *ptr != NULL; ptr++) {
		printf("%s\n", *ptr);
	}

    while (1) {
        size_t amount = read(0, buffer, sizeof(buffer));
        if (amount <= 0) break;
        write(1, buffer, amount);
    }

    write(2, "Helloe\n", 7);

    return 0;
}
