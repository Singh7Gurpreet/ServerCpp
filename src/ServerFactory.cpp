#include "ServerFactory.h"

std::unique_ptr<Server> ServerFactory::create(ServerType type, int flag) {
  switch (type) {
  case ServerType::HTTP: {
      auto server = std::make_unique<HttpTcpServer>();
      server->useStrategy(new SingleThreadServerStrategy()); 
      return server;
  }
  default:
      throw ServerNotFoundException("Invalid server type");
  }
}
