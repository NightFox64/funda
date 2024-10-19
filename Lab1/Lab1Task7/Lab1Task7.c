#include "functions.h"

int main(int argc, char *argv[]){

    if (argc != 5 && argc != 4){
        printf("Wrong args count");
        return ERROR_NO_VALUES;
    }

    const char* flags[] = {"-r", "/r", "-a", "/a"};
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

            if (findCbsInt == 0){
                char* pathLex1, *pathLex2, *pathRes; 
                if (malloc(sizeof(char) * (strlen(argv[i+1]) + 1)) != NULL){
                    char *pathLex1 = (char*)malloc(sizeof(char) * (strlen(argv[i+1]) + 1));
                }
                else{
                    printf("Failed malloc");
                    return ERROR_MALLOC;
                }
                if (malloc(sizeof(char) * (strlen(argv[i+2]) + 1)) != NULL){
                    char *pathLex2 = (char*)malloc(sizeof(char) * (strlen(argv[i+2]) + 1));
                }
                else{
                    printf("Failed malloc");
                    return ERROR_MALLOC;
                }
                if (malloc(sizeof(char) * (strlen(argv[i+3]) + 1)) != NULL){
                    char *pathRes = (char*)malloc(sizeof(char) * (strlen(argv[i+3]) + 1));
                }
                else{
                    printf("Failed malloc");
                    return ERROR_MALLOC;
                }

                pathLex1 = argv[i+1];
                pathLex2 = argv[i+2];
                pathRes = argv[i+3];

                if ((cmpFiles(pathLex1, pathRes)) || (cmpFiles(pathLex2, pathRes))){
                    printf("You're trying to overwrite the file. You can't do it");
                    return ERROR_SAME;
                }

                //Обработка ошибок
                switch(funcForR(pathLex1, pathLex2, pathRes)){
                    case ERROR_OPEN:
                        printf("Can't open a file with this path");
                        break;
                    case SUCCESS:
                        printf("");
                }
            }
            else{
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
                
                pathRes = argv[i+2];
                pathOrig = argv[i+1];
                
                if ((cmpFiles(pathOrig, pathRes))){
                    printf("You're trying to overwrite the file. You can't do it");
                    return ERROR_SAME;
                }

                //Обработка ошибок
                switch(funcForA(pathOrig, pathRes)){
                    case ERROR_OPEN:
                        printf("Can't open a file with this path");
                        break;
                    case SUCCESS:
                        printf("");
                }
            }

            return SUCCESS;
            i++;
        }
                
    }
    

    return 0;
}
