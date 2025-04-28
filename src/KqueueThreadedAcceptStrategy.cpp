#include "KqueueThreadedAcceptStrategy.h"

KqueueThreadedAcceptStrategy::KqueueThreadedAcceptStrategy(int numberOfThreads) {
  kq = KqueueHandler(numberOfThreads);
}

void KqueueThreadedAcceptStrategy::kickStart(HttpTcpServer& server, std::function<void()> function) {
  kq.registerChanges(server.getSocket());
  
  if(function) {
    function();
  }

  while(true) {
    kq.processEvents(server);
  }
}