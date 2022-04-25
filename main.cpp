#include <iostream>
#include "Vector.h"

int main() {
    Vector<int> a = { 1, 2, 3, 4};

    for (auto el: a) {
        std::cout << el << std::endl;
    }

    std::cout << std::endl;

    a.insert(a.end(), 69);

    for (auto el: a) {
        std::cout << el << std::endl;
    }

    return 0;
}
