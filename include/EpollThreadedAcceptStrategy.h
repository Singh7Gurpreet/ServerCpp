#pragma once

#ifndef __APPLE__

#include "ServerStartStrategy.h"
#include "HttpTcpServer.h"
#include "ThreadPool.h"
#include "EpollHandler.h"

class EpollThreadedAcceptStrategy : public ServerStartStrategy {
  EpollHandler epollHandler;
  public:
      EpollThreadedAcceptStrategy(int numberOfThreads = 1);
      ~EpollThreadedAcceptStrategy() = default;
  
      void kickStart(HttpTcpServer& server, std::function<void()> function) override;
};

#endif
