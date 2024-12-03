#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

enum ret_type_t{
    SUCCESS,    //Успех
    ERROR_NAN,   //Не является числом
    ERROR_FULL,  //Переполнение
    ERROR_ARGS,  //Количество аргументов неверное
    ERROR_MALLOC,    //Ошибка выделения памяти
    ERROR_BASE_NUMBER   //Число не подходит под основание
};

//Проверяет является ли строковое представление натуральным числом
int checkNumber(char* x){
    for (int i = 0; i < (int)strlen(x); i++){
        if ((x[i] < '0' || x[i] > '9')){
            return ERROR_NAN;
        }
    }
    return SUCCESS;
}

//Проверяет является ли строковое представление целым числом в сс от 2 до 36
int checkNumberInput(char* x){
    for (int i = 0; i < (int)strlen(x) - 1; i++){
        if (!(x[i] >= '0' && x[i] <= '9') && !(x[i] >= 'A' && x[i] <= 'Z')){
            return ERROR_NAN;
        }
    }
    return SUCCESS;
}

//Перевод из строкового представления в int-овое
int chToInt(char* x){
    int xInt = 0;
    int m = 1;
    int mBuf = 1;

    for (int i = (int)strlen(x) - 1; i >= 0; --i){
        xInt += (x[i] - '0') * m;
        m *= 10;
        if (mBuf > m){
            return ERROR_FULL;
        }
        mBuf *= 10;
    }
    return xInt;
}

//Переводит из десятичной в данную
char* toBaseN(int x, int n){
    char nw[BUFSIZ];
    int minFlag = 0;
    int del = 0, iter = 0, xBuf = x;
    if (x < 0){
        nw[iter] = '-';
        iter++;
        xBuf = abs(x);
    }
    while(xBuf != 0){
        del = xBuf % n;
        xBuf = xBuf / n;
        if(del >= 0 && del <= 9){
            nw[iter++] = del + '0';
        }
        else if(del > 9)
        {
            nw[iter++] = del + 'A' - 10;
        }
    }
    nw[iter] = '\0';
    char* ans = (char*)malloc(sizeof(char)*iter);
    if (ans == NULL){
        return NULL;
    }
    if(ans != NULL){
        int k = 0;
        if (nw[0] == '-'){
            ans[0] = '-';//0[ans] = *(0 + ans)
            k++;
        }
        for (int i = iter - 1, j = k; i >= 0; i--, j++)
        {
            ans[j] = nw[i];
        }
        ans[iter] = '\0';
        return ans;
    }
    else{
        char *s;
        *s = '0';
        return s;
    }
}


long long int gorner(char* _str, int size, int base){
    char str[BUFSIZ];
    for (int i = 0; i < size; i++)
    {
        str[i] = _str[i];
    }
    str[size - 1] = '\0';
    long long int res = 0, resBuf = res;
    char *ps = str;
    ps = str - 1;
    
    int minFlag = 1;
    if(*(ps+1) == '-'){
        *++ps;
    }
    if (str[0] == '-'){
        minFlag = -1;
    }
    while(*++ps){
        res = (res * base) + ((isalpha(*ps))? *ps - 'A' + 10: *ps - '0');
        if (res < resBuf){
            return LLONG_MAX;
        }
        resBuf = res;
    }
    return (minFlag * res);
}

//Проверяет, что число в нужной системе счисления
int checkBase(char* str, int size, int base){
    char charBase;
    if (base <= 9){
        charBase = base + '0';
    }
    else{
        charBase = base + 'A' - 10;
    }

    int i;
    if (str[0] == '-'){
        i = 1;
    }
    else{
        i = 0;
    }

    for (; i < size - 1; i++)
    {
        if(str[i] >= charBase){
            return ERROR_FULL;
        }
    }
    return SUCCESS;
}

int func(char** strings, int cnt, int num_sys){
    long long int sVal;
    char* sStr;
    sVal = gorner(strings[0], strlen(strings[0]), num_sys);
    if (sVal == LLONG_MAX){
        return ERROR_FULL;
    }
    sStr = strings[0];
    for (int i = 1; i < cnt; i++)
    {
        long long int v = gorner(strings[i], strlen(strings[i]), num_sys);
        if (v == LLONG_MAX){
            return ERROR_FULL;
        }
        if(sVal < v){
            sVal = v;
            sStr = strings[i];
        }
    }

    if(sStr[0] == '0' || (sStr[0] == '-' && sStr[1] == '0')){
        while(*sStr == '0'){
            sStr++;
        }
        char* save = sStr;
        while(*sStr != '\n'){
            sStr++;
        }
        *(sStr) = '\0';
        sStr = save;
        if(*sStr == '\n'){
            *--sStr = '0';
            *(sStr+1) = '\0';
        }
    }
    else{
        char* save = sStr;
        while(*sStr != '\n'){
            sStr++;
        }
        *(sStr) = '\0';
        sStr = save;
    }
    printf("%s\t", sStr);
    for (int i = 9; i <= 36; i = i + 9)
    {
        
        if (toBaseN(sVal, i)){
            printf("%s\t", toBaseN(sVal, i));
        }
        else{
            return ERROR_MALLOC;
        }
    }
    
    for (int i = 0; i < cnt; i++)
    {
        free(strings[i]);
    }
    free(strings);
    return SUCCESS;
}

//Считывание чисел
char** input(int num_sys, int* cnt, int* ret){
    int memo = 4;
    char** strings = (char**)malloc(sizeof(char*)*memo);
    if (strings == NULL){
        return NULL;
    }

    char* buffer = (char*)malloc(sizeof(char*)*memo);
    if (buffer == NULL){
        return NULL;
    }

    buffer[0] = '\0';
    char c;
    int memoN = memo, iter = 0;
    while(strcmp(buffer, "Stop\n")){

        while ((c = fgetc(stdin)) != '\n'){
            if (iter > memoN){
                memoN *= 2;
                buffer = (char*)realloc(buffer, memoN);
                buffer[iter] = c;
                iter++;
            }
            else{
                buffer[iter] = c;
                iter++;
            }
        }
        buffer[iter] = '\n';
        buffer[iter+1] = '\0';
        iter = 0;

        if(!checkNumber(buffer)){
            for (int i = 0; i < *cnt; i++)
            {
                if(strings[i] != NULL){
                    free(strings[i]);
                }
            }
            *ret = ERROR_NAN;
            free(strings);
            return SUCCESS;
        }
        if(!strcmp(buffer, "Stop\n")){
            break;
        }
        else if(strcmp(buffer, "Stop\n") && checkBase(buffer, (int)strlen(buffer), num_sys)){
            for (int i = 0; i < *cnt; i++)
            {
                if(strings[i] != NULL){
                    free(strings[i]);
                }
            }
            free(strings);
            *ret = ERROR_BASE_NUMBER;
            return SUCCESS;
        }

        char* str = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
        if (str == NULL){
            return NULL;
        }

        strcpy(str, buffer);

        if(str == NULL){
            for (int i = 0; i < *cnt; i++)
            {
                if(strings[i] != NULL){
                    free(strings[i]);
                }
            }
            free(strings);
            *ret = ERROR_MALLOC;
            return SUCCESS;
        }
        strings[(*cnt)++] = str;
        if(*cnt == memo){
            memo *= 2;
            char** strings_new = (char**)realloc(strings, memo);
            if(strings_new == NULL){
                for (int i = 0; i < *cnt; i++)
                {
                    if(strings[i] != NULL){
                        free(strings[i]);
                    }
                }
                free(strings);
                *ret = ERROR_MALLOC;
                return SUCCESS;
            }
            strings = strings_new;
        }
    }
    return strings;
}
