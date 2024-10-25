#include "functions.h"

int main() {
	char* result;
	int code = oversprintf(result, "%mf i hate people", 10.0);
	if (code != SUCCESS){
		logErrors(code);
		return code;
	}
    printf(result);
	return 0;
}