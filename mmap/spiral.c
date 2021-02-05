#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

enum mistakes {
    NUMBER_OF_ARGUMENTS = 4,
    ERROR = -1
};

void add_value(char *buffer, const int height, const int width, const int row, const int column, int value) {
    char *current_position = buffer + (height * width + 1) * row + width * column;
    char symbol = *(current_position + width);
    if (snprintf(current_position, width + 1, "%*d", width, value) <= width) { // запись в массив и проверка на ошибку
        *(current_position + width) = symbol;
    }
}

void snake(const int height, const int width, char *buffer) {
    int begin_row = 0;
    int end_row = height;
    int begin_column = 0;
    int end_column = height;
    int value = 1;
    while (begin_row < end_row && begin_column < end_column) {

        for (int i = begin_column; i < end_column; ++i) {
            add_value(buffer, height, width, begin_row, i, value);
            ++value;
        }
        ++begin_row;

        for (int i = begin_row; i < end_row; ++i) {
            add_value(buffer, height, width, i, end_column - 1, value);
            ++value;
        }
        --end_column;

        if (begin_row < end_row) {
            for (int i = end_column - 1; i >= begin_column; --i) {
                add_value(buffer, height, width, end_row - 1, i, value);
                ++value;
            }
            --end_row;
        }

        if (begin_column < end_column) {
            for (int i = end_row - 1; i >= begin_row; --i) {
                add_value(buffer, height, width, i, begin_column, value);
                ++value;
            }
            ++begin_column;
        }
    }
    char *cur; // расставим 'n'
    for (int i = 0; i < height; ++i) {
        cur = buffer + (width * height) + i * (width * height + 1);
        *cur = '\n';
    }
}

int main(const int argc, const char *argv[]) {

    if (argc != NUMBER_OF_ARGUMENTS) {
        perror("wrong number of arguments");
        return ERROR;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, 0640);
    if (ERROR == fd) {
        close(fd);
        return ERROR;
    }

    const int N = strtol(argv[2], NULL, 10);
    const int W = strtol(argv[3], NULL, 10);
    const int size_of_file = N * N * W + N; // т.к. в конце должны стоять \n

    if (ERROR == ftruncate(fd, size_of_file)) {
        perror("can't allocate size");
        return ERROR;
    }

    char *buff_snake = mmap(NULL, size_of_file, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    snake(N, W, buff_snake);

    if (ERROR == munmap(buff_snake, size_of_file) || ERROR == close(fd)) {
        return ERROR;
    }

    return 0;
}





