#include "ServerFactory.h"

std::unique_ptr<Server> ServerFactory::create(ServerType type, int flag) {
  switch (type) {
  case ServerType::HTTP: {
    auto server = std::make_unique<HttpTcpServer>();
    if ((flag & MULTITHREADED) && (flag & EVENTS_BASED)) {
      server->useStrategy(EventHandlerFactory::create());
  }
  else if (flag & MULTITHREADED) {
      server->useStrategy(std::make_unique<MultiThreadServerStrategy>(4));
  }
  else {
      server->useStrategy(std::make_unique<SingleThreadServerStrategy>());
  }
  return server;
  }
  default:
      throw ServerNotFoundException("Invalid server type");
  }
}
