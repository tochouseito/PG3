#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

class ThreadManager {
public:
    ThreadManager(size_t numThreads);
    ~ThreadManager();

    void EnqueueTask(std::function<void()> task);
    void StopAllThreads();

private:
    void WorkerThread(); // ワーカースレッドのメイン処理

    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex queueMutex_;
    std::condition_variable condition_;
    std::atomic<bool> stop_{ false };
};

// コンストラクタ: 指定した数のスレッドを作成
ThreadManager::ThreadManager(size_t numThreads) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers_.emplace_back([this] { WorkerThread(); });
    }
}

// デストラクタ: スレッドを停止して解放
ThreadManager::~ThreadManager() {
    StopAllThreads();
}

// タスクをキューに追加
void ThreadManager::EnqueueTask(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex_);
        tasks_.push(std::move(task));
    }
    condition_.notify_one(); // スレッドにタスクが追加されたことを通知
}

// ワーカースレッドの処理ループ
void ThreadManager::WorkerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            condition_.wait(lock, [this] { return stop_ || !tasks_.empty(); });

            if (stop_ && tasks_.empty()) return; // 停止フラグが立ったら終了

            task = std::move(tasks_.front());
            tasks_.pop();
        }
        task(); // タスクを実行
    }
}

// 全スレッドの停止
void ThreadManager::StopAllThreads() {
    {
        std::lock_guard<std::mutex> lock(queueMutex_);
        stop_ = true;
    }
    condition_.notify_all(); // すべてのスレッドを起こす

    for (std::thread& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

// 使用例
int main() {
    ThreadManager threadManager(4); // 4スレッドを管理

    // タスクを追加
    for (int i = 0; i < 10; ++i) {
        threadManager.EnqueueTask([i] {
            std::cout << "Task " << i << " executed on thread " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2)); // 少し待つ
    threadManager.StopAllThreads(); // 終了処理
    return 0;
}
