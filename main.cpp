#include <iostream>
#include "Vector.h"
#include "Benchmark.h"
#include <vector>
#include <sstream>

template <typename T>
void performBenchmark();

int main() {
    std::cout << "Custom vector benchmark:" << std::endl;
    performBenchmark<Vector<int>>();

    std::cout << std::endl;

    std::cout << "std::vector benchmark:" << std::endl;
    performBenchmark<std::vector<int>>();

    return 0;
}

template <typename T>
void performBenchmark()
{
    T iterations = { 10000, 100000, 1000000, 10000000, 100000000 };

    for (auto iteration: iterations) {
        T object;
        int reallocations = 0;

        std::cout << iteration << " elements test:" << std::endl;

        Benchmark::start("benchmark", "Element insertion took: ");

        for (int i = 1; i <= iteration; i++) {
            if (object.size() == object.capacity()) {
                reallocations++;
            }

            object.push_back(i);
        }

        Benchmark::end("benchmark");
        std::cout << "Reallocations: " << reallocations << std::endl << std::endl;
    }
};
