#include "ServerStartStrategy.h"
#include "HttpTcpServer.h"
#include "ThreadPool.h"
#include "KqueueHandler.h"

class KqueueThreadedAcceptStrategy : public ServerStartStrategy {
  KqueueHandler kq;
  public:
      KqueueThreadedAcceptStrategy(int numberOfThreads);
      ~KqueueThreadedAcceptStrategy();
  
      void kickStart(HttpTcpServer& server, std::function<void()> function) override;
  };