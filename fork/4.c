#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

enum program {
    ERROR = -1,
    SIZE = 4096,
    OFFSET = 4,
    CHILD = 0
};

int main(const int argc, const char *argv[]) {
    char buffer[SIZE];
    char program[SIZE + OFFSET];
    fgets(buffer, SIZE, stdin);
    if ('\n' == buffer[strlen(buffer) - 1]) {
        buffer[strlen(buffer) - 1] = '\0';
    }

    int fd = open("lublu_akos.c", O_RDWR | O_EXCL | O_CREAT,0640);

    if (ERROR == fd) {
        close(fd);
        return ERROR;
    }

    char* program_in_c = "#include <stdio.h>\n"
                          "int main() { \n"
                          "int x = (%s); \n"
                          "printf(\"%%d\\n\", x); \n"
                          "return 0; \n"
                          "}";

    int process_id = fork();
    if (CHILD == process_id) {
        if (snprintf(program, SIZE + OFFSET, program_in_c, buffer) > SIZE + OFFSET) {
            return ERROR;
        }
        dprintf(fd, "%s", program);
        execlp("gcc", "gcc", "lublu_akos.c", NULL);
        perror("smth after gcc exec it's error");
        return ERROR;
    }

    int status = 0;
    waitpid(process_id, &status, 0);

    process_id = fork();
    if (CHILD == process_id) {
        execlp("./a.out", "./a.out", NULL);
        perror("smth after a.out exec it's error");
        return ERROR;
    }

    waitpid(process_id, &status, 0);
    unlink("lublu_akos.c");
    unlink("a.out");
}
