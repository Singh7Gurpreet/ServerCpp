#pragma once

#include "Exceptions.h"

class KqueueException: public Exceptions {
  public:
  KqueueException(const std::string& message) :
         Exceptions(message) {}
  const char* type() const {
    return "KqueueException";
  }  
};