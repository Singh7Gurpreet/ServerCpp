#include "ServerFactory.h"

std::unique_ptr<Server> create(ServerType type) {
  switch (type)
  {
  case ServerType::HTTP:
    return std::make_unique<HttpTcpServer>();
  default:
    throw ServerNotFoundException("Invalid server type");
  }
}