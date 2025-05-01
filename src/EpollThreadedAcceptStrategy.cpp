#ifndef __APPLE__

#include "EpollThreadedAcceptStrategy.h"

EpollThreadedAcceptStrategy::EpollThreadedAcceptStrategy() : 
epoll(EpollUtility::getEpollInstance())
{
  pool = new ThreadPool(std::thread::hardware_concurrency());
}

EpollThreadedAcceptStrategy::~EpollThreadedAcceptStrategy() {
  delete pool;
  pool = nullptr;
}

void EpollThreadedAcceptStrategy::kickStart(HttpTcpServer& server, std::function<void()> function) {
  
  // making socket ready to listen
  try {
    server.bindAndListen();
  } catch (Exceptions &e) {
    e.logError();
    throw;
  }
  
  //calling callback provided by user
  function();

  epoll.addForRead(server.getSocket());

  while(true) {
    int n = epoll.getReadyEvents();

    if(n <= 0) continue;

    auto events = epoll.getEvents();
    std::cout << n << "\n";
    for(int i = 0; i < n; i++) {
      epoll_event tempEvent = events[i];
      if(tempEvent.data.fd == server.getSocket()) {
        sockaddr clientAddr{};
        socklen_t clientLen = sizeof(clientAddr);

        int clientSocket = accept(server.getSocket(),&clientAddr,&clientLen);
        assert(clientSocket != -1);
        epoll.addForRead(clientSocket);
      } else {
        int clientSocket = tempEvent.data.fd;
        char buffer[1024];
        int readBytes = read(clientSocket,buffer,1024);
        if((tempEvent.events & EPOLLHUP) || (tempEvent.events & EPOLLERR) || readBytes <= 0) {
          epoll.removeFileDescriptor(clientSocket);
          close(clientSocket);
        } else {
          std::string request(buffer, readBytes);
          pool->addWork([request,&server,clientSocket]{
            try{
            server.getRouter().handleRequest((char*)request.c_str(),clientSocket);
            } catch(Exceptions& e) {
              e.logError();
            }
          });
        }
      }
    }
  }
}

#endif
