#include <iostream>
#include <thread>
#include <stdio.h>

void task() {
    printf("Hello!Thread");
}

int main() {
    // スレッドを作成
    std::thread t(task);

    // スレッドの終了を待機
    t.join(); // join()でスレッドの終了を待つ

    return 0;
}