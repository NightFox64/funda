#include "functions.h"

int sumBigNumbers(BigNumber **result, int base, int count, ...) {
    if (base < 2 || base > 36) {
        return ERROR_ARGS;
    }

    int code = SUCCESS;
    va_list args;
    va_start(args, count);

    BigNumber *sum = CreateBigNumber("0", base);
    for (int i = 0; i < count; i++) {
        char *numberStr = va_arg(args, char *);
        BigNumber *current = CreateBigNumber(numberStr, base);
        if (current == NULL) {
            DestroyBigNumber(sum);
            return ERROR_MALLOC;
        }

        if (sum->len < current->len) {
            SwapBigNumbers(sum, current);
        }

        code = SumBigNumbers(sum, current);
        if (code != SUCCESS) {
            DestroyBigNumber(sum);
            DestroyBigNumber(current);
            return code;
        }
        DestroyBigNumber(current);
    }

    va_end(args);
    *result = sum;
    return SUCCESS;
}

int main() {
    BigNumber* result;
    //int code = sumBigNumbers(&result, 10, 3, "01", "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000009", "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
    int code = sumBigNumbers(&result, 10, 3, "20", "40", "3");
    if (code != SUCCESS) {
        return code;
    }
    PrintBigNumber(result);
    DestroyBigNumber(result);
    return SUCCESS;
}