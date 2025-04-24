#pragma once

#include "Exceptions.h"

class RouteNotFoundException: public Exceptions {
  public:
  RouteNotFoundException(const std::string& message) :
         Exceptions(message) {}
  const char* type() const {
    return "RouteNotFound";
  }  
};