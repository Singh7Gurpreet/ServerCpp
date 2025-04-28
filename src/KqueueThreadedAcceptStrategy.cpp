#include "KqueueThreadedAcceptStrategy.h"

KqueueThreadedAcceptStrategy::KqueueThreadedAcceptStrategy(int numberOfThreads)
  : kq(numberOfThreads)  
{

}

void KqueueThreadedAcceptStrategy::kickStart(HttpTcpServer& server, std::function<void()> function) {
  
  try{
    server.bindAndListen();
  } catch(Exceptions &e) {
    e.logError();
  }
  
  kq.registerChanges(server.getSocket());
  
  if(function) {
    function();
  }

  while(true) {
    kq.processEvents(server);
  }
}