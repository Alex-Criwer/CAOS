#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

enum {
    ERROR = -1
};

int count_size(const char* dir_path) {
    struct stat st;
    lstat(dir_path, &st);
    if (S_ISREG(st.st_mode)) {
        return st.st_size;
    } else if (S_ISDIR(st.st_mode)) {
        DIR *dir = opendir(dir_path);
        struct dirent *entry = readdir(dir);
        int sum_size = 0;
        while (entry != NULL) {
            if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
                char next_path[PATH_MAX];
                sprintf(next_path, "%s/%s",dir_path, entry->d_name);
                sum_size += count_size(next_path);
            }
            entry = readdir(dir);
        }

        if (ERROR == closedir(dir)) {
            return ERROR;
        }
        return sum_size;
    }
    return 0;
}

int main(const int argc, const char *argv[]) {
    const char* dir_path = argv[1];
    int sum_size = count_size(dir_path);
    if (ERROR == sum_size) {
        return ERROR;
    }
    printf("%d\n", sum_size);
    return 0;
}
