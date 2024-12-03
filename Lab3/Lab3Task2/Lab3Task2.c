#include "normaCalculation.h"

int main(void) {
    DimensionVector *v1 = NewDimensionVector(3, 1.0, 1.0, 1.0);
    DimensionVector *v2 = NewDimensionVector(3, 1.0, 1.0, 1.0);
    DimensionVector *v3 = NewDimensionVector(3, 1.0, 1.0, 1.0);
    int code = SUCCESS;
    int numberOfNormas = 3;
    int numberOfVectors = 3;
    int p = 1;
    double A[9] = {1, 0, 0,
                   0, 1, 0,
                   0, 0, 1};

    Vector **result = GetMaxNorma(&code, 3, numberOfVectors, numberOfNormas, v1, v2, v3, MaxNorma, NULL, SumNorma, &p, MatrixNorma, &A);
    if (code != SUCCESS) {
        DestroyDimensionVector(v1);
        DestroyDimensionVector(v2);
        DestroyDimensionVector(v3);
        printf("Wrong input. Try again\n");
        return code;
    }

    for (int i = 0; i < numberOfNormas; i++) {
        printf("Longest vectors of %d-th norma: \n", i);
        for (int j = 0; j < result[i]->len; j++) {
            DimensionVector *v = result[i]->buffer[j];
            for (int k = 0; k < v->N; k++) {
                printf("%lf ", v->Coordinates[k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    DestroyDimensionVector(v1);
    DestroyDimensionVector(v2);
    DestroyDimensionVector(v3);
    FreeVectors(result, numberOfNormas);

    return 0;
}