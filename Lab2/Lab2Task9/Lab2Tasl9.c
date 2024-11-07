#include "functions.h"

int main() {
	int code = SUCCESS;
    int n = 2;
	bool* result = checkFractions(&code, 2, n, 10.2, 0.5);
    for (int i = 0; i < n; i++){
        printf("%d\n", result[i]);
    }
	return 0;
}