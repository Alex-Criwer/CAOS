#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

enum program {
    STDIN_FD = 0,
    STDOUT_FD = 1,
    CHILD = 0,
    SIZE = 4096,
    ERROR = -1,
    NUMBER_OF_ARGUMENTS = 3
};

int main(const int argc, char *argv[]) {
    if(NUMBER_OF_ARGUMENTS != argc) {
        return ERROR;
    }

    char* first_cmd = argv[1];
    char* second_cmd = argv[2];

    int fds_pair[2];
    if (ERROR == pipe(fds_pair)) {
       return ERROR;
    }

    pid_t first_program_id = fork();

    if (CHILD == first_program_id) {
        dup2(fds_pair[1], STDOUT_FD);
        if (ERROR == close(fds_pair[1])) {
            return ERROR;
        }
        execlp(first_cmd, "first_cmd", NULL);
        perror("smth after first exec it's a mistake");
    } else {
        if (ERROR == close(fds_pair[1])) {
            return ERROR;
        }

        pid_t second_program_id = fork();

        if (CHILD == second_program_id) {
            dup2(fds_pair[0],STDIN_FD);
            if (ERROR == close(fds_pair[0])) {
                return ERROR;
            }

            execlp(second_cmd, "second_cmd", NULL);
            perror("smth after seconst exec it's a mistake");
        } else {
            waitpid(first_program_id, 0, 0);
            waitpid(second_program_id, 0, 0);
        }
    }

    return 0;
}
