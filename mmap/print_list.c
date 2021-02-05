#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define END_PTR 0
#define TRUE 1
#define ERROR -1

struct Item {
    int value;
    uint32_t next_pointer;
};

int main(const int argc, char *argv[]) {
    int fd = open(argv[1], O_RDONLY);
    if (ERROR == fd) {
        close(fd);
        return ERROR;
    }
    struct stat st;
    struct Item my_item;
    fstat(fd, &st);
    int file_size = st.st_size;
    if(file_size < sizeof(struct Item)) {
        close(fd);
        return 0;
    }
    struct Item* inf_buff = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    my_item = *inf_buff;
    while (TRUE) {
        printf("%d ", my_item.value);
        if (END_PTR == my_item.next_pointer) {
            break;
        }
        my_item = *(inf_buff + my_item.next_pointer / sizeof(struct Item));
    }
    munmap(inf_buff, file_size);
    close(fd);
    return 0;
}



