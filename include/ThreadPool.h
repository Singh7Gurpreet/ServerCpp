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
  void workAssigner();

  public:

  ThreadPool(int n);
  ~ThreadPool();
  void addWork(DataType);
};