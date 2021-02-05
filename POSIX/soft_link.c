#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

enum Program {
    SIZE = PATH_MAX + 2 // подушка безопасности, чтобы избежть \n \0
};

int main(const int argc, const char* argv[]) {
    char fileName[SIZE];
    char absoluteFileName[SIZE];
    struct stat infAboutFile;
    while(fgets(fileName, SIZE, stdin)) {
        fileName[strlen(fileName) - 1] = '\0';  // обозначаем конец имени
        if(lstat(fileName, &infAboutFile) == 0) {
            if(S_ISLNK(infAboutFile.st_mode)) {
                char* ptr = realpath(fileName, absoluteFileName);
                if(ptr == NULL) {
                    continue;
                }
                printf("%s\n", absoluteFileName);
            } else if (S_ISREG(infAboutFile.st_mode)){
                char link[SIZE] = "link_to_";
                strcat(link, fileName);
                int error = symlink(fileName, link);
                if(error) {
                    continue;
                }
                printf("%s\n", link);
            }
        }
    }

    return 0;
}
