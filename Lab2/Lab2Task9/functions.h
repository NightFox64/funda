#include "errors.h"

//НОД
int gcd(int a, int b) {
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

//Алгоритм для нахождения простых чисел всех до n
void sieveOfEratosthenes(bool* primes, int n, int base) {
	for (int i = 0; i <= n; i++) {
		primes[i] = true;
	}
	primes[0] = primes[1] = false;
	for (int p = 2; p * p <= n; p++) {
		if (primes[p]) {
			for (int i = p * p; i <= n; i += p) {
				primes[i] = false;
			}
		}
	}
}

bool checkFraction(int numerator, int denominator, int base) {
	bool* isPrime = (bool*)malloc(sizeof(bool) * (denominator + 1));
	sieveOfEratosthenes(isPrime, denominator, base);
	for (int i = 2; i <= denominator; i++) {
		if (denominator % i == 0 && isPrime[i]) {
			if (base % i != 0) {
				return false;
			}
		}
	}
	return true;
}

void doubleToFraction(double value, int* numerator, int* denominator, double tolerance) {
	double fractionalPart = value;
	int previousNumerator = 0, currentNumerator = 1;
	int previousDenominator = 1, currentDenominator = 0;
	double quotient;

	while (fabs(value - (double)currentNumerator / (double)currentDenominator) > tolerance) {
		quotient = floor(fractionalPart);
		double tempNumerator = currentNumerator;
		double tempDenominator = currentDenominator;

		currentNumerator = quotient * currentNumerator + previousNumerator;
		currentDenominator = quotient * currentDenominator + previousDenominator;

		if (currentNumerator > INT_MAX || currentDenominator > INT_MAX) {
			break;
		}

		previousNumerator = tempNumerator;
		previousDenominator = tempDenominator;

		if (fractionalPart == quotient) {
			break;
		}

		fractionalPart = 1.0 / (fractionalPart - quotient);
	}

	*numerator = currentNumerator;
	*denominator = currentDenominator;

	int commonDivisor = gcd(*numerator, *denominator);
	*numerator /= commonDivisor;
	*denominator /= commonDivisor;
}

bool* checkFractions(int* code, int base, int fractionsNum, ...) {
	if (base < 2 || base > 36) {
		*code = ERROR_ARGS;
		return NULL;
	}

	bool* result = malloc(sizeof(bool) * fractionsNum);
	if (!result) {
		*code = ERROR_MALLOC;
		return NULL;
	}

	double eps = 0.000001;

	va_list args;
	va_start(args, fractionsNum);
	for (int i = 0; i < fractionsNum; i++) {
		double fraction = fabs(va_arg(args, double));
		if (fraction > 1.0 + eps) {
			*code = ERROR_ARGS;
		}
		int numerator, denominator;
		doubleToFraction(fraction, &numerator, &denominator, 0.000001);
		int divisor = gcd(numerator, denominator);
		numerator /= divisor;
		denominator /= divisor;
		result[i] = checkFraction(numerator, denominator, base);
	}
	va_end(args);

    return result;
}