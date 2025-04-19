#ifndef HEADER_NOT_FOUND_H
#define HEADER_NOT_FOUND_H

#include "Exceptions.h"

class HeaderNotFoundException: public Exceptions {
  public:
  HeaderNotFoundException(const std::string& message) :
         Exceptions(message) {}
  const char* type() const {
    return "HeaderNotFound";
  }  
};

#endif // HEADER_NOT_FOUND_H