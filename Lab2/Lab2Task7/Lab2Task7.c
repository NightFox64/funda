#include <math.h>

#include "functions.h"

double func1(double x) { 
    return (x-1)*(x-1)/(x-1); 
}

int main() {
	int code = SUCCESS;
	double result = solveDichotomy(-5.0, 5.0, func1, 0.00000000001, &code);
	if (code != SUCCESS) {
		logErrors(code);
		return code;
	}
	printf("%lf\n", result);
	return SUCCESS;
}