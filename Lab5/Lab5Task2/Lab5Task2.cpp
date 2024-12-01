#include "encoder.h"

int main() {
    vector<byte> key = {byte(0x01), byte(0x23), byte(0x45), byte(0x67), byte(0x89), byte(0xAB), byte(0xCD), byte(0xEF)};
    //vector<byte> key = {};
    Encoder encoder(key);

    int code = encoder.encode("input.txt", "encrypted.txt", true);
    if (code) {
        logErrors(code);
        return code;
    }

    code = encoder.encode("encrypted.txt", "decrypted.txt", true);
    if (code) {
        logErrors(code);
        return code;
    }

    return SUCCESS;
}