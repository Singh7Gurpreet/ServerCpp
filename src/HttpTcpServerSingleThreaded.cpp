#include "HttpTcpServerSingleThreaded.h" 

HttpTcpServer::HttpTcpServer() : routes(Router::getRouter()) {
  socketId = socket(AF_INET, SOCK_STREAM, 0);
  pr.sin_family = AF_INET;
  pr.sin_addr.s_addr = INADDR_ANY;
}

HttpTcpServer::~HttpTcpServer() {
  close(socketId);
}

void HttpTcpServer::kickStart(int port, std::function<void()> function) {
  this->port = port;
  pr.sin_port = htons(this->port);
  if(bind(socketId, (sockaddr*)&pr, sizeof(pr)) < 0) {
    std::cout << "hello";
  };
  int l = listen(socketId, 128);
  if(l < 0) {
    throw ServerInitializationException("Problem with listen error number is" + std::string(strerror(errno)));
  }

  if(function) {
  function();

  }
    while (true) {
      sockaddr_in clientAddr{};
      socklen_t clientSize = sizeof(clientAddr);
      int clientSocket = accept(socketId, (sockaddr*)&clientAddr, &clientSize);

      if (clientSocket >= 0) {
          char buffer[8192] = {0};
          read(clientSocket, buffer, sizeof(buffer));
          try {
            routes.handleRequest(buffer,clientSocket);
          } catch (Exceptions& e) {
            e.logError();
          }
          // h1.response.setBody("<h1>Hello from server!</h1>").setContentType(TEXT_HTML).setStatus(OK);
          // char *p = h1.response.generateResponse();
          // std::cout << p << std::endl;
          // send(clientSocket, p, h1.response.length(), 0);
          // delete p;
          // p = nullptr;
          close(clientSocket);
      }
  }
}