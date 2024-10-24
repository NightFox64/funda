#include "functions.h"

int main() {
	int code = SUCCESS;
    int n = 5;
	bool* result = checkFractions(&code, 2, n, -(1.0 / 3.0), 1.0 / 6.0, 1.0 / 9.0, 9734.0 / 9735.0, 0.2);
    for (int i = 0; i < n; i++){
        printf("%d\n", result[i]);
    }
	return 0;
}