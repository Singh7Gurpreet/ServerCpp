#ifndef GENERATABLE_H
#define GENERATABLE_H

#include <string>

class Generatable {
  public:
    virtual char* generateResponse() = 0;
    virtual int length() = 0;
};

#endif // GENERATABLE_H