#include "SingleThreadServerStrategy.h"

void SingleThreadServerStrategy::kickStart(HttpTcpServer& server, std::function<void()> callback) {
  
  try{
    server.bindAndListen();
  } catch(Exceptions& e) {
    e.logError();
  }

  if(callback) {
  callback();
  }
    while (true) {
      sockaddr_in clientAddr{};
      socklen_t clientSize = sizeof(clientAddr);
      int clientSocket = accept(server.getSocket(), (sockaddr*)&clientAddr, &clientSize);

      if (clientSocket >= 0) {
          char buffer[8192] = {0};
          read(clientSocket, buffer, sizeof(buffer));
          try {
            server.getRouter().handleRequest(buffer,clientSocket);
          } catch (Exceptions& e) {
            e.logError();
          }
          close(clientSocket);
      }
  }
}