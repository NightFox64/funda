#include "functions.h"

int main(int argc, char *argv[]){

    if (argc != 3){
        printf("Wrong args count");
        return ERROR_NO_VALUES;
    }

    for (int i = 1; i < argc; ++i)
    {
        char *pathRes;
        char *pathOrig;
        pathOrig = (char*)malloc(sizeof(char) * (strlen(argv[i+1]) + 1));
        if (pathOrig == NULL){
            printf("Failed malloc");
            return ERROR_MALLOC;
        }
        pathRes = (char*)malloc(sizeof(char) * (strlen(argv[i+2]) + 1));
        if (pathRes == NULL){
            free(pathOrig);
            printf("Failed malloc");
            return ERROR_MALLOC;
        }

        pathOrig = argv[i];
        pathRes = argv[i+1];

        if ((cmpFiles(pathOrig, pathRes))){
            printf("You're trying to overwrite the file. You can't do it");
            return ERROR_SAME;
        }
        
        switch (readPush(pathOrig, pathRes))
        {
        case 2:
            printf("Can't open the file with this path");
            break;
        case 3:
            printf("Overflow. The number in the file is too big");
            break;
        case 5:
            printf("Please remove not number characters");
            break;
        }

        return SUCCESS;
        i++;
    }
                
    return SUCCESS;
}
