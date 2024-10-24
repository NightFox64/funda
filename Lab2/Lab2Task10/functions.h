#include "errors.h"

// возвращает значение i-й производной в точке(а), n - порядок многочлена
double derivative(int i, double a, int n, const double *coeffs) {
    double result = 0.0;

    for (int j = i; j <= n; j++) {
        double term = coeffs[j];
        for (int k = 0; k < i; k++) {
            term *= (j - k);
        }
        result += term * pow(a, j - i);
    }
    return result;
}

int decomposePolynomial(double eps, double a, double *result, int n, ...) {
    if ((eps < 0) || (result == NULL)){
        return ERROR_ARGS;
    }

    va_list args;
    va_start(args, n);

    double *coeffs = (double*)malloc((n + 1) * sizeof(double));
    if (coeffs == NULL) {
        return ERROR_MALLOC;
    }

    for (int i = 0; i <= n; i++) {
        coeffs[i] = va_arg(args, double);
    }
    va_end(args);

    unsigned long long int fact = 1;
    for (int i = 0; i <= n; i++) {
        if (i != 0) {
            fact *= i;
        }
        result[i] = derivative(i, a, n, coeffs) / (double)fact;
        
        if (fabs(result[i]) < eps) {
            result[i] = 0.0;
        }
    }

    free(coeffs);
    return SUCCESS;
}
