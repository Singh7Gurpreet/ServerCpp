#pragma once

#include "Exceptions.h"

class VersionNotFound: public Exceptions {
  public:
  VersionNotFound(const std::string& message) :
         Exceptions(message) {}
  const char* type() const {
    return "HttpVersionNotFound";
  }  
};