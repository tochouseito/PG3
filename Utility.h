#pragma once
// スマートポインタ用
#include <memory>
#include <iostream>
#include <numbers>
#include <list>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <regex>

const float PI = std::numbers::pi_v<float>;

// 出力関数
template <typename T>
void CharOut(const std::string& text, const T& instance) {
	std::cout << text << instance << "\n";
}
void CharOut(const std::string& text) {
	std::cout << text << "\n";
}