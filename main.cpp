#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdio.h>

std::mutex mtx;                     // ミューテックス
std::condition_variable cv;         // 条件変数
bool ready = false;                 // 条件を示すフラグ

void worker() {
    std::unique_lock<std::mutex> lock(mtx);
    printf("Worker: Waiting for the signal...");

    cv.wait(lock, [] { return ready; }); // 条件が満たされるまで待機
    printf("Worker: Signal received! Proceeding...");
}

void signaler() {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // シミュレーションのための遅延
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    printf("Signaler: Sending signal...");
    cv.notify_one(); // 待機中のスレッドを1つ再開
}

int main() {
    std::thread t1(worker);
    std::thread t2(signaler);

    t1.join();
    t2.join();

    return 0;
}