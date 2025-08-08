#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

class ThreadPool {
   public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    template <class F>
    void Enqueue(F&& f);

   private:
    std::vector<std::thread> Workers_;
    std::queue<std::function<void()>> Tasks_;
    std::mutex QueueMutex_;
    std::condition_variable Condition_;
    bool Stop_;
};

template <class F>
void ThreadPool::Enqueue(F&& f) {
    {
        std::unique_lock<std::mutex> lock(QueueMutex_);
        if (Stop_) {
            throw std::runtime_error("Enqueue on stopped ThreadPool");
        }
        Tasks_.emplace(std::forward<F>(f));
    }
    Condition_.notify_one();
}
