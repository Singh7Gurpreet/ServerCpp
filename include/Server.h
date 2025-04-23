#ifndef SERVER_H
#define SERVER_H

#include <functional>

/*
Will be using factory pattern for this because
one can use different type of servers so factory pattern
like websockets(bidirectional), webserver, http1.1, http3.0 etc.
can also add flags(or options) for multithreading and other features.
*/

class Server{
  public:
    virtual void listen(int port, std::function<void()> function) = 0;
};

#endif