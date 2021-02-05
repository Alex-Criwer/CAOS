#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>

struct Item {
    int value;
    uint32_t next_pointer;
};

enum program {
    ERROR = -1
};

int main(const int argc, const char *argv[]) {
    if (argc != 2) {
        return ERROR;
    }

    int nextPointer = -1;
    struct Item item;
    int my_fd = open(argv[1], O_RDONLY);
    if (ERROR == my_fd) {
        return ERROR;
    }

    while (nextPointer != 0) {
        ssize_t numberOfReadBytes = read(my_fd, &item, sizeof(item));
        if (numberOfReadBytes <= 0) {    // достигнут конец файла или ошибка
            break;
        }
        printf("%d ", item.value);
        nextPointer = item.next_pointer;
        lseek(my_fd, item.next_pointer, SEEK_SET);
    }
    if (ERROR == close(my_fd)) {
        return ERROR;
    }
    return 0;
}