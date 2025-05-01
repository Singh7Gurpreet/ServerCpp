#pragma once

#ifndef __APPLE__  // epoll is typically on Linux
#define MAX_EVENTS 1024
#define BUFFER_SIZE 1024

#include <iostream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <cstring>

#include "EventsHandler.h"
#include "EpollException.h"
#include "HttpTcpServer.h"
#include "ThreadPool.h"

class EpollHandler : public EventHandler {
  int epollFd;
  int socketId;
  std::vector<struct epoll_event> events;
  ThreadPool* pool;

  public:
  EpollHandler(int n = 1);
  ~EpollHandler();
  void registerChanges(int socketId);
  void processEvents(HttpTcpServer& server);
};

#endif
