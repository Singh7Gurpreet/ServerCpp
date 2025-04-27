#include "ServerFactory.h"

std::unique_ptr<Server> ServerFactory::create(ServerType type, int flag) {
  switch (type) {
  case ServerType::HTTP: {
    auto server = std::make_unique<HttpTcpServer>();
      if(flag & MULTITHREADED) {
        server->useStrategy(new MultiThreadServerStrategy(4));
      } else {
      server->useStrategy(new SingleThreadServerStrategy()); 
      }
      return server;
  }
  default:
      throw ServerNotFoundException("Invalid server type");
  }
}
