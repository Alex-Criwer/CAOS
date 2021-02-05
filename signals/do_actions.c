#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

enum program {
    TRUE = 1,
    FALSE = 0
};

volatile sig_atomic_t answer = 0;
volatile sig_atomic_t another_sign = FALSE;
volatile sig_atomic_t must_exit = FALSE;
volatile sig_atomic_t must_to_clear_stdout = FALSE;

void handle_sigusr1(int signum) {
    ++answer;
    must_to_clear_stdout = TRUE;
}

void handle_sigusr2(int signum) {
    another_sign = TRUE;
    must_to_clear_stdout = TRUE;
}

void handle_term(int signum){
    must_exit = TRUE;
}

int main() {
    struct sigaction actions_usr1;
    memset(&actions_usr1, 0, sizeof(struct sigaction));
    actions_usr1.sa_handler = handle_sigusr1;
    actions_usr1.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &actions_usr1, NULL);

    struct sigaction actions_usr2;
    memset(&actions_usr2, 0, sizeof(struct sigaction));
    actions_usr2.sa_handler = handle_sigusr2;
    actions_usr2.sa_flags = SA_RESTART;
    sigaction(SIGUSR2, &actions_usr2, NULL);

    struct sigaction actions_term;
    memset(&actions_term, 0, sizeof(struct sigaction));
    actions_term.sa_handler = handle_term;
    actions_term.sa_flags = SA_RESTART;
    sigaction(SIGTERM, &actions_term, NULL);

    printf("%d\n", getpid());
    fflush(stdout);
    scanf("%d", &answer);

    while (!must_exit) {
        pause();
        if (another_sign) {
            answer *= (-1);
            another_sign = FALSE;
        }

        if (must_to_clear_stdout) {
            printf("%d\n", answer);
            fflush(stdout);
            must_to_clear_stdout = FALSE;
        }
    }
    return 0;
}