#include "HttpResponse.h"

HttpResponse& HttpResponse::setStatus(HttpStatusCode code) {
  this->status = code;
  return *this;
}

HttpResponse& HttpResponse::setContentType(HttpContentType type) {
  this->contentType = type;
  return *this;
}

HttpResponse& HttpResponse::setBody(std::string&& content) {
    this->body = std::move(content);
    this->bodyLength = static_cast<int>(this->body.size());
    return *this;
}

/*

HTTP/1.1 200 OK\r\n
Content-Type: text/html\r\n
Content-Length: 28\r\n
Connection: close\r\n
\r\n
<h1>Hello from server</h1>


 */


// Will be start working on this tommorow
char* HttpResponse::generateResponse() {
  //need something like 
  // `Hi there I am ${}`
  char *response =
  "";

  return response;
}

int HttpResponse::length() {
  return lengthOfResponse;
}
