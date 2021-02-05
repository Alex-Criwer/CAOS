#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum program {
    ERROR = -1,
    NUMBER_OF_ARGUMENTS = 2
};

int main(const int argc, const char *argv[]) {

    if (NUMBER_OF_ARGUMENTS != argc) {
        perror("invalid number of arguments");
        return ERROR;
    }

    const int N =  strtol(argv[1], NULL, 10);
    int value = 1;

    pid_t process_id;
    for (int i = 0; i < N; ++i) {
        process_id = fork();
        if (ERROR == process_id) {
            perror("invalid fork");
            return ERROR;
        } else if (0 == process_id) { //child
            if(value != N) {
                printf("%d ", value);
            } else {
                printf("%d\n", value);
            }
            return 0;
        } else {
            int status = 0;
            waitpid(process_id, &status, 0);
            ++value;
        }
    }

    return 0;
}