#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <atomic>

std::queue<std::function<void()>> taskQueue; // タスクキュー
std::mutex mtx;
std::condition_variable cv;
std::atomic<bool> stopFlag(false);          // スレッドの終了フラグ

void workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return !taskQueue.empty() || stopFlag; });

            if (stopFlag && taskQueue.empty()) break; // 終了条件
            task = std::move(taskQueue.front());
            taskQueue.pop();
        }
        task(); // タスクを実行
    }
}

void addTask(const std::function<void()>& task) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        taskQueue.push(task); // タスクをキューに追加
    }
    cv.notify_one(); // ワーカーに通知
}

int main() {
    const int numThreads = 4;
    std::vector<std::thread> threads;

    // ワーカースレッドを起動
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(workerThread);
    }

    // タスクを追加
    for (int i = 0; i < 10; ++i) {
        addTask([i] {
            std::cout << "Task " << i << " is being processed by thread " << std::this_thread::get_id() << std::endl;
            });
    }

    // タスクキューが空になったら終了フラグを設定
    {
        std::lock_guard<std::mutex> lock(mtx);
        stopFlag = true;
    }
    cv.notify_all();

    // ワーカースレッドを終了
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}