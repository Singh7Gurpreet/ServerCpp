#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "HttpMessage.h"
#include "Parsable.h"
#include "ParsingException.h"
class HttpRequest : public HttpMessage, public Parsable{
  public:
    void parse(const std::string& message);
};

#endif