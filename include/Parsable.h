#ifndef PARSABLE_H
#define PARSABLE_H

#include <string>

class Parsable{
  virtual void parse(const std::string& message) = 0;
};

#endif