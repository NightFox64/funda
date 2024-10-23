#include "functions.h"

int main(int argc, char* argv[]) {

    if (checkInput(argc, argv)) {
        printf("Your input must have the flag and args for it\n");
        return ERROR_ARGS;
    }

    switch (argv[1][1]) {
        case 'l':
            if (argc != 3) {
                printf("Your input must have only one string and only one flag\n");
                return ERROR_ARGS;
            }

            printf("The length of your string is: %d\n", demidovStrlen(argv[2]));

            break;

        case 'r':
            if (argc != 3){
                printf("Your input must have only one string and only one flag\n");
                return ERROR_ARGS;
            }

            char* reverse = malloc((demidovStrlen(argv[2]) + 1) * sizeof(char*));
            if (reverse == NULL) {
                printf("Failed to malloc\n");
                return ERROR_MALLOC;
            }

            demidovReverse(reverse, argv[2]);

            printf("Your string was reversed: %s\n", reverse);

            free(reverse);
            break;

        case 'u':
            if (argc != 3){
                printf("Your input must have only one string and only one flag\n");
                return ERROR_ARGS;
            }

            char* smthNew = malloc((demidovStrlen(argv[2]) + 1) * sizeof(char*));
            if (smthNew == NULL) {
                printf("Failed to malloc\n");
                return ERROR_MALLOC;
            }

            raiseOddPos(smthNew, argv[2]);

            printf("All odd positions were raised: %s\n", smthNew);
            free(smthNew);
            break;

        case 'n':
            if (argc != 3){
                printf("Your input must have only one string and only one flag\n");
                return ERROR_ARGS;
            }

            char *res = malloc((demidovStrlen(argv[2]) + 1) * sizeof(char*));
            if (res == NULL) {
                perror("Failed to malloc\n");
                return ERROR_MALLOC;
            }

            if (changeOrder(res, argv[2])){
                printf("Failed to malloc\n");
                return ERROR_MALLOC;
            }

            printf("Here is your right order: %s\n", res);
            free(res);
            break;

        case 'c':
            if (argc < 4){
                printf("Your input must have one flag, seed and minimum one string\n");
                return ERROR_ARGS;
            }
            if (!checkNumber(argv[2]) || atoi(argv[2]) < 0){
                printf("Seed must be a natural number\n");
                return ERROR_ARGS;
            }

            int allLen = 0;
            for (int i = 4; i < argc; i++){
                allLen += demidovStrlen(argv[i]);
            }

            char* result = (char*)malloc((allLen + 1) * sizeof(char*));
            if (result == NULL) {
                printf("Failed to malloc\n");
                return ERROR_MALLOC;
            }

            if (randomStrcat(argc, argv, result) == ERROR_MALLOC){
                printf("Failed to malloc in func\n");
                return ERROR_MALLOC;
            }

            printf("Your ultimate result: %s\n", result);
            free(result);
            break;

        default:
            printf("Wrong flag\n");
            return ERROR_ARGS;
    }

    return SUCCESS;
}
