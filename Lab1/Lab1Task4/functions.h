#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

enum ret_type_t{
    SUCCESS,    //Успех
    ERROR_NO_VALUES, //Недостаточно аргументов
    ERROR_OPEN,  //Не удалось открыть файл
    ERROR_DELETE,   //Не удалось удалить оригинальный файл
    ERROR_RENAME,    //Не удалось переименовать выходной файл
    ERROR_SAME,  //Одинаковые файлы
    ERROR_MALLOC    //Ошибка выделения памяти
};
typedef int (*callback)(char*, char*);

//Находит последнее вхождение символа
int lastPos(char* origStr, char ch){
    int res = -1;
    for (int i = 0; i < (int)strlen(origStr); i++){
        if (origStr[i] == ch){
            res = i;
        }
    }
    return res;
}

//Сравнение имен двух файлов по данным путям
int cmpFiles(char* pathOrig, char* pathRes){
    char* ptrOrig, *ptrRes;
    ptrOrig = strrchr(pathOrig, '\\');
    ptrRes = strrchr(pathRes, '\\');
    if(!(ptrOrig == NULL && ptrRes == NULL)){
        
        if(ptrOrig != NULL && ptrRes == NULL){
            ptrOrig++;
            return !strcmp(ptrOrig, pathRes);
        }
        else if(ptrOrig == NULL && ptrRes != NULL){
            ptrRes++;
            return !strcmp(ptrRes, pathOrig);
        }
        else{
            ptrOrig++;
            ptrRes++;
            return !strcmp(ptrOrig, ptrRes);
        }
    }
    if(!strcmp(pathOrig, pathRes)){
        return 1;
    }
    return 0;
}


//Проверка флага
int findFlag(char* qarg, const char** flags, int size){
    for (int i = 0; i < size; ++i)
    {
        if (!(strcmp(qarg, flags[i])))
        {
            return i;
        }
        
    }
   return -1; 
}

//Исключает арабские цифры из файла
int funcForD(char* path_orig, char* path_res){

    FILE* fileOrig, *fileRes;
    if (!fopen(path_orig, "r") || !fopen(path_res, "w")){
        return ERROR_OPEN;
    }
    fileOrig = fopen(path_orig, "r");
    fileRes = fopen(path_res, "w");

    char c;
    while ((c = fgetc(fileOrig)) != EOF){
        if (!((c >= '0') && (c <= '9'))){
            fputc(c, fileRes);
        }
    }
    fclose(fileOrig);
    fclose(fileRes);

    return SUCCESS;
}

//Записывает для каждой строки файла количество букв латинского алфавита
int funcForI(char* path_orig, char* path_res){

    FILE* fileOrig, *fileRes;
    if (!fopen(path_orig, "r") || !fopen(path_res, "w")){
        return ERROR_OPEN;
    }
    fileOrig = fopen(path_orig, "r");
    fileRes = fopen(path_res, "w");

    char c;
    int counter = 0;
    while ((c = fgetc(fileOrig)) != EOF){
        if (c != '\n'){
            if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))){
                counter++;
            }
        }
        else{
            fprintf(fileRes, "%d\n", counter);
            counter = 0;
        }
    }
    fprintf(fileRes, "%d\n", counter);
    fclose(fileOrig);
    fclose(fileRes);

    return SUCCESS;
}

//Записывает для каждой строки файла количество символов, отличных от латинского алфавита, арабских цифр, а также пробела
int funcForS(char* path_orig, char* path_res){

    FILE* fileOrig, *fileRes;
    if (!fopen(path_orig, "r") || !fopen(path_res, "w")){
        return ERROR_OPEN;
    }
    fileOrig = fopen(path_orig, "r");
    fileRes = fopen(path_res, "w");

    char c;
    int counter = 0;
    while ((c = fgetc(fileOrig)) != EOF){
        if (c != '\n'){
            if (!(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) && !((c >= '0') && (c <= '9')) && !(c == ' ')){
                counter++;
            }
        }
        else{
            fprintf(fileRes, "%d\n", counter);
            counter = 0;
        }
    }
    fprintf(fileRes, "%d\n", counter);
    fclose(fileOrig);
    fclose(fileRes);

    return SUCCESS;
}



//Заменяет все !(арабские цифры) в файле на ASCII код в 16-ричной системе счисления
int funcForA(char* path_orig, char* path_res){

    FILE* fileOrig, *fileRes;
    
    fileOrig = fopen(path_orig, "r");
    fileRes = fopen(path_res, "w");

    if (!fileOrig || !fileRes){
        return ERROR_OPEN;
    }

    char c;
    char number[100];
    while ((c = fgetc(fileOrig)) != EOF){
        if (!((c >= '0') && (c <= '9')) && (c != '\n')){
            int codeASCII = c;
            int i = 0;
            while(codeASCII != 0){
                int rem = codeASCII % 16;
                if (rem <= 9){
                    number[i] = (char)(rem + '0');
                    i++;
                }
                else{
                    number[i] = (char)(rem - 10 + 'A');
                    i++;
                }
                codeASCII /= 16;
            }
            number[i] = '\0';
            for (int j = i - 1; j >= 0; j--){
                fputc(number[j], fileRes);
            }
        }
        else{
            fputc(c, fileRes);
        }
    }

    fclose(fileOrig);
    fclose(fileRes);

    return SUCCESS;
} 
