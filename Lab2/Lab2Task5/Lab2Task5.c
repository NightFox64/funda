#include "functions.h"

int main() {
	char* result;
	FILE* out = fopen("out.txt", "w");
	if (out == NULL){
		logErrors(ERROR_OPEN_FILE);
		return ERROR_OPEN_FILE;
	}
	int code = overfprintf(stdout, "%Ro %Zr %mi", 2024, 55, 16);
	if (code != SUCCESS){
		logErrors(code);
		return code;
	}
    //printf(result);
	return 0;
}