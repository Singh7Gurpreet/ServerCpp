#ifndef PARSABLE_H
#define PARSABLE_H

#include <string>

class Parsable{
  virtual void Parse(const std::string& message) = 0;
};

#endif