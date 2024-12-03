#include "functions.h"

int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Wrong number of arguments");
        return ERROR_ARGS;
    }

    if (checkNumber(argv[1])){
        printf("There must be an epsilon and x");
        return ERROR_NAN;
    }

    if (chToD(argv[1]) == ERROR_FULL && ((int)strlen(argv[1]) > 3)){
        printf("Your number is too big");
        return ERROR_FULL;
    }

    double eps = chToD(argv[1]);
    callback cbs[] = {&funcA, &funcB, &funcC, &funcD};
    for (int i = 0; i < 4; i++){
        callback find = cbs[i];

        if (integral(eps, find)){
            printf("Your epsilon is too big for current sum");
            return ERROR_EPS;
        }
    }
                
    return 0;
}
