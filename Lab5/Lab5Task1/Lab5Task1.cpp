#include "binary_int.h"

int main() {
    binary_int a(10);
    binary_int b(5);
    binary_int g(3);

    cout << a << endl;
    cout << a-- << endl;
    cout << a << endl;


    cout << "a: " << a << endl;     //1010
    cout << "b: " << b << endl;     //101

    binary_int c = a + b + g;
    cout << "a + b: " << c << endl; //1111

    c += binary_int(3);
    cout << "c += 3: " << c << endl;//10010

    binary_int d = c - b;
    cout << "c - b: " << d << endl; //1101

    d *= binary_int(3);
    cout << "d *= 3: " << d << endl;//100111

    d <<= 1;
    cout << "d <<= 1: " << d << endl;//1001110

    d >>= 2;
    cout << "d >>= 2: " << d << endl;//10011

    binary_int f(8);

    auto split_result = f.split();
    cout << "Split f: " << split_result.first << " | " << split_result.second << endl;  //10 | 0

    binary_int e(1);

    cout << "e++: " << e++ << endl; //10

    cout << "++e: " << ++e << endl; //11

    return 0;
}