#define STATIC_SIZE 10

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

enum ret_type_t{
    SUCCESS,    //Успех
    ERROR_NAN,   //Не является числом
    ERROR_FULL,  //Переполнение
    ERROR_ARGS,  //Количество аргументов неверное
    ERROR_ZERO_LENGTH,   //Массив на 0 элементов
    ERROR_MALLOC    //Ошибка выделения памяти
};

//Перевод из строкового представления в int-овое
int chToInt(char* x){
    int xInt = 0;
    int m = 1;
    int mBuf = 1;
    int minFlag = 1;

    for (int i = strlen(x) - 1; i >= 0; --i){
        if (x[i] == '-'){
            minFlag = -1;
        }
        else{
            xInt += (x[i] - '0') * m;
            m *= 10;
            if (mBuf > m){
                return ERROR_FULL;
            }
            mBuf *= 10;
        }
        
    }
    return minFlag * xInt;
}

//Проверяет является ли строковое представление вещественным числом
int checkNumber(char* x){
    int flagDot = 0, flagMin = 0;
    for (int i = 0; i < (int)strlen(x); i++){
        if ((x[i] < '0' || x[i] > '9') && (x[i] != '.') && (x[i] != '-')){
            return ERROR_NAN;
        }
        if (x[i] == '.'){
            flagDot++;
            if (flagDot > 1){
                return ERROR_NAN;
            }
        }
        if (x[i] == '-'){
            flagMin++;
            if (flagMin > 1){
                return ERROR_NAN;
            }
        }
    }
    return SUCCESS;
}

//Выполняет первое условие заддания
int* firstTask(int array[STATIC_SIZE], int a, int b){
    srand (time(NULL)); 
    int valMax = array[0], idMax = 0, valMin = array[0], idMin = 0;
    for (int i = 1; i < STATIC_SIZE; i++)
    {
        if (valMin > array[i]){
            valMin = array[i];
            idMin = i;
        }
        if (valMax < array[i]){
            valMax = array[i];
            idMax = i;
        }
    }
    int buf = valMax;
    array[idMax] = valMin;
    array[idMin] = buf;

    return array;
}

//Правило для сравнения
int compare(const void* a, const void* b){
    int d1 = *(int*)a;
    int d2 = *(int*)b;
    if(d1 < d2){
        return -1;
    }
    else if(d1 == d2){
        return 0;
    }
    else{
        return 1;
    }
}

//Угадайте, что это
int binSearch(int* arr, int size, int val){
    int start = 0, end = size - 1, mid = (start + end) / 2;
    while (start <= end){
        mid = (start + end) / 2;
        if (val == arr[mid]){
            return mid;
        }
        if (val < arr[mid]){
            end = mid - 1;
        }
        else{
            start = mid + 1;
        }
    }
    return mid;
}

//int linSearch(int* array, int size, int val){
//    for (int i = 1; i < size; i++) {
//        if (array[i] > val){
//            return i-1;
//        }
//    }
//    return (size-1);
//}

//Функция для заполнения и вывода динамического массива
int fillRandom(int* arr, int size){
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 2001 - 1000;
    }
    return SUCCESS;
}

//Функция для заполнения третьего массива
int secondTask(int* arrA, int sizeA, int* arrB, int sizeB, int* arrC){

    qsort(arrB, sizeB, sizeof(int), compare);

    for (int i = 0; i < sizeA; i++)
    {
        arrC[i] = arrA[i] + arrB[binSearch(arrB, sizeB, arrA[i])];
    }

    return SUCCESS;
}