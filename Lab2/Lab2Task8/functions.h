#include "errors.h"

int charToValue(char c) {
	if (c >= '0' && c <= '9') {
        return c - '0';
    }
	if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    } 
	if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    } 
	return -1;
}

char valueToChar(int value) {
	if (value >= 0 && value <= 9) {
        return '0' + value;
    }
	if (value >= 10 && value <= 35) {
        return 'A' + (value - 10);
    } 
	return '?';
}

int baseToDigits(char *numberStr, int base, uint8_t* digits) {
	if (numberStr == NULL || base < 2 || base > 36) {
		return ERROR_ARGS;
	}

	int len = strlen(numberStr);
	memset(digits, 0, MAX_DIGITS * sizeof(uint8_t));

	for (int i = 0; i < len; i++) {
		int value = charToValue(numberStr[i]);
		if (value >= base || value < 0) {
			return ERROR_ARGS;
		}

		int carry = value;
		for (int j = 0; j < MAX_DIGITS; j++) {
			carry += digits[j] * base;
			digits[j] = carry % base;
			carry /= base;
		}
	}

	return SUCCESS;
}

int addLargeNumbers(uint8_t* result, uint8_t* num1, uint8_t* num2, int base) {
	int carry = 0;
	for (int i = 0; i < MAX_DIGITS; i++) {
		int sum = num1[i] + num2[i] + carry;
		result[i] = sum % base;
		carry = sum / base;
	}

	return SUCCESS;
}

void printLargeNumber(uint8_t* digits, int base) {
	int i = MAX_DIGITS - 1;
	while (i >= 0 && digits[i] == 0) {
		i--;
	}

	if (i == -1) {
		printf("0");
	} else {
		for (; i >= 0; i--) {
			printf("%c", valueToChar(digits[i]));
		}
	}
	printf("\n");
}

int sumBigNumbers(uint8_t* sum, int base, int count, ...) {
	if (base < 2 || base > 36) {
        return ERROR_MALLOC;
	}

	va_list args;
	va_start(args, count);
    int memo = 2;

	if (sum == NULL) {
		return ERROR_MALLOC;
	}
	memset(sum, 0, MAX_DIGITS * sizeof(uint8_t));

	for (int i = 0; i < count; i++) {
		char* numberStr = va_arg(args, char*);

		uint8_t* currentNumber = (uint8_t*)malloc(MAX_DIGITS * sizeof(uint8_t));
		if (currentNumber == NULL) {
			free(sum);
			return ERROR_MALLOC;
		}

		int state = baseToDigits(numberStr, base, currentNumber);
		if (state != SUCCESS) {
			free(currentNumber);
			free(sum);
			return state;
		}

		state = addLargeNumbers(sum, sum, currentNumber, base);
		free(currentNumber);
		if (state != SUCCESS) {
			free(sum);
			return state;
		}
	}

	va_end(args);

	return SUCCESS;
}