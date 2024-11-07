#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>


typedef enum {
    kOptA,
    kOptD
} kOption;

typedef enum {
    SUCCESS,    //Успех
    ERROR_NAN,   //Не является числом
    ERROR_FULL,  //Переполнение
    ERROR_ARGS,  //Ошибка при вводе аргументов
    ERROR_MALLOC,    //Ошибка выделения памяти
    ERROR_OPEN_FILE,    //Не удалось открыть файл
    ERROR_ITERATIONS_LIMIT, //Слишком много итераций вышло, закругляйся
	ERROR_SAME_FILES,	//Попытка перезаписать входной файл
    ERROR_UNKNOWN_FLAG, //Неизвестный флаг
    ERROR_PARSING,      //Failed to parse data
    ERROR_VALIDATE_EMPLOYEE,    //Obvious
    ERROR_SAME_IDS,             //You entered same ID with different info
} kState;

typedef struct {
    kState State;
    kOption Option;
    char *InputPath;
    char *OutputPath;
} Args;

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

        case ERROR_UNKNOWN_FLAG:
            printf("This flag doesn't exist. Put flag and then two paths\n");
            break;

        case ERROR_SAME_FILES:
            printf("You put same files. Put flag and then two paths\n");
            break;

        case ERROR_VALIDATE_EMPLOYEE:
            printf("You put very strange data in the file...\n");
            break;

        case ERROR_PARSING:
            printf("Failed to parese data\n");
            break;

        case ERROR_SAME_IDS:
            printf("You entered same IDs with different info\n");
            break;

		default:
			printf("UNKNOWN ERROR CODE\n");
			break;
	}
}

bool fileExists(char *path) {
    FILE *input = fopen(path, "r");
    if (!input) {
        return false;
    }
    fclose(input);
    return true;
}

//bool sameFile(char *input, char *output) {
//    char* resbuf1 = (char*)malloc(sizeof(char) * MAX_PATH);
//    if (resbuf1 == NULL){
//        return true;
//    }
//    DWORD res1 = GetFullPathName(input, MAX_PATH, resbuf1, &resbuf1);
//    char* resbuf2 = (char*)malloc(sizeof(char) * MAX_PATH);
//    if (resbuf2 == NULL){
//        free(resbuf1);
//        return true;
//    }
//    DWORD res2 = GetFullPathName(output, MAX_PATH, resbuf2, &resbuf2);
//    if (res1 != 0 && res2 != 0) {
//        if (!strcmp(resbuf1, resbuf2)){
//            return true;
//        }
//    }
//    return false;
//}

bool sameFile(const char *path1, const char *path2) {
    struct stat stat1, stat2;
    stat(path1, &stat1);
    stat(path2, &stat2);
    if (stat1.st_ino == stat2.st_ino && stat1.st_dev == stat2.st_dev) {
        return true;
    }
    return false;
}

Args *ParseArgs(int argc, char **argv) {
    Args *result = (Args*)malloc(sizeof(Args));
    if (!result) {
        return result;
    }
    result->State = SUCCESS;

    if (argc < 4 || argc > 4) {
        result->State = ERROR_ARGS;
        return result;
    }

    char *flag = argv[1];
    if (flag[0] != '-' && flag[0] != '/') {
        result->State = ERROR_UNKNOWN_FLAG;
        return result;
    }

    if (flag[1] == 'd') {
        result->Option = kOptD;
    } else if (flag[1] == 'a') {
        result->Option = kOptA;
    } else {
        result->State = ERROR_UNKNOWN_FLAG;
        return result;
    }

    result->InputPath = argv[2];
    if (!fileExists(result->InputPath)) {
        result->State = ERROR_OPEN_FILE;
        return result;
    }
    result->OutputPath = argv[3];
    if (sameFile(result->InputPath, result->OutputPath)) {
        result->State = ERROR_SAME_FILES;
    }

    return result;
}