#pragma once 

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#include "Server.h"
#include "HttpRequest.h"


class HttpTcpServer : public Server {
  int socketId;
  int port;

  public:
  HttpTcpServer();
  void listen(int port, std::function<void()> function);
};