#ifndef __APPLE__

#include "EpollHandler.h"

EpollHandler::EpollHandler(int n) {
  this->epollFd = epoll_create1(0);
  pool = new ThreadPool(n);
  if (epollFd == -1) {
    throw EpollException("Failed to create epoll instance");
  }
  this->events.resize(MAX_EVENTS);
}

EpollHandler::~EpollHandler() {
  delete pool;
  pool = nullptr;
  close(epollFd);
  close(socketId);
}

void EpollHandler::registerChanges(int socketId) {
  this->socketId = socketId;

  struct epoll_event event;
  event.events = EPOLLIN | EPOLLET; // Readable events, Edge Triggered (optional)
  event.data.fd = socketId;

  if (epoll_ctl(epollFd, EPOLL_CTL_ADD, socketId, &event) == -1) {
    throw EpollException("Failed to register event with epoll");
  }
}

void EpollHandler::processEvents(HttpTcpServer& server) {
  int nevents = epoll_wait(this->epollFd, this->events.data(), MAX_EVENTS, -1);
  if (nevents == -1) {
    throw EpollException("Error waiting for events");
  }

  for (int i = 0; i < nevents; ++i) {
    if (events[i].events & EPOLLIN) {
      if (events[i].data.fd == socketId) {
        sockaddr_in clientAddr{};
        socklen_t clientSize = sizeof(clientAddr);
        int clientSocket = accept(socketId, (sockaddr*)&clientAddr, &clientSize);

        if (clientSocket >= 0) {
          fcntl(clientSocket, F_SETFL, O_NONBLOCK);
          char buffer[1024] = {0};

          pool->addWork([clientSocket, buffer, &server]() mutable {
            try {
              ssize_t bytes = read(clientSocket, buffer, sizeof(buffer));
              if (bytes > 0) {
                server.getRouter().handleRequest(buffer, clientSocket);
              }
              close(clientSocket);
            } catch (Exceptions& e) {
              e.logError();
            }
          });
        }
      }
    }
  }
}

#endif
