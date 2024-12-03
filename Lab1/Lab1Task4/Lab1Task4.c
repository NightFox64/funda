#include "functions.h"

int main(int argc, char *argv[]){

    if (argc != 3 && argc != 4){
        printf("Wrong args count");
        return ERROR_NO_VALUES;
    }

    const char* flags[] = {"-d", "/d", "-nd", "/nd", "-i", "/i", "-ni", "/ni", "-s", "/s", "-ns", "/ns", "-a", "/a", "-na", "/na"};
    callback cbs[] = {&funcForD, &funcForI, &funcForS, &funcForA};
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
            int findCbsInt = ret / 4;
            callback find = cbs[findCbsInt];

            char *pathRes;
            char *pathOrig;
            pathOrig = (char*)malloc(sizeof(char) * (strlen(argv[i+1]) + 1));
            if (pathOrig == NULL){
                printf("Failed malloc");
                return ERROR_MALLOC;
            }
            pathOrig = argv[i+1];
            if (strstr(argv[i], "n") == NULL){
                if (argc == 4){
                    printf("Wrong number of args");
                    return ERROR_NO_VALUES;
                }
                pathRes = (char*)malloc(sizeof(char) * (strlen(argv[i+1]) + 5));
                if (pathRes == NULL){
                    free(pathOrig);
                    printf("Failed malloc");
                    return ERROR_MALLOC;
                }
                char ch = '\\';
                int pos = lastPos(pathOrig, ch);
                for (int i = 0; i <= pos; ++i){
                    pathRes[i] = pathOrig[i];
                }

                pathRes[pos+1] = 'o';
                pathRes[pos+2] = 'u';
                pathRes[pos+3] = 't';
                pathRes[pos+4] = '_';
                
                int k = pos+5;
                for (int i = (pos + 1); i < (int)strlen(pathOrig); ++i){
                    pathRes[k] = pathOrig[i];
                    k++;
                }
                pathRes[k] = '\0';
            }
            else{
                
                pathRes = (char*)malloc(sizeof(char) * (strlen(argv[i+2]) + 1));
                if (pathRes == NULL){
                    free(pathOrig);
                    printf("Failed malloc");
                    return ERROR_MALLOC;
                }
                pathRes = argv[i+2];
                if ((cmpFiles(pathOrig, pathRes))){
                    printf("You're trying to overwrite the file. You can't do it");
                    return ERROR_SAME;
                }
            }
            
            //Обработка ошибок
            switch(find(pathOrig, pathRes)){
                case ERROR_OPEN:
                    printf("Can't open a file with this paths");
                    break;
                case ERROR_DELETE:
                    printf("Can't delete a file with this path: %s", pathOrig);
                    break;
                case ERROR_RENAME:
                    printf("Can't rename a file with this path: %s", pathRes);
                    break;
                case SUCCESS:
                    printf("");
            }
            free(pathOrig);
            free(pathRes);
            return SUCCESS;
            i++;
        }
                
    }
    

    return 0;
}
