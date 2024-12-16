#include <iostream>
#include <iomanip>

double calculate_recursive_wage(int hours) {
    double wage = 100.0; // 初回時給
    double total = wage;

    for (int i = 2; i <= hours; ++i) {
        wage = (wage * 2) - 50; // 前時間の時給を元に計算
        total += wage;          // 合計金額に加算
    }

    return total;
}

double calculate_general_wage(int hours, double hourly_rate = 1072.0) {
    return hours * hourly_rate;
}

int main() {
    int hours;
    std::cout << "働く時間数を入力してください: ";
    std::cin >> hours;

    double general_wage = calculate_general_wage(hours);
    double recursive_wage = calculate_recursive_wage(hours);

    std::cout << "\n--- 賃金比較結果 ---\n";
    std::cout << "一般的な賃金体系: " << general_wage << " 円\n";
    std::cout << "再帰的な賃金体系: " << recursive_wage << " 円\n";

    if (recursive_wage > general_wage) {
        std::cout << "再帰的な賃金体系の方が有利です。\n";
    } else {
        std::cout << "一般的な賃金体系の方が有利です。\n";
    }

    return 0;
}
