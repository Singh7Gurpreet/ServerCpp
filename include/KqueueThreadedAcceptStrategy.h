#pragma once

#ifdef __APPLE__

#include "ServerStartStrategy.h"
#include "HttpTcpServer.h"
#include "ThreadPool.h"
#include "KqueueHandler.h"

class KqueueThreadedAcceptStrategy : public ServerStartStrategy {
  KqueueHandler kq;
  public:
      KqueueThreadedAcceptStrategy(int numberOfThreads = 1);
      ~KqueueThreadedAcceptStrategy() = default;
  
      void kickStart(HttpTcpServer& server, std::function<void()> function) override;
  };

#endif