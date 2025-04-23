#pragma once

#include "Exceptions.h"

class ServerNotFoundException: public Exceptions {
  public:
  ServerNotFoundException(const std::string& message) :
         Exceptions(message) {}
  const char* type() const {
    return "ServerTypeNotValid";
  }  
};