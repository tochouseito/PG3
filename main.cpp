#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <functional>

// SetTimeout関数を作成する
void SetTimeout(std::function<void()> func, int delayMilliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
    func();
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // 乱数のシードを設定

    int diceResult = rand() % 6 + 1; // サイコロの目を1から6までランダムに決定
    int userGuess;

    std::cout << "サイコロの目が奇数か偶数かを当ててください！ (奇数=1, 偶数=0): ";
    std::cin >> userGuess;

    // ラムダ式でサイコロの偶奇を判定し、入力値をキャプチャして結果を判断する
    auto checkResult = [=]() {
        bool isEven = (diceResult % 2 == 0);
        bool userCorrect = ((userGuess == 0 && isEven) || (userGuess == 1 && !isEven));

        std::cout << "\n--- 結果発表 ---\n";
        if (userCorrect) {
            std::cout << "正解！サイコロの目は " << diceResult << " でした！" << std::endl;
        } else {
            std::cout << "不正解！サイコロの目は " << diceResult << " でした！" << std::endl;
        }
        };

    // SetTimeoutを使用して3秒後に結果を表示
    std::cout << "結果を確認中...\n";
    SetTimeout(checkResult, 3000);

    return 0;
}
