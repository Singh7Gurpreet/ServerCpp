#pragma once

#include <thread>
#include <functional>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stdexcept>

template <typename DataType>
class ThreadPool {
    std::vector<std::thread> workers;
    std::vector<std::queue<DataType>> workQueues;
    std::vector<std::mutex> queueLocks;
    std::condition_variable cv;
    std::mutex cvLock;
    bool stop = false;
    int count = 0;  // round-robin index

    void workAssigner(int index) {
        while (true) {
            DataType work;

            {
                std::unique_lock<std::mutex> lock(queueLocks[index]);

                if (workQueues[index].empty()) {
                    lock.unlock();

                    // Wait on global cv (so all threads sleep when idle)
                    std::unique_lock<std::mutex> cvUnlock(cvLock);
                    cv.wait(cvUnlock, [this]() {
                        return stop; // woken up either to check stop or retry
                    });
                    continue;
                }

                // Pop task from this thread's queue
                work = std::move(workQueues[index].front());
                workQueues[index].pop();
            }

            // Execute work outside lock
            work();
        }
    }

public:
    ThreadPool(int n) {
        if (n <= 0)
            throw std::runtime_error("Thread count must be positive");

        stop = false;
        workQueues.resize(n);
        queueLocks.resize(n);

        for (int i = 0; i < n; ++i) {
            workers.emplace_back(&ThreadPool::workAssigner, this, i);
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(cvLock);
            stop = true;
        }
        cv.notify_all();

        for (auto &worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    void addWork(DataType d) {
        int index;

        {
            std::lock_guard<std::mutex> lock(cvLock);
            index = count;
            count = (count + 1) % workQueues.size();
        }

        {
            std::lock_guard<std::mutex> lock(queueLocks[index]);
            workQueues[index].push(std::move(d));
        }

        cv.notify_all();  // Notify all threads to check their queues
    }
};