#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <limits.h>

using namespace std;

enum ret_type_t {
    SUCCESS,            //Happy end
    ERROR_OPEN_FILE,    //Failed to open file
    ERROR_SAME_FILES,   //You're trying to overwrite file
    ERROR_NO_KEY,       //Null key, can't do encoding
};

void logErrors(int code) {
    switch(code) {
        case ERROR_OPEN_FILE: {
            cout << "Failed to open file" << endl;
            break;
        }
        case ERROR_SAME_FILES: {
            cout << "You're trying to overwrite file" << endl;
            break;
        }
        case ERROR_NO_KEY: {
            cout << "Null key, can't do encoding" << endl;
            break;
        }
    }
}