#pragma once 

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

#include "Server.h"
#include "Router.h"
#include "HttpRequest.h"
#include "ServerInitializationError.h"

class HttpTcpServer : public Server {
  int socketId;
  int port;
  sockaddr_in pr{};
  Router& routes;

  public:
  HttpTcpServer();
  ~HttpTcpServer();
  void use(Router& routes);
  void useMiddleWares(std::function<void(HttpRequest&)> middleware);
  void kickStart(int port, std::function<void()> function);
};