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
    this->bodyLength = this->body.size();
    return *this;
}

std::string HttpResponse::getContentType() {
  return getContentTypeString(this->contentType);
}

HttpStatusCode HttpResponse::getStatus() {
  return this->status;
}

std::string HttpResponse::getBody() {
  return this->body;
}


/*

HTTP/1.1 200 OK\r\n
Content-Type: text/html\r\n
Content-Length: 28\r\n
Connection: close\r\n
\r\n
<h1>Hello from server</h1>


 */


// Will be working for only http 1.0 because connection is close everytime
char* HttpResponse::generateResponse() {
  std::stringstream output;

  output << getHttpVersionString(this->getVersion()) << " " << this->getStatus() << "\r\n";
  output << "Content-Length: " << this->bodyLength << "\r\n";
  output << "Content-Type: " << this->getContentType() << "\r\n";
  output << "Connection: " << "keep-alive\r\n";
  output << "\r\n";
  output << this->getBody();

  std::string responseStr = output.str();

  char* responseCStr = new char[responseStr.size() + 1]; 
  lengthOfResponse = responseStr.size();
  std::strcpy(responseCStr, responseStr.c_str());
  return responseCStr;
}

int HttpResponse::length() {
  return lengthOfResponse;
}
