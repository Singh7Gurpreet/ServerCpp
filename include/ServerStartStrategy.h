#pragma once

#include <functional>

#include "HttpTcpServer.h"

class HttpTcpServer;

class ServerStartStrategy {
  public:
      virtual void kickStart(HttpTcpServer& server, std::function<void()> function) = 0;
      virtual ~ServerStartStrategy() = default;
  };
  