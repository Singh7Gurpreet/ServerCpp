#pragma once

#include "Exceptions.h"

class ServerInitializationException: public Exceptions {
  public:
  ServerInitializationException(const std::string& message) :
         Exceptions(message) {}
  const char* type() const {
    return "ServerInitializationError";
  }  
};