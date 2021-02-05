#define _XOPEN_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

enum CONSTANTS {
    DATE_SIZE = 18,
    MONTH_OFFSET = 5,
    DAY_OFFSET = 8,
    HOURS_OFFSET = 11,
    MINUTES_OFFSET = 14
};

void make_machine_time(char *date, struct tm *tm_date) {
    strptime(date, "%Y-%m-%d %R", tm_date);
    tm_date->tm_sec = 0;
    tm_date->tm_isdst = -1;
    tm_date->tm_wday = 0;
    tm_date->tm_yday = 0;
}

time_t difference(char *first_date, char *second_date) {
    struct tm tm_first_date, tm_second_date;
    make_machine_time(first_date, &tm_first_date);
    make_machine_time(second_date, &tm_second_date);
    time_t first_seconds = mktime(&tm_first_date);
    time_t second_seconds = mktime(&tm_second_date);
    return difftime(second_seconds, first_seconds) / 60;
}

int main(const int argc, char *argv[]) {
    char first_date[DATE_SIZE];
    char second_date[DATE_SIZE];
    memset(first_date, 0, DATE_SIZE);
    memset(second_date, 0, DATE_SIZE);
    fgets(first_date, DATE_SIZE, stdin);
    while (fgets(second_date, DATE_SIZE, stdin) != NULL) {
        printf("%ld\n", difference(first_date, second_date));
        memset(first_date, 0, DATE_SIZE);
        int i;
        for (i = 0; i < DATE_SIZE; ++i) {
            first_date[i] = second_date[i];
        }
        memset(second_date, 0, DATE_SIZE);
    }
    return 0;
}

