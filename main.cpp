#include "Utility.h"

void LoadAndSortTxtFile(std::vector<std::string>& numbers, const std::string& fileName) {

	// ファイルを開く
    std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open the file " << fileName << std::endl;
		return;
	}

    // ファイルを一行読み込み
    std::string line;
    if (std::getline(file, line)) {
        // []を削除
        line.erase(std::remove(line.begin(), line.end(), '['), line.end());
        line.erase(std::remove(line.begin(), line.end(), ']'), line.end());
        // カンマで分割してvectorに格納
        std::regex re(",");
        std::sregex_token_iterator it(line.begin(), line.end(), re, -1);
        std::sregex_token_iterator end;
        for (; it != end; ++it) {
			numbers.push_back(it->str());
        }
    }

	// ファイルを閉じる
	file.close();

    // 番号順にソート
    std::sort(numbers.begin(), numbers.end(), [](const std::string& first, const std::string& second) {
        std::regex re("k(\\d{3})g(\\d+)\\@g.neec\\.ac\\.jp");
        // 格納用
        std::smatch matchFirst, matchSecond;
		int numPreFirst = 0, numPreSecond = 0;
		int numPostFirst = 0, numPostSecond = 0;

		// 先頭の数字を抽出
		if (std::regex_search(first, matchFirst, re)) {
			numPreFirst = std::stoi(matchFirst[1]);
			numPostFirst = std::stoi(matchFirst[2]);
		}

		// 学籍番号の部分を抽出
		if (std::regex_search(second, matchSecond, re)) {
			numPreSecond = std::stoi(matchSecond[1]);
			numPostSecond = std::stoi(matchSecond[2]);
		}

		// 先頭の数字で比較して同じ場合は学籍番号で比較
		if (numPreFirst == numPreSecond) {
			return numPostFirst < numPostSecond;
		}
        return numPreFirst < numPreSecond;
        });
}

int main() {

    // コンテナ
	std::vector<std::string> numbers;

    LoadAndSortTxtFile(numbers, "PG3_2024_03_02.txt");

	// 出力
    for (const std::string& number : numbers) {
		CharOut("", number);
    }

    return 0;
}
