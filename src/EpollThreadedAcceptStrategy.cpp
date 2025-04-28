#ifndef __APPLE__

#include "EpollThreadedAcceptStrategy.h"

EpollThreadedAcceptStrategy::EpollThreadedAcceptStrategy(int numberOfThreads)
  : epollHandler(numberOfThreads) 
{

}

void EpollThreadedAcceptStrategy::kickStart(HttpTcpServer& server, std::function<void()> function) {

  try {
    server.bindAndListen();
  } catch (Exceptions &e) {
    e.logError();
  }

  epollHandler.registerChanges(server.getSocket());

  if (function) {
    function();
  }

  while (true) {
    epollHandler.processEvents(server);
  }
}

#endif
