#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <sstream>

#include "HttpMessage.h"
#include "Parsable.h"
#include "ParsingException.h"
class HttpRequest : public HttpMessage, public Parsable{
  public:
    void parse(const std::string& message);
    void parseHeaders(const std::string& header);
    void parseFirstLine(const std::string& line);
};

#endif // HTTP_REQUEST_H