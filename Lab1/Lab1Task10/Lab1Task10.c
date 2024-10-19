#include "functions.h"

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Wrong number of arguments\n");
        return ERROR_ARGS;
    }
    if (checkNumber(argv[1])){
        printf("There must be a natural number");
        return ERROR_NAN;
    }
    if ((chToInt(argv[1]) == ERROR_FULL) && (strlen(argv[1]) > 2)){
        printf("Overflow. Your number is too big\n");
        return ERROR_FULL;
    }
    int base = chToInt(argv[1]);
    if(base < 2 || base > 36){
        printf("The number system must be in range of [2, 36]\n");
        return ERROR_FULL;
    }
    
    int res = SUCCESS, count = 0;
    char** strings = input(base, &count, &res);

    if(res != SUCCESS){
        switch(res){
            case ERROR_MALLOC:
                printf("Error with malloc");
                return ERROR_MALLOC;
            case ERROR_NAN:
                printf("There's not a number in your input");
                return ERROR_NAN;
            case ERROR_BASE_NUMBER:
                printf("Your numbers are not from your number system");
                return ERROR_BASE_NUMBER;
        }
    }

    if (func(strings, count, base)){
        printf("You entered too huge number. Please, try smth else");
        return ERROR_FULL;
    }
    for (int i = 0; i < count; i++)
        {
            if(strings[i] != NULL){
                free(strings[i]);
            }
        }
}