#include "errors.h"

unsigned int ultimateInc(unsigned int n) {
    unsigned int mask = 1;
    while (n & mask) {
        n ^= mask;
        mask <<= 1;
    }
    n ^= mask;
    return n;
}

unsigned int ultimateDec(unsigned int n) {
    unsigned int mask = 1;
    while (!(n & mask)) {
        n ^= mask;
        mask <<= 1;
    }
    n ^= mask;
    return n;
}

class logical_values_array {
private:
    unsigned int value;

public:
    logical_values_array(unsigned int val = 0) : value(val) {}

    unsigned int get_value() const {
        return value;
    }

    void set_value(unsigned int val) {
        value = val;
    }

    logical_values_array operator~() const {
        return logical_values_array(~value);
    }

    logical_values_array operator&(const logical_values_array& other) const {
        return logical_values_array(value & other.value);
    }

    logical_values_array operator|(const logical_values_array& other) const {
        return logical_values_array(value | other.value);
    }

    //(A -> B) = ~A | B
    logical_values_array implication(const logical_values_array& other) const {
        return ~(*this) | other;
    }

    //(A <-> B) = ~(A ^ B)
    logical_values_array coimplication(const logical_values_array& other) const {
        return ~(*this ^ other);
    }

    //(A ^ B) = A & ~B | ~A & B
    logical_values_array operator^(const logical_values_array& other) const {
        return logical_values_array((value & ~other.value) | (~value & other.value));
    }

    //(A == B) = ~(A ^ B)
    logical_values_array equalant(const logical_values_array& other) const {
        return ~(*this ^ other);
    }

    //(A ↓ B) = ~(A | B)
    logical_values_array pearce(const logical_values_array& other) const {
        return ~(*this | other);
    }

    //(A | B) = ~(A & B)
    logical_values_array sheffer(const logical_values_array& other) const {
        return ~(*this & other);
    }

    static bool equals(const logical_values_array& a, const logical_values_array& b) {
        return a.value == b.value;
    }

    bool get_bit(int position) const {
        return (value >> position) & 1;
    }

    int to_binary_string(char* destiny) {
        unsigned int number = value, memo = sizeof(char) << 2, index = 0;

        while (number > 0) {
            if (index >= memo) {
                memo <<= 1;
                char* buff = (char*)realloc(destiny, memo);
                if (buff == NULL){
                    return ERROR_MALLOC;
                }
                destiny = buff;
            }
            destiny[index] = (number & 1) ? '1' : '0';
            index = ultimateInc(index);
            number >>= 1;
        }

        destiny[index] = '\0';
        int left = 0;
        int right = ultimateDec(index);
        while(left < right) {
            char temp = destiny[right];
            destiny[right] = destiny[left];
            destiny[left] = temp;
            left = ultimateInc(left);
            right = ultimateDec(right);
        }

        return SUCCESS;
    }
};