#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

extern void normalize_path(char * path);

void delete_slash (char* path, int counterOfSlashes) {
    int counter = 1;
    do {
        *(path + counter) = *(path + counter + counterOfSlashes - 1);
        ++counter;
    } while (*(path + counter + counterOfSlashes  - 2) != '\0');
}

void delete_one_point (char* path) {
    delete_slash (path, 2); //т.к. надо удалить ./
}

void delete_two_points (char* path) {
    int counter = 5; // 4 - /../ 
    while (*(path - 1) != '/') {
        --path;
        ++counter;
    }
    delete_slash (path, counter);
}

void normalize_path (char * path) {

    if (*path == '\0') {
        return;
    }

    if (*path != '/') {
        ++path;
        normalize_path (path);
        return;
    }

    int i = 0;
    while (*(path + i) == '/') {
        ++i;
    }

    if (i > 1) {
        delete_slash (path, i);
        normalize_path (path);
        return;
    }

    if (*(path + 1) != '.') {
        ++path;
        normalize_path (path);
        return;;
    }

    if (*(path + 2) != '.') {
        delete_one_point (path);
        normalize_path (path);
        return;
    }

    delete_two_points (path);
    normalize_path (path);
}


