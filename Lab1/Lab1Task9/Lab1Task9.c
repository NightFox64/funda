#include "functions.h"

int main(int argc, char *argv[]){

    if (argc != 3){
        printf("Wrong number of arguments");
        return ERROR_ARGS;
    }

    if (checkNumber(argv[1]) || checkNumber(argv[2])){
        printf("There must be a natural number");
        return ERROR_NAN;
    }

    if ((chToInt(argv[1]) == ERROR_FULL) && ((int)strlen(argv[1]) > 3)){
        printf("Your number is too big");
        return ERROR_FULL;
    }
    if ((chToInt(argv[2]) == ERROR_FULL) && ((int)strlen(argv[2]) > 3)){
        printf("Your number is too big");
        return ERROR_FULL;
    }

    int a = chToInt(argv[1]);
    int b = chToInt(argv[2]);
    int flagStatic = 0;
    printf("a=%d, b=%d\n", a, b);
    srand(time(NULL)); 

    if (b <= a){
        printf("The array has a negative or zero length. The second number must be bigger\n");
        flagStatic = 1;
    }

    if (!flagStatic){
        int array[STATIC_SIZE];
        
        printf("The static massive before change: ");
        for (int i = 0; i < STATIC_SIZE; i++){
            array[i] = rand() % abs(b - a + 1) + a;
            printf("%d ", array[i]);
        }

        printf("\n");
        firstTask(array, a, b);

        printf("The static massive after change:  ");
        for (int i = 0; i < STATIC_SIZE; i++){
            printf("%d ", array[i]);
        }
        printf("\n\n");
    }

    //int sizeA = rand() % (10000 - 9) + 10;
    //int sizeB = rand() % (10000 - 9) + 10;
    int sizeA = STATIC_SIZE, sizeB = STATIC_SIZE;

    int* arrA = (int*)malloc(sizeof(int)*sizeA);
    int* arrB = (int*)malloc(sizeof(int)*sizeB);

    if (arrA == NULL){
        return ERROR_MALLOC;
    }
    if (arrB == NULL){
        free(arrA);
        return ERROR_MALLOC;
    }

    fillRandom(arrA, sizeA);
    printf("The dynamic array A: ");
    for (int i = 0; i < sizeA; i++){
        printf("%d ", arrA[i]);
    }
    printf("\n");
    fillRandom(arrB, sizeB);
    printf("The dynamic array B: ");
    for (int i = 0; i < sizeB; i++){
        printf("%d ", arrB[i]);
    }
    printf("\n");

    int* arrC = (int*)malloc(sizeof(int)*sizeA);
    if(arrC == NULL){
        free(arrA);
        free(arrB);
        return ERROR_MALLOC;
    }

    secondTask(arrA, sizeA, arrB, sizeB, arrC);

    printf("The dynamic array C: ");
    for (int i = 0; i < sizeA; i++){
        printf("%d ", arrC[i]);
    }
    printf("\n");

    free(arrA);
    free(arrB);
    free(arrC);

    return SUCCESS;
}
