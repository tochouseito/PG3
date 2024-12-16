#include <cstdio>

// テンプレート関数：2つの引数の小さい値を返す
template <typename T>
T Min(T a, T b) {
    return (a < b) ? a : b;
}

// オーバーロード関数: char型の場合にメッセージを出力する
const char* Min(char a, char b) {
    return "数値以外は代入できません";
}

int main() {
    // int型
    int intA = 10, intB = 20;
    printf("int型の小さい値: %d\n", Min(intA, intB));

    // float型
    float floatA = 10.5f, floatB = 20.5f;
    printf("float型の小さい値: %.2f\n", Min(floatA, floatB));

    // double型
    double doubleA = 10.123, doubleB = 5.456;
    printf("double型の小さい値: %.3lf\n", Min(doubleA, doubleB));

    // char型
    char charA = 'a', charB = 'b';
    printf("char型: %s\n", Min(charA, charB));

    return 0;
}
