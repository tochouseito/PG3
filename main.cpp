#include <iostream>
#include <thread>
#include <mutex>
#include <stdio.h>

std::mutex mtx;

void task(const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx); // ロックを自動管理
    std::cout << message << std::endl;
    // スコープを抜けると自動的にアンロックされる
}

int main() {
    std::thread t1(task, "Hello from thread 1");
    std::thread t2(task, "Hello from thread 2");

    t1.join();
    t2.join();

    return 0;
}