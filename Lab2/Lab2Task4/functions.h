#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"

int getRotateDirection(double ax, double ay, double bx, double by, double cx, double cy) {
    double abx = bx - ax;
    double aby = by - ay;
    double bcx = cx - bx;
    double bcy = cy - by;
    double prod = abx * bcy - aby * bcx;
    if (prod > 0.0) {
        return 1;
    } else if (prod < 0.0) {
        return -1;
    }
    return 0;
}

int isConvexPolygon(int numPoints, ...) {
    if (numPoints < 3) {
        return 0;
    }

    va_list args;
    va_start(args, numPoints);

    double x1, y1, x2, y2, x3, y3, firstX, firstY, secondX, secondY;

    x1 = firstX = va_arg(args, double);
    y1 = firstY = va_arg(args, double);
    x2 = secondX = va_arg(args, double);
    y2 = secondY = va_arg(args, double);
    x3 = va_arg(args, double);
    y3 = va_arg(args, double);

    int currentDirection = getRotateDirection(x1, y1, x2, y2, x3, y3);

    for (int i = 3; i < numPoints; i++) {
        x1 = x2;
        x2 = x3;
        y1 = y2;
        y2 = y3;
        x3 = va_arg(args, double);
        y3 = va_arg(args, double);
        int dir = getRotateDirection(x1, y1, x2, y2, x3, y3);

        if (dir == 0) {
            continue;
        }
        if (dir != currentDirection) {
            va_end(args);
            return 0;
        }
    }
    va_end(args);

    return getRotateDirection(x2, y2, x3, y3, firstX, firstY) == currentDirection &&
           getRotateDirection(x3, y3, firstX, firstY, secondX, secondY) == currentDirection;
}

int calculatePolynom(double *result, double x, int n, ...) {
    va_list args;
    va_start(args, n);
    double current = 0.0;
    for (int i = 0; i <= n; i++) {
        double k = va_arg(args, double);
        current *= x;
        if (current > DBL_MAX || current < -DBL_MAX) {
            va_end(args);
            return ERROR_FULL;
        }
        current += k;
        if (current > DBL_MAX || current < -DBL_MAX) {
            va_end(args);
            return ERROR_FULL;
        }
    }
    va_end(args);
    *result = current;
    return SUCCESS;
}

int parseToDecimal(const char *str, int base, int *code) {
    int num = 0;
    while (*str) {
        char digit = *str++;
        int value;

        if (digit >= '0' && digit <= '9') {
            value = digit - '0';
        } else if (digit >= 'A' && digit <= 'Z') {
            value = digit - 'A' + 10;
        } else if (digit >= 'a' && digit <= 'z') {
            value = digit - 'a' + 10;
        } else {
            *code = ERROR_NAN;
            return -1;
        }

        if (value >= base) {
            *code = ERROR_NAN;
            return -1;
        }

        int numBuf = num * base + value;
        if (numBuf < num) {
            *code = ERROR_FULL;
            return -1;
        }
        num = numBuf;
    }
    *code = SUCCESS;
    return num;
}

int convertFromDecimal(int num, int base, char *result) {
    char *buffer = (char *)malloc(sizeof(char) * 2);
    if (buffer == NULL) {
        return ERROR_MALLOC;
    }

    int memo = 2;
    int index = 0;

    while (num > 0) {
        int remain = num % base;
        if (index >= memo) {
            memo *= 2;
            char *newBuffer = (char *)realloc(buffer, sizeof(char) * memo);
            if (newBuffer == NULL) {
                free(buffer);
                return ERROR_MALLOC;
            }
            buffer = newBuffer;
        }
        buffer[index++] = (remain < 10) ? (remain + '0') : (remain - 10 + 'A');
        num /= base;
    }

    for (int i = 0; i < index; i++) {
        result[i] = buffer[index - i - 1];
    }
    result[index] = '\0';
    free(buffer);
    return SUCCESS;
}

char *substring(const char *str, int index, int *code) {
    if (index < 0 || index > (int)strlen(str)) {
        *code = ERROR_FULL;
        return NULL;
    }

    char *result = (char *)malloc((index + 1) * sizeof(char));
    if (result == NULL) {
        *code = ERROR_MALLOC;
        return NULL;
    }

    strncpy(result, str, index);
    result[index] = '\0';

    *code = SUCCESS;
    return result;
}

int isKaprekar(int num, int base, int *code) {
    if (num == 1) {
        return 1;
    }

    int square = num * num;
    char *squareStr = (char *)malloc(sizeof(char) * (CHAR_BIT * sizeof(int) + 1));
    if (squareStr == NULL) {
        *code = ERROR_MALLOC;
        return 0;
    }
    if (convertFromDecimal(square, base, squareStr) != SUCCESS) {
        free(squareStr);
        return 0;
    }

    int len = (int)strlen(squareStr);
    for (int i = 1; i < len; i++) {
        char *leftSubstr = substring(squareStr, i, code);
        if (*code != SUCCESS) {
            free(squareStr);
            return 0;
        }
        int left = parseToDecimal(leftSubstr, base, code);
        free(leftSubstr);
        if (*code != SUCCESS) {
            free(squareStr);
            return 0;
        }
        int right = parseToDecimal(squareStr + i, base, code);
        if (*code != SUCCESS) {
            free(squareStr);
            return 0;
        }
        if (right > 0 && left + right == num) {
            free(squareStr);
            return 1;
        }
    }
    free(squareStr);
    return 0;
}

int *findKaprekarNumbers(int *code, int base, int numArgs, ...) {
    *code = SUCCESS;
    va_list args;
    va_start(args, numArgs);
    int *kaprekars = (int *)malloc(sizeof(int) * numArgs);
    if (!kaprekars) {
        *code = ERROR_MALLOC;
        va_end(args);
        return NULL;
    }

    for (int i = 0; i < numArgs; i++) {
        const char *strNum = va_arg(args, const char *);
        int decimalNum = parseToDecimal(strNum, base, code);
        if (*code != SUCCESS) {
            free(kaprekars);
            va_end(args);
            return NULL;
        }
        kaprekars[i] = isKaprekar(decimalNum, base, code);
        if (*code != SUCCESS) {
            free(kaprekars);
            va_end(args);
            return NULL;
        }
    }

    va_end(args);
    return kaprekars;
}
