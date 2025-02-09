#include "Utility.h"

void OutStations(const std::list<const char*>& stations,const char* year) {
    CharOut("--Stations in ", year);
    for (const char* station : stations) {
        CharOut("Station: ", station);
    }
}

int main() {

    // 初期の山手線
    std::list<const char*> yamanoteLine = {
        "Tokyo",
        "Kanda",
        "Akihabara",
        "Ueno",
        "Okachimachi",
        "Yurakucho",
        "Shinagawa",
        "Shibuya",
        "Shinjuku",
        "Ikebukuro",
        "Tabata"
    };

    // 駅一覧表示
    OutStations(yamanoteLine, "1970--");

    // 西日暮里の追加
	for (const char* station : yamanoteLine) {
        if (station == "Tabata") {
			// Tabataの次に追加
			auto it = std::find(yamanoteLine.begin(), yamanoteLine.end(), station);
			yamanoteLine.insert(std::next(it), "Nishi-Nippori");
			break;
        }
	}

    // 駅一覧表示
    OutStations(yamanoteLine, "2019--");

    // 高輪ゲートウェイの追加
    for (const char* station : yamanoteLine) {
        if (station == "Shinagawa") {
            // Tabataの次に追加
            auto it = std::find(yamanoteLine.begin(), yamanoteLine.end(), station);
            yamanoteLine.insert(std::next(it), "Takanawa Gateway");
            break;
        }
    }

	// 駅一覧表示
	OutStations(yamanoteLine, "2022--");

    return 0;
}
