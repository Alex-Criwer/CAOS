#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


enum program {
    ERROR = -1,
    SIZE = 4096,
    CHILD = 0,
    FIRST_PROCESS = 1,
    TRUE = 1
};

int main(const int argc, const char *argv[]) {
    int counter = 0; // to count number of processes
    char buffer[SIZE];
    memset(buffer, 0, SIZE);
    pid_t process_id;

    while (TRUE) {
        int read = scanf("%s", buffer);
        if (EOF == read) {
            return 0;
        }
        process_id = fork();
        ++counter;

        if (ERROR == process_id) {
            perror("invalid fork");
            return ERROR;
        }

        if (CHILD != process_id) { // parent
            int status;
            waitpid(process_id, &status, 0); // завершение дочернего
            if (FIRST_PROCESS == counter) {
                printf("%d\n", WEXITSTATUS(status) + 1);
                return 0;
            }
           return WEXITSTATUS(status) + 1;
        }
        memset(buffer, 0, SIZE);
    }
    return 0;
}
