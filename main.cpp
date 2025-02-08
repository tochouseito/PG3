#include <iostream>

// 比較クラス
template <typename T1, typename T2>
class Compare {
public:
	T1 a;
	T2 b;
	Compare(T1 a, T2 b) : a(a), b(b) {};
	inline T1 Min() {
		return static_cast<T1>(a < b ? a : b);
	}
};

// 出力関数
template <typename T>
void CharOut(const std::string& text,const T& instance) {
	std::cout << text << instance << "\n";
}

// メイン関数
int main() {
    // int, float, double型の組み合わせ
	Compare<int, int> compare(76, 0);
	Compare<float, float> compare2(6.0f, 7.0f);
	Compare<double, double> compare3(6.0, 89.0);
	Compare<int, float> compare4(4, 7.0f);
	Compare<int, double> compare5(6, 1.0);
	Compare<float, double> compare6(-10.0f, 0.0);

	// 出力
	CharOut("compare.IsEqual() : ", compare.Min());
	CharOut("compare2.IsEqual() : ", compare2.Min());
	CharOut("compare3.IsEqual() : ", compare3.Min());
	CharOut("compare4.IsEqual() : ", compare4.Min());
	CharOut("compare5.IsEqual() : ", compare5.Min());
	CharOut("compare6.IsEqual() : ", compare6.Min());

    return 0;
}
