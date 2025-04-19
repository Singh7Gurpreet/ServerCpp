#ifndef PARSING_ERROR_H
#define PARSING_ERROR_H

#include "Exceptions.h"

class ParsingError: public Exceptions {
  const char* type() {
    return "Parsing Error";
  }  
};

#endif //PARSING_ERROR_H