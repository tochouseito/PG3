#pragma once

// スマートポインタ用
#include <memory>

#include <iostream>
// 出力関数
template <typename T>
void CharOut(const std::string& text, const T& instance) {
	std::cout << text << instance << "\n";
}
void CharOut(const std::string& text) {
	std::cout << text << "\n";
}