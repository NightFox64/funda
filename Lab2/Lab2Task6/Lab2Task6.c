#include "functions.h"

int main() {
    int num;
    unsigned int unum;
    char input[256];

    printf("Enter a Roman numeral: ");
    oversscanf(input, "%Ro", &num);
    printf("Parsed Roman numeral: %d\n", num);

    printf("Enter Fibonacci-Zec number: ");
    oversscanf(input, "%Zr", &unum);
    printf("Parsed Fibonacci-Zec: %u\n", unum);

    printf("Enter a number in base 16: ");
    oversscanf(input, "%Cv", &num, 16);
    printf("Parsed number: %d\n", num);

    printf("Enter a number in base 16 (uppercase): ");
    oversscanf(input, "%CV", &num, 16);
    printf("Parsed number: %d\n", num);

    oversscanf(input, "%d", &num);
    printf("Just number: %d\n", num);

    return SUCCESS;
}
