// Error.h
#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>


class Exceptions {
  std::string message;
  public:
  explicit Exceptions(std::string errorMessage) : message(std::move(errorMessage)) {}

    // virtual destructor for safe polymorphic usage
    virtual ~Exceptions() = default;

    // Match std::exception interface
    virtual const char* what() const noexcept {
        return message.c_str();
    }

    // Custom identifier for subclass type
    virtual const char* type() const = 0;

    virtual void logError() const{
      std::cout << "[ " << this->type() << " ]: " << what() << std::endl;
    }
};

#endif
