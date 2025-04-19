#ifndef SERVER_H
#define SERVER_H

#include <functional>

class Server{
  public:
    virtual int bind(int port) = 0;
    virtual void listen() = 0;
};

#endif