#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>

enum ret_type_t{
    SUCCESS,    //Успех
    ERROR_NAN,   //Не является числом
    ERROR_FULL,  //Переполнение
    ERROR_ARGS,  //Ошибка при вводе аргументов
    ERROR_MALLOC,    //Ошибка выделения памяти
    ERROR_NEGATIVE, //Корень из отрицательного. Думай
};

// Функция для вычисления среднего геометрического
double geometricSum(int count, ...) {
    va_list args;
    va_start(args, count);

    double result = 1.0;
    for (int i = 0; i < count; i++) {

        double num = va_arg(args, double);

        if (num < 0.0){
            return -2;
        }

        result *= pow(num, 1.0 / count);

        if (result > DBL_MAX || result < -DBL_MAX) {
			return -1;
		}
    }

    va_end(args);

    return result;
}

// Рекурсивная функция для возведения числа в степень
double fastPower(double base, int exp, int* error) {

    if (*error) {
		return 0.0;
	}

    if (exp == 0) {
		return 1.0;
	}

	if (exp < 0) {
		return 1.0 / fastPower(base, -exp, error);
	}

	long double half = fastPower(base, exp / 2, error);

	if (fabs(half) > (DBL_MAX)) {
		*error = ERROR_FULL;
		return 0.0;
	}

	long double result = half * half;

	if (exp % 2 != 0) {
		if (fabs(half) > DBL_MAX) {
			*error = ERROR_FULL;
			return 0.0;
		}
		result *= base;
	}

	return result;
}