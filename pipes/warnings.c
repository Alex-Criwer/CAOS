#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


// the view of error is connect_2_processes.c:22:23: error: initialization discards

enum program {
    STDIN_FD = 0,
    STDOUT_FD = 1,
    ERROR_FD = 2,
    CHILD = 0,
    SIZE = 4096,
    ERROR = -1,
    NUMBER_OF_ARGUMENTS = 2,
};

int main(const int argc, char *argv[]) {
    if (NUMBER_OF_ARGUMENTS != argc) {
        return ERROR;
    }

    int number_of_errors = 0, number_of_warnings = 0;

    char *program_name = argv[1];
    int file_descriptor = open(program_name, O_RDONLY);
    if (ERROR == file_descriptor) {
        return ERROR;
    }

    int fds_pair[2];
    pipe(fds_pair);

    pid_t program_id = fork();
    if (ERROR == program_id) {
        return ERROR;
    }

    if (CHILD == program_id) {
        dup2(fds_pair[1], ERROR_FD);
        close(fds_pair[1]);
        execlp("gcc", "gcc", program_name, NULL);
        perror("smth wrong in first exec");
    } else {
        close(fds_pair[1]); // to avoid dead lock
        dup2(fds_pair[0], STDIN_FD);
        close(fds_pair[0]);

        int prev_error_line = -1, prev_warning_line = -1;
        const char *format_to_read = strcat(program_name, ":%d:%d:");
        char buffer[SIZE];
        while (scanf("%s", buffer) != EOF) {
            int line = 0, position = 0;
            int number_of_arguments = sscanf(buffer, format_to_read, &line, &position);
            if (2 == number_of_arguments) {
                scanf("%s", buffer);
                if (line != prev_error_line && strcmp("error:", buffer) == 0) {
                    ++number_of_errors;
                    prev_error_line = line;
                }

                if (line != prev_warning_line && strcmp("warning:", buffer) == 0) {
                    ++number_of_warnings;
                    prev_warning_line = line;
                }
            }
        }
    }

    waitpid(program_id, 0, 0);
    printf("%d %d", number_of_errors, number_of_warnings);

    return 0;
}
