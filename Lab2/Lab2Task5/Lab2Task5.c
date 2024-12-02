#include "functions.h"

int main() {
    overfprintf(stdout, "Roman: %Ro\n", -29);
    overfprintf(stdout, "Fibonacci-Zec: %Zr\n", 21);
    overfprintf(stdout, "Custom Base Low: %Cv\n", -255, 16);
	overfprintf(stdout, "Custom Base High: %CV\n", -255, 16);
	overfprintf(stdout, "Change base Low: %to\n", "-fff", 16);
	overfprintf(stdout, "Change base High: %TO\n", "-FF", 16);
	overfprintf(stdout, "Mem dump int: %mi\n", -5);
	overfprintf(stdout, "Mem dump unsigned int: %mu\n", -5);
	overfprintf(stdout, "Mem dump double: %md\n", -5.0);
	overfprintf(stdout, "Mem dump float: %mf\n", -5.0);

    return SUCCESS;
}
