#include "HttpMessage.h"

// Setters
void HttpMessage::setHeader(const std::string& headerName, const std::string& headerContent) {
    headers[headerName] = headerContent;
}

void HttpMessage::setPath(const std::string& path) {
  if(path.empty()) {
    throw ParsingException("Path is empty");
  }

  this->path = path;
}

void HttpMessage::setVersion(const std::string& version) {
  // HTTP/1.0, HTTP/1.1, HTTP/2, and HTTP/3
  // Currently Supports HTTP/1.0 only

  if(version.empty()) {
    throw ParsingException("version is empty");
  }

  if(version == "HTTP/1.0") {
    this->version = HttpVersions::HTTP_1_0;
  } else if(version == "HTTP/1.1") {
    this->version = HttpVersions::HTTP_1_1;
  } else if(version == "HTTP/2.0") {
    this->version = HttpVersions::HTTP_2_0;
  } else if(version == "HTTP/3.0") {
    this->version = HttpVersions::HTTP_3_0;
  } else {
    throw new ParsingException("Version name is invalid");
  }
}

void HttpMessage::setMethod(const std::string& methodName) {
    if(methodName.empty()) {
      throw ParsingException("Method name is empty");
    }
    if(methodName == "GET"){
    this->method = HttpMethod::GET;
    } else if(methodName == "POST") {
      this->method = HttpMethod::POST;
    } else if(methodName == "PUT") {
      this->method = HttpMethod::PUT;
    } else if(methodName == "PATCH") {
      this->method = HttpMethod::PATCH;
    } else if(methodName == "DELETE") {
      this->method = HttpMethod::DELETE;
    } else {
      throw new ParsingException("Method name not found");
    }
}

// Getters
HttpMethod HttpMessage::getMethod() const {
    return this->method;
}

std::string HttpMessage::getHeader(const std::string& headerName) const {
  try { 
  auto it = headers.find(headerName);
    if (it != headers.end()) {
        return it->second;
    } else {
      throw new HeaderNotFoundException("Header not found");
    }
  } catch (const Exceptions& e) {
    e.logError();
  }
}

HttpVersions HttpMessage::getVersion() const {
    return this->version;
}

std::string HttpMessage::getPath() const {
  return this->path;
}