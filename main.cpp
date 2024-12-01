#include <iostream>
#include <thread>

// スレッドで実行する関数
void printMessage(const std::string& message) {
    for (int i = 0; i < 5; ++i) {
        std::cout << message << " " << i << std::endl;
    }
}

int main() {
    // 新しいスレッドを作成して、printMessageを実行
    std::thread t(printMessage, "Hello from thread");

    // メインスレッドで別の処理
    for (int i = 0; i < 5; ++i) {
        std::cout << "Hello from main " << i << std::endl;
    }

    // スレッドの終了を待機
    t.join();

    return 0;
}