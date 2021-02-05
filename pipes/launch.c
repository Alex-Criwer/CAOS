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
    SIZE = 4096
};

int main(const int argc, const char *argv[]) {
    const char *cmd = argv[1];
    const char *in_name = argv[2];

    int in = open(in_name, O_RDONLY);
    dup2(in, STDIN_FD);
    close(in);

    int fds_pair[2];
    pipe(fds_pair);

    pid_t pid = fork();
    if (CHILD == pid) {
        dup2(fds_pair[1], STDOUT_FD);
        close(fds_pair[1]);
        execlp("cmd", cmd, NULL);
    } else {
        close(fds_pair[1]);
        int total_count = 0;
        ssize_t count;
        char buffer[SIZE];
        while ((count = read(fds_pair[0], buffer, SIZE)) > 0) {
            total_count += count;
        }
        waitpid(pid, 0, 0);
        printf("%d\n", total_count);
    }
    return 0;
}
