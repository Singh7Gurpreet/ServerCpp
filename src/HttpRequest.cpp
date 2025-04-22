#include "HttpRequest.h"

void HttpRequest::parseFirstLine(const std::string& firstLine) {
  std::stringstream ss(firstLine);
  std::string methodName, path, version;
  ss >> methodName >> path >> version;

  try{
  setMethod(methodName);
  this->response.setVersion(version);
  setVersion(version);
  setPath(path); 

  } catch (const Exceptions& e) {
    e.logError();
  }
}

void HttpRequest::parseHeaders(const std::string& line) {
  std::string::size_type firstColon = line.find(':');

  if(firstColon == std::string::npos) {
    throw ParsingException("Invalid Header");
  } 

  this->setHeader(line.substr(0,firstColon),line.substr(firstColon+1));
}


/*
  Developer Note:

  One might get confuse with this line.pop_back() well,
  We get our http message in this format 

  GET / HTTP/1.1\r\n
  Host: localhost:3000\r\n
  User-Agent: curl/8.7.1\r\n
  Accept: *//*\r\n  // used for escaping /
  \r\n

  here /r is carriage return so to remove this we need
  to use this pop_back() function and /n is taken care
  by getline
*/ 

void HttpRequest::parse(const std::string& message) {
  std::stringstream messageStream(message);
  std::string line;

  getline(messageStream, line);
  // getting carriage return out of picture :)
  line.pop_back();
  parseFirstLine(line);

  while(getline(messageStream,line)) {
    line.pop_back();
    if(line.empty()) break;
    parseHeaders(line);
  }
}

void HttpRequest::handleRequest() {

}