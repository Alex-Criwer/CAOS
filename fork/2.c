#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum program {
    ERROR = -1,
    SIZE = 4096,
    OFFSET = 10
};

int main(const int argc, const char *argv[]) {
    char buffer[SIZE];
    char program[SIZE + OFFSET];
    fgets(buffer, SIZE, stdin);
    if ('\n' == buffer[strlen(buffer) - 1]) {
        buffer[strlen(buffer) - 1] = '\0';
    }

    if (snprintf(program, SIZE + OFFSET, "print (%s)", buffer) > SIZE + OFFSET) {
        return ERROR;
    }
    execlp("python", "python3", "-c", program, NULL);
    perror("smth after exec it's error");
    return 0;
}
