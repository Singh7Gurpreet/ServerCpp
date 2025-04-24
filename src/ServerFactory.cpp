#include "ServerFactory.h"

std::unique_ptr<Server> ServerFactory::create(ServerType type, int flag) {
  switch (type)
  {
  case ServerType::HTTP:
    return std::make_unique<HttpTcpServer>();
  default:
    throw ServerNotFoundException("Invalid server type");
  }
}