#pragma once

#include <thread>
#include <functional>
#include <vector>
#include <queue>
#include <mutex>

template <typename DataType>
class ThreadPool{
  std::vector<std::thread> workers;
  std::queue<DataType> workQueue;
  std::mutex lockGuard;
  std::condition_variable cv;
  bool stop;
  void workAssigner() {
    while (true) {
        std::unique_lock<std::mutex> lock(this->lockGuard);

        cv.wait(lock, [this]() {
            return stop || !this->workQueue.empty();
        });

        if (stop && this->workQueue.empty()) {
            return;
        }

        auto work = std::move(this->workQueue.front());
        this->workQueue.pop();

        lock.unlock();

        work(); // Execute the task
    }
};

  public:

  ThreadPool(int n) {
    if (n < 0) {
        throw std::runtime_error("Number of threads cannot be negative");
    }
    unsigned int un = static_cast<unsigned int>(n);

    unsigned int max_threads = std::thread::hardware_concurrency();
    if (max_threads != 0 && un > max_threads) {
        throw std::runtime_error("Requested threads exceed system capabilities");
    }
    
    stop = false;
    for (unsigned int i = 0; i < un; i++) {
        workers.push_back(std::thread(&ThreadPool::workAssigner, this));
    }
}

  ~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(lockGuard);
        stop = true;
    }
    cv.notify_all();

    for (std::thread &worker : workers) {
        if (worker.joinable())
            worker.join(); 
    }
}

  void addWork(DataType d) {
    {
        std::lock_guard<std::mutex> lock(this->lockGuard);
        workQueue.push(std::move(d));
    }
    cv.notify_one();
}
};