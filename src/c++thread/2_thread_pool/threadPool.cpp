#include "threadPool.hpp"

#include <iostream>




ThreadPool::ThreadPool(size_t numThreads) : Stop_(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        // Create and start worker threads which will wait for tasks
        // and execute them when available - inside a lambda function
        Workers_.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(QueueMutex_);
                    Condition_.wait(lock, [this] { return Stop_ || !Tasks_.empty(); });
                    if (Stop_ && Tasks_.empty()) return;
                    task = std::move(Tasks_.front());
                    Tasks_.pop();
                }
                task();
            }
        });
    }
}


ThreadPool::~ThreadPool(){
    {
        std::unique_lock<std::mutex> lock(QueueMutex_);
        Stop_ = true;
    }
    Condition_.notify_all();
    for (std::thread &worker : Workers_) {
        worker.join();
    }
}
