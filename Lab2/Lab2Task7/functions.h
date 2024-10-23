#include "errors.h"

#define ITERATION_LIMIT 10000000

typedef double (*uravn)(double);

double solveDichotomy(double a, double b, uravn f, double eps, int* code) {
	if (f(a) * f(b) >= 0.0) {
		*code = ERROR_NO_SOLVE;
		return 0.0;
	}
	*code = SUCCESS;
	double c;
	int n = 0;
	while ((b - a) / 2 > eps) {
		if (n > ITERATION_LIMIT) {
			*code = ERROR_ITERATIONS_LIMIT;
			return 0.0;
		}
		c = (a + b) / 2;
		if (f(a) * f(c) > 0) {
			a = c;
		} else {
			b = c;
		}
		n++;
	}
	return c;
}