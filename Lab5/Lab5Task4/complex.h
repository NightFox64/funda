#include "errors.h"

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }

    Complex operator/(const Complex& other) const {
        if (other.imag == 0 && other.real == 0){
            return Complex(0, 0);
        }
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
                       (imag * other.real - real * other.imag) / denominator);
    }

    double modulus() const {
        return sqrt(real * real + imag * imag);
    }

    double argument() const {
        return atan2(imag, real);
    }

    void display() const {
        //cout << real << (imag >= 0 ? "+" : "") << imag << "i" << endl;
        cout << real << " + " << imag << "i" << endl;
    }
};