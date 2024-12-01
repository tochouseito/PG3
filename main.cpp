#include <iostream>
#include <thread>
#include <mutex>
#include <stdio.h>

std::mutex mtx;
int counter = 0;

void incrementCounter(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // ロック
        ++counter;
    }
}

int main() {
    const int iterations = 1000;
    std::thread t1(incrementCounter, iterations);
    std::thread t2(incrementCounter, iterations);

    t1.join();
    t2.join();

    printf("counter:%d", counter);

    return 0;
}