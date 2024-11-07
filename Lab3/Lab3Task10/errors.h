#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

enum ret_type_t{
    SUCCESS,    //Успех
    ERROR_NAN,   //Не является числом
    ERROR_FULL,  //Переполнение
    ERROR_ARGS,  //Ошибка при вводе аргументов
    ERROR_MALLOC,    //Ошибка выделения памяти
    ERROR_OPEN_FILE,    //Не удалось открыть файл
    ERROR_ITERATIONS_LIMIT, //Слишком много итераций вышло, закругляйся
    ERROR_NO_SOLVE, //В заданном интервале нет корня
	ERROR_SAME_FILES,	//Obvious
};

void logErrors(int code) {
	switch (code) {
		case ERROR_NAN:
			printf("Found not a number\n");
			break;

		case ERROR_FULL:
			printf("Overflow detected\n");
			break;

		case ERROR_ARGS:
			printf("Wrong arguments\n");
			break;
			
		case ERROR_MALLOC:
			printf("Failed to malloc\n");
			break;

		case ERROR_OPEN_FILE:
			printf("Failed to open file\n");
			break;

        case ERROR_ITERATIONS_LIMIT:
            printf("Too many iterations. Time to shut up\n");
            break;

        case ERROR_NO_SOLVE:
            printf("There is no solvement in your interval\n");
            break;

		case ERROR_SAME_FILES:
            printf("Same files\n");
            break;

		default:
			printf("UNKNOWN ERROR CODE\n");
			break;
	}
}