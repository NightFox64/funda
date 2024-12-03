#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum ret_type_t{
    SUCCESS,    //Успех
    ERROR_NAN,   //Не является числом
    ERROR_FULL,  //Переполнение
    ERROR_ARGS,  //Ошибка при вводе аргументов
    ERROR_MALLOC,    //Ошибка выделения памяти
};

//Check if input seems correct
int checkInput(int argc, char *argv[])
{
    if (argc < 3 || argv[1][0] != '-' || argv[1][2] != '\0')
        return ERROR_ARGS;
    return SUCCESS;
}

//The most powerful function to size strings
size_t demidovStrlen(const char* str) {
    if (str != NULL){
        const char* buf = str;
        size_t length = 0;
        while (*buf++) {
            length++;
        }
        return length;
    }
    return 0;
}

//The most powerful string concatination function
char* demidovStrcat(char* str1, const char* str2) {
    size_t len1 = demidovStrlen(str1);
    size_t len2 = demidovStrlen(str2);

    for (size_t j = 0; j < len2; j++) {
        str1[len1 + j] = str2[j];
    }

    str1[len1 + len2] = '\0';

    return str1;
}

//The most powerful function to create a reversed string
int demidovReverse(char *reversed, const char* str) {
    size_t len = demidovStrlen(str);

    for (size_t i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';
    return SUCCESS;
}

//The name says for itself
int raiseOddPos(char* result, const char* str) {
    for (size_t i = 0; i < demidovStrlen(str); i++) {
        if (i % 2 != 0) {
            result[i] = toupper((unsigned char)str[i]);
        } else {
            result[i] = str[i];
        }
    }
    result[demidovStrlen(str)] = '\0';
    return SUCCESS;
}

//Digits first, letters second and everythin else in the end
int changeOrder(char* res, const char* str) {
    res[0] = '\0';
    char* digits = malloc((demidovStrlen(str) + 1) * sizeof(char*));
    if (digits == NULL){
        return ERROR_MALLOC;
    }
    char* letters = malloc((demidovStrlen(str) + 1) * sizeof(char*));
    if (letters == NULL){
        free(digits);
        return ERROR_MALLOC;
    }
    char* others = malloc((demidovStrlen(str) + 1) * sizeof(char*));
    if (others == NULL){
        free(digits);
        free(letters);
        return ERROR_MALLOC;
    }

    size_t d = 0, l = 0, o = 0;
    for (size_t i = 0; i < demidovStrlen(str); i++) {
        if ((isdigit(str[i]))) {
            digits[d] = str[i];
            d++;
        } else if (isalpha(str[i])) {
            letters[l] = str[i];
            l++;
        } else {
            others[o] = str[i];
            o++;
        }
    }

    digits[d] = '\0';
    letters[l] = '\0';
    others[o] = '\0';

    demidovStrcat(res, digits);
    demidovStrcat(res, letters);
    demidovStrcat(res, others);
    
    res[demidovStrlen(str)] = '\0';

    free(digits);
    free(letters);
    free(others);

    return SUCCESS;
}

//You give args with seed and this func will concat your args randomly
int randomStrcat(int count, char* strings[], char* result) {
    result[0] = '\0';

    unsigned int seed = (unsigned int)atoi(strings[3]);
    int tmp = count - 3;

    char* used = (char*)malloc(tmp * sizeof(char*));
    if (used == NULL){
        return ERROR_MALLOC;
    }

    srand(seed);

    while (tmp){
        int randN = rand() % (count - 3) + 3;
        if (used[randN] != ' '){
            demidovStrcat(result, strings[randN]);
            used[randN] = ' ';
            tmp--;
        }
    }
}

//Check number or not
int checkNumber(const char *str) {
    if (*str == '-') {
        str++;
    }

    int hasDot = 0;
    if (*str == '\0'){
        return 0;
    }

    while (*str) {
        if (*str == '.') {
            if (hasDot){
                return 0;
            }
            hasDot = 1;
        } else if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}