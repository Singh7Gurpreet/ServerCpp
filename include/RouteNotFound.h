#pragma once

#include "Exceptions.h"

class RouteNotFound: public Exceptions {
  public:
  RouteNotFound(const std::string& message) :
         Exceptions(message) {}
  const char* type() const {
    return "RouteNotFound";
  }  
};