#include <iostream>
#include <string>

class Enemy {
public:
    Enemy() {
        // 初期状態を接近に設定
        currentState = &Enemy::approach;
    }

    void update() {
        // 現在の状態を実行
        if (currentState) {
            (this->*currentState)(); // メンバ関数ポインタを実行
        }
    }

private:
    // 状態関数のポインタ型定義
    using StateFunction = void (Enemy::*)();

    // 現在の状態を保持する変数
    StateFunction currentState;

    // 状態: 接近
    void approach() {
        std::cout << "敵は接近している" << std::endl;
        // 状態を射撃に遷移
        currentState = &Enemy::shoot;
    }

    // 状態: 射撃
    void shoot() {
        std::cout << "敵は射撃している" << std::endl;
        // 状態を離脱に遷移
        currentState = &Enemy::flee;
    }

    // 状態: 離脱
    void flee() {
        std::cout << "敵は離脱している" << std::endl;
        // 状態遷移を終了
        currentState = nullptr;
    }
};

int main() {
    Enemy enemy;

    while (true) {
        enemy.update();
        if (std::cin.get() == 'q') break; // 'q' を押すと終了
    }

    return 0;
}
