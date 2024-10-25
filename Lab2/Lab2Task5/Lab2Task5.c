#include "functions.h"

int main() {
	char* result;
	FILE* out = fopen("out.txt", "w");
	if (out == NULL){
		logErrors(ERROR_OPEN_FILE);
		return ERROR_OPEN_FILE;
	}
	int code = overfprintf(out, "%Ro i hate people", 2024);
	if (code != SUCCESS){
		logErrors(code);
		return code;
	}
    //printf(result);
	return 0;
}