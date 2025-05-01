#include "HttpTcpServer.h" 

HttpTcpServer::HttpTcpServer() : routes(Router::getRouter()) {
  socketId = socket(AF_INET, SOCK_STREAM, 0);
  pr.sin_family = AF_INET;
  pr.sin_addr.s_addr = INADDR_ANY;
}

HttpTcpServer::~HttpTcpServer() {
  close(socketId);
}

sockaddr_in* HttpTcpServer::getAddress() {
  return &pr;
}

Router& HttpTcpServer::getRouter() {
  return this->routes;
}

int HttpTcpServer::getPort() {
  return this->port;
}

int HttpTcpServer::getSocket() {
  return this->socketId;
}

void HttpTcpServer::bindAndListen() {
  if(bind(socketId, (sockaddr*)&pr, sizeof(pr)) < 0 ) {
    throw ServerInitializationException("Problem with binding socket error");
  }
  int l = listen(socketId, SOMAXCONN);
  if(l < 0) {
    throw ServerInitializationException("Problem with listen error, number is" + std::string(strerror(errno)));
  }
}

void HttpTcpServer::useStrategy(std::unique_ptr<ServerStartStrategy> ptr) {
  this->strategy = std::move(ptr);
}

void HttpTcpServer::kickStart(int port, std::function<void()> function) {
  this->port = port;
  pr.sin_port = htons(this->port);
  this->strategy->kickStart(*this,function);
}