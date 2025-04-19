#include "HttpMessage.h"

// constructor
HttpMessage::HttpMessage() {
    // Default constructor – no special logic needed for now
}

// destructor
HttpMessage::~HttpMessage() {
    // Virtual destructor – useful for cleanup in derived classes
}

// Setters
void HttpMessage::setHeader(const std::string& headerName, const std::string& headerContent) {
    headers[headerName] = headerContent;
}

void HttpMessage::setVersion(const std::string& version) {
  // HTTP/1.0, HTTP/1.1, HTTP/2, and HTTP/3
  // Currently Supports HTTP/1.0 only

  if(version == "HTTP/1.0") {
    this->version = HttpVersions::HTTP_1_0;
  } else if(version == "HTTP/1.1") {
    this->version = HttpVersions::HTTP_1_1;
  } else if(version == "HTTP/2.0") {
    this->version = HttpVersions::HTTP_2_0;
  } else if(version == "HTTP/3.0") {
    this->version = HttpVersions::HTTP_3_0;
  }
}

void HttpMessage::setMethod(const std::string& methodName) {
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
    }
}

// Getters
HttpMethod HttpMessage::getMethod() const {
    return this->method;
}

std::string HttpMessage::getHeader(const std::string& headerName) const {
    auto it = headers.find(headerName);
    if (it != headers.end()) {
        return it->second;
    }
    return ""; // or throw an exception if preferred
}

HttpVersions HttpMessage::getVersion() const {
    return this->version;
}
