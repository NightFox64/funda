#include "vector.h"

int main() { try {
    Vector v = {1.0, 2.0, 3.0};

    std::cout << "Examples of using at():" << std::endl;
    //std::cout << v.at(-1) << std::endl;
    std::cout << v.at(0) << std::endl;
    std::cout << v.at(1) << std::endl;
    std::cout << v.at(2) << std::endl;
    //std::cout << v.at(3) << std::endl << std::endl;

    std::cout << "Example of using front(): " << v.front() << std::endl;

    Vector a = {};
    //std::cout << a.front() << std::endl;

    std::cout << "Example of using back(): " << v.back() << std::endl;

    std::cout << "Example of using data(): " << v.data() << std::endl;

    std::cout << "Example of using empty(): " << v.empty() << " " << a.empty() << std::endl;

    std::cout << "Example of using size(): " << v.size() << " " << a.size() << std::endl;

    std::cout << "Example of using capacity() before reserve(10): " << v.capacity() << std::endl;
    v.reserve(10);
    std::cout << "Example of using capacity() after reserve(10): " << v.capacity() << std::endl;
    v.reserve(3);
    std::cout << "Example of using capacity() after reserve(3): " << v.capacity() << std::endl;
    v.shrink_to_fit();
    std::cout << "Example of using capacity() after shrink_to_fit(): " << v.capacity() << std::endl;

    v.clear();
    std::cout << "Example of using size() after using v.clear(): " << v.size() << " " << a.size() << std::endl;

    v.push_back(4.0);
    v.insert(1, 5.0);
    v.insert(0, 1.0);
    v.insert(2, 2.0);
    v.insert(3, 3.0);
    v.erase(2);
    v.pop_back();
    v.resize(10);
    v.resize(11, 123);

    for (const auto& elem : v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "Example of comparing for equality: " << (v == a) << std::endl;
    std::cout << "Example of comparing for non-equality: " << (v != a) << std::endl;
    std::cout << "Example of comparing for >: " << (v > a) << std::endl;
    std::cout << "Example of comparing for <=: " << (v <= a) << std::endl;


    return 0;
}

    catch (const std::out_of_range& e) {
        std::cout << "Trying to get access to outer limit of vector" << std::endl;
    }
    
}
