#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signalfd.h>

enum program {
    ERROR = -1,
    TRUE = 1,
    NUMBER_OF_SYMBOLS_TO_READ = 1
};

void print_line (int file_fd) {
    char symbol;
    while (read(file_fd, &symbol, NUMBER_OF_SYMBOLS_TO_READ) > 0) {
        putchar(symbol);
        if ('\n' == symbol) {
            fflush(stdout);
            return;
        }
    }
}

int main (const int argc, const char* argv[]) {
    sigset_t blocking_mask;
    sigfillset(&blocking_mask);
    if (ERROR == sigprocmask(SIG_BLOCK, &blocking_mask, NULL)){
        return ERROR;
    }

    sigset_t my_signals_mask;
    sigemptyset(&my_signals_mask);
    for (int i = 0; i < argc; ++i) {
        sigaddset(&my_signals_mask, SIGRTMIN + i);
    }

    int files[argc];
    for (int i = 1; i < argc; ++i) {
        files[i - 1] = open(argv[i], O_RDONLY);
    }

    int signal_fd = signalfd(-1, &my_signals_mask, 0);
    struct signalfd_siginfo information;

    while (TRUE) {
        read(signal_fd, &information, sizeof(information));
        int number_of_line = information.ssi_signo - SIGRTMIN;

        if (0 == number_of_line) {
            for (int i = 1; i < argc; ++i) {
                close(files[i - 1]);
            }
            return 0;
        } else {
            print_line(files[number_of_line - 1]);
        }

    }
}