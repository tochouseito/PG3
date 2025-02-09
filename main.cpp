#include <iostream>
#include <string>
#include <chrono>

int main() {
    // 100,000文字の'a'で初期化された文字列
    std::string a(100000, 'a');

    // コピーの時間計測
    std::chrono::high_resolution_clock::time_point startCopy = std::chrono::high_resolution_clock::now();
    std::string b = a; // コピー
    std::chrono::high_resolution_clock::time_point endCopy = std::chrono::high_resolution_clock::now();
    long long copyTime = std::chrono::duration_cast<std::chrono::microseconds>(endCopy - startCopy).count();

    // ムーブの時間計測
    std::chrono::high_resolution_clock::time_point startMove = std::chrono::high_resolution_clock::now();
    std::string c = std::move(a); // ムーブ
    std::chrono::high_resolution_clock::time_point endMove = std::chrono::high_resolution_clock::now();
    long long moveTime = std::chrono::duration_cast<std::chrono::microseconds>(endMove - startMove).count();

    // 結果を表示
    std::cout << "Copy Time: " << copyTime << " microseconds" << std::endl;
    std::cout << "Move Time: " << moveTime << " microseconds" << std::endl;

    return 0;
}
