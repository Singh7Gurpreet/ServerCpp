#pragma once

#include "Exceptions.h"

class EpollException: public Exceptions {
  public:
  EpollException(const std::string& message) :
         Exceptions(message) {}
  const char* type() const {
    return "EpollException";
  }  
};
