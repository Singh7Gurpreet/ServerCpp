#include "KqueueHandler.h"

KqueueHandler::KqueueHandler(int n) {
  kq = kqueue();
  pool = new ThreadPool<std::function<void()>>(n);
  if(kq == -1) {
    throw KqueueException("Failed to create kqueue");
  }
}

KqueueHandler::~KqueueHandler() {
  delete pool;
  pool = nullptr;
  close(kq);
  close(socketId);
}

void KqueueHandler::registerChanges(int socketId) {
  this->socketId = socketId;
  EV_SET(&change, socketId, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, nullptr);
  int k = kevent(kq, &change, 1, nullptr, 0, nullptr);
  if(k == -1) {
    throw KqueueException("Failed to register event");
  }
}

void KqueueHandler::processEvents(HttpTcpServer& server) {
  int nevents = kevent(kq, nullptr, 0, events.data(), MAX_EVENTS, nullptr);
  if (nevents == -1) {
      throw KqueueException("Error in waiting for events");
  }

  for (int i = 0; i < nevents; ++i) {
      if (events[i].filter == EVFILT_READ) {
          if (events[i].ident == (uintptr_t)socketId) { 
              sockaddr_in clientAddr{};
              socklen_t clientSize = sizeof(clientAddr);
              int clientSocket = accept(socketId, (sockaddr*)&clientAddr, &clientSize);
              
              if (clientSocket >= 0) {
                  fcntl(clientSocket, F_SETFL, O_NONBLOCK);
                  char buffer[1024] = {0};

                  // Instead of reading here, push the clientSocket to thread pool
                  pool->addWork([clientSocket, buffer, &server]() mutable {
                      try {
                          ssize_t bytes = read(clientSocket, buffer, sizeof(buffer));
                          if (bytes > 0) {
                              server.getRouter().handleRequest(buffer, clientSocket);
                          }
                          close(clientSocket); // close after handling
                      } catch (Exceptions& e) {
                          e.logError();
                      }
                  });
              }
          }
      }
  }
}
