#include "functions.h"

int main() {
	int code = SUCCESS;
    int n = 2;
	bool* result = checkFractions(&code, 2, n, 0.5, 10.2);
    if (code != SUCCESS) {
        logErrors(code);
        return code;
    }
    for (int i = 0; i < n; i++){
        printf("%d\n", result[i]);
    }
	return 0;
}