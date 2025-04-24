#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <sstream>

#include "HttpMessage.h"
#include "Parsable.h"
#include "ParsingException.h"
#include "HttpResponse.h"
class HttpRequest : public HttpMessage, public Parsable{
    
  public:
    HttpRequest() {}
    HttpRequest(char buffer[]);
    HttpResponse response;
    void parse(const std::string& message);
    void parseHeaders(const std::string& header);
    void parseFirstLine(const std::string& line);
    void handleRequest();
};

#endif // HTTP_REQUEST_H