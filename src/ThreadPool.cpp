// #include "ThreadPool.h"

// template <typename DataType>
// ThreadPool<DataType>::ThreadPool(int n) {
//     unsigned int max_threads = std::thread::hardware_concurrency();
//     if (max_threads != 0 && n > max_threads) {
//         throw std::runtime_error("Requested threads exceed system capabilities");
//     }

//     stop = false;
//     for (int i = 0; i < n; i++) {
//         workers.push_back(std::thread(&ThreadPool::workAssigner, this));
//     }
// }

// template <typename DataType>
// ThreadPool<DataType>::~ThreadPool() {
//     {
//         std::unique_lock<std::mutex> lock(lockGuard);
//         stop = true;
//     }
//     cv.notify_all();

//     for (std::thread &worker : workers) {
//         if (worker.joinable())
//             worker.join(); 
//     }
// }

// template <typename DataType>
// void ThreadPool<DataType>::addWork(DataType d) {
//     {
//         std::lock_guard<std::mutex> lock(this->lockGuard);
//         workQueue.push(std::move(d));
//     }
//     cv.notify_one();
// }

// template <typename DataType>
// void ThreadPool<DataType>::workAssigner() {
//     while (true) {
//         std::unique_lock<std::mutex> lock(this->lockGuard);

//         cv.wait(lock, [this]() {
//             return stop || !this->workQueue.empty();
//         });

//         if (stop && this->workQueue.empty()) {
//             return;
//         }

//         auto work = std::move(this->workQueue.front());
//         this->workQueue.pop();

//         lock.unlock();

//         work(); // Execute the task
//     }
// }
