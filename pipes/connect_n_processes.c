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
};

int main(const int argc, char *argv[]) {
    int first_fds_pair[2];
    if (ERROR == pipe(first_fds_pair)) {
        return ERROR;
    }

    pid_t first_program_id = fork();
    if (ERROR == first_program_id) {
        return ERROR;
    }

    if (CHILD == first_program_id) {
        dup2(first_fds_pair[1], STDOUT_FD);
        if (ERROR == close(first_fds_pair[1])) {
            return ERROR;
        }
        close(first_fds_pair[0]);
        execlp(argv[1], argv[1], NULL);
        perror("smth after first exec it's a mistake");
    }

    waitpid(first_program_id, 0,0);

    int second_fds_pair[2];
    if (ERROR == pipe(second_fds_pair)) {
        return ERROR;
    }

    for (int i = 2; i < argc; ++i) {
        pid_t i_program_id = fork();
        if (CHILD == i_program_id) {
            dup2(first_fds_pair[0], STDIN_FD);
            close(first_fds_pair[0]);
            close(first_fds_pair[1]);
            if (argc - 1 != i) {
                dup2(second_fds_pair[1], STDOUT_FD);
                close(second_fds_pair[1]);
                close(second_fds_pair[0]);
            }
            execlp(argv[i], argv[i], NULL);
            perror("smth after i exec it's a mistake");
        }
        close(first_fds_pair[1]);
        close(first_fds_pair[0]);
        waitpid(i_program_id, 0, 0);
        if (argc - 1 == i) {
            break;
        }
        first_fds_pair[0] = second_fds_pair[0];
        first_fds_pair[1] = second_fds_pair[1];
        pipe(second_fds_pair);
    }
    return 0;
}


