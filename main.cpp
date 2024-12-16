#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

// 関数ポインタ用の型定義
using Callback = void (*)(bool);

// 判定結果を表示するコールバック関数
void showResult(bool isCorrect) {
    if (isCorrect) {
        std::cout << "正解！おめでとうございます！" << std::endl;
    } else {
        std::cout << "不正解！残念でした！" << std::endl;
    }
}

// サイコロを振る関数
int rollDice() {
    return rand() % 6 + 1; // 1から6までのランダムな数
}

// ユーザー入力を処理し、結果を判定する関数
void judgeGame(Callback callback) {
    int diceResult = rollDice();
    std::cout << "サイコロの目が奇数か偶数かを当ててください！ (奇数=1, 偶数=0): ";

    int userGuess;
    std::cin >> userGuess;

    bool isEven = (diceResult % 2 == 0);
    bool userCorrect = ((userGuess == 0 && isEven) || (userGuess == 1 && !isEven));

    // 答えをすぐに出さず、3秒間待機
    std::cout << "結果を確認中...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // コールバック関数で結果を通知
    callback(userCorrect);
    std::cout << "実際のサイコロの目: " << diceResult << std::endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // 乱数のシードを設定

    std::cout << "サイコロの目が奇数か偶数かを当てるゲームを始めます！" << std::endl;

    // ゲームの開始
    judgeGame(showResult);

    return 0;
}
