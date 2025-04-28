#pragma once


#ifdef __APPLE__

#define MAX_EVENTS 1024
#define BUFFER_SIZE 1024

#include <iostream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <cstring>


#include "EventsHandler.h"
#include "KqueueExceptions.h"
#include "HttpTcpServer.h"
#include "ThreadPool.h"

class KqueueHandler: public EventHandler {
  int kq;
  struct kevent change;
  int socketId;
  std::vector<struct kevent> events;
  ThreadPool<std::function<void()>> *pool;

  public:
  KqueueHandler(int n = 1);
  ~KqueueHandler();
  void registerChanges(int socketId);
  void processEvents(HttpTcpServer& server);
};

#endif