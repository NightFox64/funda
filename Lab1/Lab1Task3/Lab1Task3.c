#include "functions.h"

int main(int argc, char *argv[]){

    if (argc == 1){
        printf("Maybe you want to put something?");
        return ERROR_ARGS;
    }

    const char* flags[] = {"-q", "/q", "-m", "/m", "-t", "/t"};
    callback cbs[] = {&funcForQ, &funcForM, &funcForT};
    for (int i = 1; i < argc; ++i)
    {
        int ret = findFlag(argv[i], flags, sizeof(flags)/sizeof(char*));
        if (ret == -1)
        {
            printf("This flag doesn't exist: %s\n", argv[i]);
            return -1;
        }
        else 
        {
            int findCbsInt = ret / 2;
            callback find = cbs[findCbsInt];

            if (findCbsInt == 1 && argc != 4){
                printf("Wrong number of arguments");
                return ERROR_ARGS;
            }

            if ((findCbsInt == 0 || findCbsInt == 2) && argc != 6){
                printf("Wrong number of arguments");
                return ERROR_ARGS;
            }

            for (int j = i+1; j < argc; ++j){
                if (checkNumber(argv[j])){
                    printf("There must be a number");
                    return ERROR_NAN;
                }

                if (chToD(argv[j]) == ERROR_FULL && ((int)strlen(argv[j]) > 3)){
                    printf("Your number is too big");
                    return ERROR_FULL;
                }
            }

            if (findCbsInt == 1){
                double arg1 = chToD(argv[i+1]);
                double arg2 = chToD(argv[i+2]);
                if (find(arg1, arg2, 0, 0)){
                    printf("You can't dev on NULL");
                    return ERROR_DEL_NULL;
                }
                return SUCCESS;
            }
            else{
                double eps = chToD(argv[i+1]);
                double arg1 = chToD(argv[i+2]);
                double arg2 = chToD(argv[i+3]);
                double arg3 = chToD(argv[i+4]);

                find(eps, arg1, arg2, arg3);
                return SUCCESS;
            }

            i++;
        }
                
    }
    

    return 0;
}
