#include "HttpRequest.h"

/* 
GET / HTTP/1.1
Host: localhost:3000
User-Agent: curl/8.7.1
Accept: *//*

*/

void HttpRequest::parseFirstLine(const std::string& firstLine) {
  std::stringstream ss(firstLine);
  std::string methodName, path, version;
  ss >> methodName >> path >> version;

  try{
  setMethod(methodName);
  setVersion(version);
  setPath(path); 

  } catch (const Exceptions& e) {
    e.logError();
  }
}

void HttpRequest::parseHeaders(const std::string& line) {
  int firstColon = line.find(":");

  if(firstColon == std::string::npos) {
    throw ParsingException("Invalid Header");
  } 

  this->setHeader(line.substr(0,firstColon+1),line.substr(firstColon));
}

void HttpRequest::parse(const std::string& message) {
  std::stringstream messageStream(message);
  std::string line;

  getline(messageStream, line);

  // getting carriage return out of picture :)
  line.pop_back();

  while(getline(messageStream,line)) {
    line.pop_back();
    parseHeaders(line);
  }
}