#include <iostream>
#include <cmath>

using namespace std;

enum ret_type_t {
    SUCCESS,    //Happy end
    ERROR_MALLOC,   //Failed to allocate memory
};

void logError(int code) {
    switch(code) {
        case ERROR_MALLOC: {
            cout << "Failed to allocate memory" << endl;
        }
    }
}