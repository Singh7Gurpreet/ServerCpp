#include "HttpRequest.h"

HttpRequest::HttpRequest(char buffer[]) {
  std::string requestBuffer = std::string(buffer);
  try{
  this->parse(requestBuffer);
  } catch(Exceptions& e) {
    e.logError();
    throw;
  }
}

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
    throw;
  }
}

void HttpRequest::parseHeaders(const std::string& line) {
  std::string::size_type firstColon = line.find(':');
  if(line.empty()) return;
  if(firstColon == std::string::npos) {
    throw ParsingException("Invalid Header: " + line);
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

  try {
    getline(messageStream, line);
    if (!line.empty()) line.pop_back();  // ✅ only pop if not empty
    parseFirstLine(line);

    while (getline(messageStream, line)) {
      if (!line.empty()) line.pop_back();  // ✅ safety check here too
      if (line == "\r" || line.empty()) break;
      parseHeaders(line);
    }
  } catch (Exceptions& e) {
    e.logError();
    throw;
  }
}

void HttpRequest::handleRequest() {

}