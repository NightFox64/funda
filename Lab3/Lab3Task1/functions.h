#include "errors.h"

unsigned int ultimateInc(unsigned int n) {
    unsigned int mask = 1;
    while (n & mask) {
        n ^= mask;
        mask <<= 1;
    }
    n ^= mask;
    return n;
}

unsigned int ultimateDec(unsigned int n) {
    unsigned int mask = 1;
    while (!(n & mask)) {
        n ^= mask;
        mask <<= 1;
    }
    n ^= mask;
    return n;
}

unsigned int ultimateProz2(unsigned int n){
    return n <<= 1;
}

char* decimalToBase2r(int numberInput, unsigned short r, int* code) {
    if (r > 5 || r < 1) {
        *code = ERROR_ARGS;
        return NULL;
    }
    *code = SUCCESS;
    unsigned int base = 1 << r;
    unsigned int mask = ultimateDec(base);
    unsigned int memo = sizeof(char);
    unsigned int number = abs(numberInput);
    int flagMinus = 0;

    char* result = (char*)malloc(memo);
    if (result == NULL) {
        *code = ERROR_MALLOC;
        return NULL;
    }

    if (numberInput < 0) {
        flagMinus = 1;
    }
    
    unsigned int index = 0;
    char* chars = "0123456789abcdefghijklmnopqrstuv";

    while (number > 0) {
        if (index >= memo){
            memo = ultimateProz2(memo);
            char* buff = (char*)realloc(result, memo);
            if (buff == NULL){
                *code = ERROR_MALLOC;
                free(result);
                return NULL;
            }
            result = buff;
        }
        result[index] = chars[(number & mask)];
        index = ultimateInc(index);
        number >>= r;
    }

    if (flagMinus){
        result[index] = '-';
        index = ultimateInc(index);
    }

    result[index] = '\0';
    int left = 0;
    int right = ultimateDec(index);
    while(left < right) {
        char temp = result[right];
        result[right] = result[left];
        result[left] = temp;
        left = ultimateInc(left);
        right = ultimateDec(right);
    }
    return result;
}