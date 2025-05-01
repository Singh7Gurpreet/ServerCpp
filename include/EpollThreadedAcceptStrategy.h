#pragma once

#ifndef __APPLE__

#include "ServerStartStrategy.h"
#include "HttpTcpServer.h"
#include "ThreadPool.h"
#include "EpollUtility.h"

class EpollThreadedAcceptStrategy : public ServerStartStrategy {
  EpollUtility &epoll;
  ThreadPool *pool;
  public:
      EpollThreadedAcceptStrategy();
      ~EpollThreadedAcceptStrategy();
  
      void kickStart(HttpTcpServer& server, std::function<void()> function) override;
};

#endif
