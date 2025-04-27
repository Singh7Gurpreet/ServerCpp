#include "ServerStartStrategy.h"
#include "HttpTcpServer.h"
#include "ThreadPool.h"

class MultiThreadServerStrategy : public ServerStartStrategy {
  ThreadPool<std::function<void()>> *pool;
  public:
      MultiThreadServerStrategy(int numberOfThreads);
      ~MultiThreadServerStrategy();
  
      void kickStart(HttpTcpServer& server, std::function<void()> function) override;
  };