#pragma once

#include <thread>
#include <functional>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stdexcept>

class ThreadPool {
public:
    explicit ThreadPool(size_t threads);
    ~ThreadPool();

    template <typename F, typename... Args>
    auto addWork(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

private:
    // Worker loop
    void workAssigner();

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> workQueue;

    std::mutex lockGuard;
    std::condition_variable cv;
    bool stop = false;
};

// Constructor
inline ThreadPool::ThreadPool(size_t threads) {
    if (threads == 0)
        throw std::runtime_error("Thread count must be > 0");

    for (size_t i = 0; i < threads; ++i) {
        workers.emplace_back(&ThreadPool::workAssigner, this);
    }
}

// Destructor
inline ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(lockGuard);
        stop = true;
    }
    cv.notify_all();

    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

// Worker thread loop
inline void ThreadPool::workAssigner() {
    while (true) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(lockGuard);
            cv.wait(lock, [this]() {
                return stop || !workQueue.empty();
            });

            if (stop && workQueue.empty()) return;

            task = std::move(workQueue.front());
            workQueue.pop();
        }

        task(); // Execute task
    }
}

// Template: Add work
template <typename F, typename... Args>
auto ThreadPool::addWork(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> res = task->get_future();

    {
        std::lock_guard<std::mutex> lock(lockGuard);
        if (stop) {
            throw std::runtime_error("addWork on stopped ThreadPool");
        }

        workQueue.emplace([task]() { (*task)(); });
    }

    cv.notify_one();
    return res;
}
