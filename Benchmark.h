//
// Created by Martynas Skrebė on 2022-04-27.
//

#ifndef VECTOR_BENCHMARK_H
#define VECTOR_BENCHMARK_H


#include <chrono>
#include <map>

struct BenchmarkResult {
    std::chrono::steady_clock::time_point start;
    std::string title;
};

class Benchmark {
    static std::map<std::string, BenchmarkResult> benchmarks;

public:
    static void start(const std::string& benchmark, std::string title = "Time difference is: ");
    static void end(const std::string& benchmark);
};


#endif //VECTOR_BENCHMARK_H
