#include "functions.h"

int main() {
    int n = 2;
    double epsilon = 0.00001;
    double a = 1.0;
    double* result = (double*)malloc(sizeof(double) * (n + 1));
    if (result == NULL){
        logErrors(ERROR_MALLOC);
        return ERROR_MALLOC;
    }

    int code = decomposePolynomial(epsilon, a, result, n, 5.0, 2.0, 10.0);
    if (code != SUCCESS) {
        logErrors(code);
        return code;
    }

    for (int i = 0; i <= n; i++) {
        printf("g%d = %f\n", i, result[i]);
    }

    return 0;
}