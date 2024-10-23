#include <stdio.h>
#include <stdlib.h>

enum ret_type_t{
    SUCCESS,    //Успех
    ERROR_NAN,   //Не является числом
    ERROR_FULL,  //Переполнение
    ERROR_ARGS,  //Ошибка при вводе аргументов
    ERROR_MALLOC,    //Ошибка выделения памяти
    ERROR_OPEN_FILE,    //Не удалось открыть файл
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
			printf("Wrong number of arguments\n");
			break;
			
		case ERROR_MALLOC:
			printf("Failed to malloc\n");
			break;

		case ERROR_OPEN_FILE:
			printf("Failed to open file\n");
			break;

		default:
			printf("UNKNOWN ERROR CODE\n");
			break;
	}
}