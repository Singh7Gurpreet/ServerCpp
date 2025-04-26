#include "ServerStartStrategy.h"
#include "HttpTcpServer.h"

class SingleThreadServerStrategy : public ServerStartStrategy {
  public:
      SingleThreadServerStrategy() = default;
      ~SingleThreadServerStrategy() override = default;
  
      void kickStart(HttpTcpServer& server, std::function<void()> function) override;
  };