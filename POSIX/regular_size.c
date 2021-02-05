#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define SIZE 4096

int main(const int argc, const char *argv[]) {
    off_t sumSize = 0;
    char fileName[SIZE];
    while (fgets(fileName, SIZE, stdin) != NULL) {
        for (int i = 0; i < SIZE && fileName[i] != EOF; ++i) {
            if (fileName[i] == '\n') { // то есть мы пишем другой filename
                fileName[i] = '\0';
                break;
            }
        }
        struct stat infAboutFile;
        if (lstat(fileName, &infAboutFile) == 0 && S_ISREG(infAboutFile.st_mode)) {
            sumSize += infAboutFile.st_size;
        }
    }
    printf("%ld", sumSize);
    return 0;
}