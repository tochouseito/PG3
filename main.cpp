#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdio.h>

int main() {
    std::mutex mtx;
    std::condition_variable cv;
    int currentThread = 1; // 実行中のスレッドを示す番号

    // スレッドで実行するラムダ関数
    auto printThread = [&mtx, &cv, &currentThread](int id) {
        std::unique_lock<std::mutex> lock(mtx);

        // 自分の順番になるまで待機
        cv.wait(lock, [&] { return currentThread == id; });

        // 順番が来たらメッセージを表示
        printf("thread%d\n", id);

        // 次のスレッドに進む
        currentThread++;
        cv.notify_all(); // 他のスレッドに通知
        };

    // スレッドを作成
    std::thread t1(printThread, 1);
    std::thread t2(printThread, 2);
    std::thread t3(printThread, 3);

    // スレッドの終了を待機
    t1.join();
    t2.join();
    t3.join();

    return 0;
}