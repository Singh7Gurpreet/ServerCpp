#pragma once 

#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

#include "Server.h"
#include "Router.h"
#include "HttpRequest.h"
#include "ServerStartStrategy.h"
#include "ServerInitializationError.h"

class ServerStartStrategy;

class HttpTcpServer : public Server {
  int socketId;
  int port;
  sockaddr_in pr{};
  Router& routes;
  std::unique_ptr<ServerStartStrategy> strategy; 

  public:
  HttpTcpServer();
  ~HttpTcpServer();
  Router& getRouter();
  int getPort();
  int getSocket();
  void useStrategy(std::unique_ptr<ServerStartStrategy>);
  void bindAndListen();
  void useMiddleWares(std::function<void(HttpRequest&)> middleware);
  void kickStart(int port, std::function<void()> function);
};