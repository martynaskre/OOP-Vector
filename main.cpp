#include <iostream>
#include "Vector.h"
#include <vector>

void testVector() {
    Vector<int> a = { 1, 2, 3, 4 };
    Vector<int> b = { 1, 2, 3, 4 };

    std::cout << (a != b) << std::endl;

//    std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;
//
//    for (auto el: a) {
//        std::cout << el << std::endl;
//    }
//
//    a.resize(6);
//
//    std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << std::endl;
//
//    std::cout << std::endl;
//
//    for (auto el: a) {
//        std::cout << el << std::endl;
//    }
}

void testRealVector()
{
    std::vector<int> b = { 1, 2, 3, 4 };

    std::cout << "size: " << b.size() << ", capacity: " << b.capacity() << std::endl;

    for (auto el: b) {
        std::cout << el << std::endl;
    }

    b.resize(6);

    std::cout << "size: " << b.size() << ", capacity: " << b.capacity() << std::endl;

    std::cout << std::endl;

    for (auto el: b) {
        std::cout << el << std::endl;
    }
}

int main() {
    testVector();

    return 0;
}
