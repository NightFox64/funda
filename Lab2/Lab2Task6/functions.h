#include "errors.h"

int roman_to_int(const char *roman) {
    struct Roman {
        int value;
        const char *symbol;
    } roman_map[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };

    int result = 0, i = 0;
    while (*roman) {
        if (strncmp(roman, roman_map[i].symbol, strlen(roman_map[i].symbol)) == 0) {
            result += roman_map[i].value;
            roman += strlen(roman_map[i].symbol);
        } else {
            i++;
        }
    }
    return result;
}

unsigned int fib_zec_to_int(const char *fib_zec) {
    unsigned int fib[64], i = 0;
    fib[0] = 1; fib[1] = 2;
    for (i = 2; i < 64; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    unsigned int num = 0, index = 0;
    size_t len = strlen(fib_zec);

    for (int j = len - 2; j >= 0; j--) {
        if (fib_zec[j] == '1') {
            num += fib[index];
        }
        index++;
    }
    return num;
}

int base_to_decimal(const char *num_str, int base) {
    int result = 0;
    int is_negative = (*num_str == '-');
    if (is_negative) num_str++;

    while (*num_str) {
        char c = tolower(*num_str);
        int value = (c >= '0' && c <= '9') ? c - '0' : c - 'a' + 10;
        result = result * base + value;
        num_str++;
    }
    return is_negative ? -result : result;
}

int overfscanf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    int total_read = 0;

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'R':
                    format++;
                    if (*format == 'o') {
                        int *num = va_arg(args, int *);
                        fscanf(stream, "%255s", buffer);
                        *num = roman_to_int(buffer);
                        total_read++;
                    }
                    break;
                case 'Z':
                    format++;
                    if (*format == 'r') {
                        unsigned int *num = va_arg(args, unsigned int *);
                        fscanf(stream, "%255s", buffer);
                        *num = fib_zec_to_int(buffer);
                        total_read++;
                    }
                    break;
                case 'C':
                    format++;
                    int *num = va_arg(args, int *);
                    int base = va_arg(args, int);
                    if (base < 2 || base > 36) base = 10;
                    fscanf(stream, "%255s", buffer);
                    *num = base_to_decimal(buffer, base);
                    total_read++;
                    break;
                default:
                    ungetc('%', stream);
                    total_read += vfscanf(stream, format - 1, args);
            }
        } else {
            ungetc(*format, stream);
            total_read += vfscanf(stream, format, args);
        }
        format++;
    }

    va_end(args);
    return total_read;
}

int oversscanf(const char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    int total_read = 0;

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'R':
                    format++;
                    if (*format == 'o') {
                        int *num = va_arg(args, int *);
                        fscanf(stdin, "%255s", buffer);
                        *num = roman_to_int(buffer);
                        total_read++;
                    }
                    break;
                case 'Z':
                    format++;
                    if (*format == 'r') {
                        unsigned int *num = va_arg(args, unsigned int *);
                        fscanf(stdin, "%255s", buffer);
                        *num = fib_zec_to_int(buffer);
                        total_read++;
                    }
                    break;
                case 'C':
                    format++;
                    int *num = va_arg(args, int *);
                    int base = va_arg(args, int);
                    if (base < 2 || base > 36) base = 10;
                    fscanf(stdin, "%255s", buffer);
                    *num = base_to_decimal(buffer, base);
                    total_read++;
                    break;
                default:
                    ungetc('%', stdin);
                    //--format;
                    total_read += fscanf(stdin, format, args);
            }
        } else {
            ungetc(*format, stdin);
            total_read += fscanf(stdin, format, args);
        }
        format++;
    }

    va_end(args);
    return total_read;
}
