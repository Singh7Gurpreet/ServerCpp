#ifndef PARSING_ERROR_H
#define PARSING_ERROR_H

#include "Exceptions.h"

class ParsingException: public Exceptions {
  public:
  ParsingException(std::string message) :
       Exceptions(message) {}
  const char* type() const {
    return "Parsing Error";
  }  
};

#endif //PARSING_ERROR_H