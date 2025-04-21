#pragma once

#include "Exceptions.h"

class ContentTypeNotFound: public Exceptions {
  public:
  ContentTypeNotFound(const std::string& message) :
         Exceptions(message) {}
  const char* type() const {
    return "ContentTypeNotFound";
  }  
};