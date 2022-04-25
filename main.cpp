#include <iostream>
#include "Vector.h"

int main() {
    Vector<int> a = { 1, 2, 3, 4};

    for (auto el: a) {
        std::cout << el << std::endl;
    }

    std::cout << std::endl;

    a.erase(a.begin(), a.begin() + 1);

    for (auto el: a) {
        std::cout << el << std::endl;
    }

    return 0;
}
