#include "complex.h"

int main() {
    Complex z1(3, 4);
    Complex z2(1, -1);

    cout << "z1 = ";
    z1.display();
    cout << "z2 = ";
    z2.display();

    Complex sum = z1 + z2;
    cout << "Sum z1 + z2 = ";
    sum.display();

    Complex diff = z1 - z2;
    cout << "Subtract z1 - z2 = ";
    diff.display();

    Complex product = z1 * z2;
    cout << "Multiply z1 * z2 = ";
    product.display();

    Complex quotient = z1 / z2;
    cout << "Devision z1 / z2 = ";
    quotient.display();

    cout << "Modulus z1 = " << z1.modulus() << endl;
    cout << "Argument z1 = " << z1.argument() << " rad" << endl;

    return SUCCESS;
}