#include "functions.h"

int main(int argc, char* argv[]) {
    if (argc == 0){
        printf("No arguments?");
        return ERROR_ARGS;
    }

    double result;
	result = geometricSum(4, 29999999999999999.0, 355555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555.0, 466666666666666666666666666666666666666666666666666666666666666666666666666666666666.0, 5555555555555555555555555555555555555555555555555555555555555555555555555555555.0);
	if (result == -1) {
		printf("Overflow detected\n");
		//return ERROR_FULL;
	} else if (result == -2){
        printf("Squar from a negative number detected. No complex numbers for today\n");
        //return ERROR_NEGATIVE;
    } else {
        printf("geometric summary is: %lf\n", result);
    }

/////////////////////////////////////////////////////////////////////////////////////////////Peep

	long double base = 2.0;
	int exponent = -3;
    int error = 0;
	long double res = fastPower(base, exponent, &error);
	if (error) {
        printf("Overflow detected\n");
		return ERROR_FULL;
	}
	printf("binpow: %Lf^%d=%Lf\n", base, exponent, res);
	
    
    
    return SUCCESS;
}