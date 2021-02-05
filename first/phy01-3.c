#include <stdio.h>
#include <inttypes.h>

const size_t DIFF_BTW_NUM_AND_UPPERCASE = 10;
const size_t DIFF_BTW_NUM_AND_LOWERCASE = 36;
const size_t SET_SIZE = 62;

size_t fromCharToNumber(const char element) {
    if (element >= '0' && element <= '9') {
        return element - '0';
    } else if (element >= 'A' && element <= 'Z') {
        return element - 'A' + DIFF_BTW_NUM_AND_UPPERCASE;
    } else {
        return element - 'a' + DIFF_BTW_NUM_AND_LOWERCASE;
    }
}

char fromNumbertoChar(size_t number) {
    if (number >= 0 && number <= 9) {
        return (char) (number + '0');
    } else if (number >= DIFF_BTW_NUM_AND_UPPERCASE && number < DIFF_BTW_NUM_AND_LOWERCASE) {
        return (char) (number - DIFF_BTW_NUM_AND_UPPERCASE + 'A');
    } else {
        return (char) (number - DIFF_BTW_NUM_AND_LOWERCASE + 'a');
    }
}

int main() {
    uint64_t resultSet = 0,
             timeSet = 0;
    char elementOfTheSet = ' ';
    uint64_t i = 0;
    uint64_t myLiteral = 1;
    while ((elementOfTheSet = getchar()) != EOF) {
        if (elementOfTheSet == '&') {
            resultSet &= timeSet;
            timeSet = 0;
        } else if (elementOfTheSet == '|') {
            resultSet |= timeSet;
            timeSet = 0;
        } else if (elementOfTheSet == '^') {
            resultSet ^= timeSet;
            timeSet = 0;
        } else if (elementOfTheSet == '~') {
            resultSet = ~resultSet;
        } else {
            myLiteral = 1;
            myLiteral = (myLiteral << fromCharToNumber(elementOfTheSet));
            timeSet |= myLiteral;
        }
    }

    for (i = 0; i < SET_SIZE; ++i) {
        if (((resultSet >> i) & (uint64_t) 1) == 1) {
            printf("%c", fromNumbertoChar(i));
        }
    }
    return 0;
}