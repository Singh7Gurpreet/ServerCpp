#include "ServerStartStrategy.h"
#include "HttpTcpServer.h"
#include "ThreadPool.h"

class MultiThreadServerStrategy : public ServerStartStrategy {
  ThreadPool *pool;
  public:
      MultiThreadServerStrategy();
      ~MultiThreadServerStrategy();
  
      void kickStart(HttpTcpServer& server, std::function<void()> function) override;
  };