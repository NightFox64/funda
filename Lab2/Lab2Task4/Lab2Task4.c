#include "functions.h"

int main() {
	double res;
	int code = calculatePolynom(&res, 10.0, 4.0, 1.0, 1.0, 1.0, 1.0, 1.0);
	if (code != SUCCESS) {
        logErrors(code);
		return code;
	}
	printf("%lf\n", res);

	int resultB = isConvexPolygon(5, 0.0, 0.0, 0.0, 5.0, 5.0, 5.0, 2.0, 2.0, 5.0, 0.0, 3.0, 2.0);
	if (resultB) {
		printf("convex\n");
	} else {
		printf("not convex\n");
	}

	code = SUCCESS;
	int n = 2;
	int* result = findKaprekarNumbers(&code, 10, n, "01", "9");
	if (code != SUCCESS) {
        logErrors(code);
		return code;
	}
    
	for (int i = 0; i < (n); i++) {
		printf("%d\n", result[i]);
	}

	free(result);

	return SUCCESS;
}