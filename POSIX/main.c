#include <unistd.h>
#include <fcntl.h>

int main(const int argc, const char *argv[]) {
    int exit_code = 0;
    int in = open(argv[1], O_RDONLY);
    if (in == -1) {
        exit_code = 1;
        goto final;
    }
    int out_digits = open(argv[2], O_WRONLY | O_CREAT, 0640);
    int out_other = open(argv[3], O_WRONLY | O_CREAT, 0640);
    if (out_digits == -1 || out_other == -1) {
        exit_code = 2;
        goto final;
    }

    ssize_t in_read;
    char in_byte;
    int out;

    while (in_read = read(in, &in_byte, sizeof(in_byte)) > 0) {
        if (in_byte >= '0' && in_byte <= '9') {
            out = out_digits;
        } else {
            out = out_other;
        }

        if (write(out, &in_byte, sizeof(in_byte)) == -1) {
            exit_code = -1;
            goto final;
        }
    }

    if (in_read == -1) {
        exit_code = 3;
    }

    final:
    close(in);
    close(out_digits);
    close(out_other);
    return exit_code;
}
