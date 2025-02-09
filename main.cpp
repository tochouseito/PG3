#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include <condition_variable>

// グローバル変数
std::vector<std::vector<int>> mapData; // マップデータ格納
std::mutex mtx;                        // 排他制御用
std::condition_variable cv;            // 条件変数
bool isLoaded = false;                 // データロード完了フラグ

// CSVファイルを読み込む関数
void LoadCSV(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << fileName << std::endl;
        return;
    }

    std::vector<std::vector<int>> tempData;
    std::string line;

    // CSV読み込み
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<int> row;

        // カンマで区切って値を取得
        while (std::getline(ss, cell, ',')) {
            row.push_back(std::stoi(cell)); // 整数に変換して格納
        }
        tempData.push_back(row);
    }

    // ファイルを閉じる
    file.close();

    // コピー
    {
        std::lock_guard<std::mutex> lock(mtx);
        mapData = std::move(tempData); // データを移動
        isLoaded = true;
    }

    // データ読み込み完了を通知
    cv.notify_one();
}

// マップデータを表示する関数
void OutMap() {
    // データが読み込まれるまで待機
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return isLoaded; });

    // データを描画
    std::cout << "Map Data " << std::endl;
    for (const auto& row : mapData) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // CSVファイル名
    const std::string fileName = "Map.csv";

    // スレッドを開始して非同期でCSVを読み込む
    std::thread loader(LoadCSV, fileName);

    // メインスレッドでマップを表示
    OutMap();

    // スレッドの終了を待つ
    loader.join();

    return 0;
}
