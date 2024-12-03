#include "logical_values_array.h"

int main() {
    logical_values_array a(5);
    logical_values_array b(3);

    cout << "a: " << a.get_value() << endl; //101
    cout << "b: " << b.get_value() << endl; //11

    cout << "a & b: " << (a & b).get_value() << endl;   //1
    cout << "a | b: " << (a | b).get_value() << endl;   //111
    cout << "a ^ b: " << (a ^ b).get_value() << endl;   //110
    cout << "~a: " << (~a).get_value() << endl;                     //11111111111111111111111111111010
    cout << "a -> b: " << a.implication(b).get_value() << endl;     //11111111111111111111111111111011
    cout << "a <-> b: " << a.coimplication(b).get_value() << endl;  //11111111111111111111111111111001
    cout << "a == b: " << a.equalant(b).get_value() << endl;        //11111111111111111111111111111001
    cout << "a ↓ b: " << a.pearce(b).get_value() << endl;           //11111111111111111111111111111000
    cout << "a | b: " << a.sheffer(b).get_value() << endl;          //11111111111111111111111111111110

    cout << "Bit 0 of a: " << a.get_bit(0) << endl;
    cout << "Bit 1 of a: " << a.get_bit(1) << endl;
    cout << "Bit 2 of a: " << a.get_bit(2) << endl;
    //cout << "Bit 3 of a: " << a.get_bit(3) << endl;
    cout << "Bit 0 of b: " << b.get_bit(0) << endl;
    cout << "Bit 1 of b: " << b.get_bit(1) << endl;

    char* binary_str = (char*)malloc(sizeof(char) << 1);
    if (binary_str == NULL) {
        logError(ERROR_MALLOC);
        return ERROR_MALLOC;
    }

    int code = a.to_binary_string(binary_str);
    if (code) {
        logError(code);
        return code;
    }
    cout << "Binary representation of a: " << binary_str << endl;
    free(binary_str);

    logical_values_array c(5);
    cout << "a == c: " << logical_values_array::equals(a, c) << endl;
    cout << "a == b: " << logical_values_array::equals(a, b) << endl;


    return 0;
}