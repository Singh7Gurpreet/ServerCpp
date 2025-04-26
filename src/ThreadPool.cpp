#include "ThreadPool.h"

template <typename DataType>
ThreadPool<DataType>::ThreadPool(int n) {
  unsigned int max_threads = std::thread::hardware_concurrency();
        if (max_threads != 0 && n > max_threads) {
            throw std::runtime_error("Requested threads exceed system capabilities");
        }  
    for (int i = 0; i < n; i++) {
      workers.push_back(std::thread(&ThreadPool::workAssigner, this));
  }
  
}

template <typename DataType>
ThreadPool<DataType>::~ThreadPool() {

}

template <typename DataType>
void ThreadPool<DataType>::addWork(DataType d) {
  {
  std::lock_guard<std::mutex> lock(this->lockGuard);
  workQueue.push(d);
  }
  cv.notify_one();
}

template <typename DataType>
void ThreadPool<DataType>::workAssigner() {
    std::unique_lock<std::mutex> lock(this->lockGuard);

    cv.wait(lock, [this]() {
        return !this->workQueue.empty();
    });

    auto work = this->workQueue.front();
    this->workQueue.pop();

    lock.unlock();

    work();
}