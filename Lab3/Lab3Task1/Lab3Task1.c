#include "functions.h"

int main() {
    char* result;
    int number = -5545;
    unsigned short r = 1;
    int code = SUCCESS;
    result = decimalToBase2r(number, r, &code);
    if (code != SUCCESS) {
        logErrors(code);
        return code;
    }
    printf("%s", result);
    free(result);
    return SUCCESS;
}