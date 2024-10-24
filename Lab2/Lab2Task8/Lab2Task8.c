#include "functions.h"

int main() {
    uint8_t* sum;
    sum = (uint8_t *)malloc(MAX_DIGITS * sizeof(uint8_t));
	int code;
    int base = 2;

    code = sumBigNumbers(sum, base, 3, "101", "110", "11");
	if (code != SUCCESS) {
		logErrors(code);
        return code;
	}

    printf("Sum: ");
	printLargeNumber(sum, base);
	free(sum);
	return 0;
}