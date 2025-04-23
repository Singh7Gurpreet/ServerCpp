#pragma once 

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

#include "Server.h"
#include "HttpRequest.h"
#include "ServerInitializationError.h"

class HttpTcpServer : public Server {
  int socketId;
  int port;
  sockaddr_in pr{};

  public:
  HttpTcpServer();
  ~HttpTcpServer();
  void kickStart(int port, std::function<void()> function);
};