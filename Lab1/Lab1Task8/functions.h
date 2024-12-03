#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

enum ret_type_t{
    SUCCESS,    //Успех
    ERROR_NO_VALUES, //Недостаточно аргументов
    ERROR_OPEN,  //Не удалось открыть файл
    ERROR_FULL,  //Переполнение числа
    ERROR_SAME,  //Одинаковые файлы
    ERROR_TRASH, //Прекращает работау, если попадается мусор
    ERROR_MALLOC    //Ошибка выделения памяти
};

//Сравнение имен двух файлов по данным путям
int cmpFiles(char* pathOrig, char* pathRes){
    char* ptrOrig, *ptrRes;
    ptrOrig = strrchr(pathOrig, '/');
    ptrRes = strrchr(pathRes, '/');
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

//Определяет минимальное основание
int foundation(char* number){
    int found = 2;
    for (int i = 0; i < (int)strlen(number); ++i){
        if ((number[i] >= '0') && (number[i] <= '9')){
            found = fmax(found, number[i] - '0' + 1);
        }
        else{
            if ((number[i] >= 'a') && (number[i] <= 'z')){
                found = fmax(found, number[i] - 'a' + 10 + 1);
            }
            if ((number[i] >= 'A') && (number[i] <= 'Z')){
                found = fmax(found, number[i] - 'A' + 10 + 1);
            }
        }
    }

    return found;
}

long long convertDecPrint(char* number, int base){
    long long m = 1, sum = 0, mBuf = m;
    for (int i = (int)strlen(number) - 1; i >= 0; i--){
        if ((number[i] >= '0') && (number[i] <= '9')){
            sum += (number[i] - '0') * m;
        }
        else{
            sum += (tolower(number[i]) - 10 - 'a') * m;
        }
        m *= base;
        if (m < mBuf){
            return ERROR_FULL;
        }
        else{
            mBuf = m;
        }
    }
    return sum;
}

//Переписывает оригинальный файл в результирующий с кучей странных условий...
int readPush(char* path_orig, char* path_res){

    FILE* fileOrig, *fileRes;
    if (!fopen(path_orig, "r") || !fopen(path_res, "w")){
        return ERROR_OPEN;
    }
    fileOrig = fopen(path_orig, "r");
    fileRes = fopen(path_res, "w");

    char c;
    int i = 0;
    char* number = (char*)malloc(sizeof(char) * 2);
    int iterMalloc = 4;

    while ((c = fgetc(fileOrig)) != EOF){
        if (!isalnum(c) && (c != ' ') && (c != '\t') && (c != '\n')){
            return ERROR_TRASH;
        }
        while ((c == ' ') || (c == '\t') || (c == '\n') || (c == '0')){
            c = fgetc(fileOrig);
        }
        if (c == EOF){
            break;
        }
        i = 0;
        while ((c != ' ') && (c != '\t') && (c != '\n') && (c != EOF)){
            if (i > 1){
                if (iterMalloc < i){
                    iterMalloc *= 2;
                    number = (char*)realloc(number, iterMalloc * sizeof(char));
                }
            }
            number[i] = c;
            c = fgetc(fileOrig);
            i++;
        }
        if (i > 1){
                if (iterMalloc < i){
                    iterMalloc *= 2;
                    number = (char*)realloc(number, iterMalloc * sizeof(char));
                }
            }
        number[i] = '\0';

        for (int j = 0; j < (int)strlen(number); j++){
            fputc(number[j], fileRes);
        }
        fprintf(fileRes, " %d ", foundation(number));

        if (convertDecPrint(number, foundation(number)) == ERROR_FULL){
            fprintf(fileRes, "(Number is too long)\n");
        }
        else{
            fprintf(fileRes, "%lli\n", convertDecPrint(number, foundation(number)));
        }

        if (c == EOF){
            break;
        }
    }
    
    fclose(fileOrig);
    fclose(fileRes);

    return SUCCESS;
}
