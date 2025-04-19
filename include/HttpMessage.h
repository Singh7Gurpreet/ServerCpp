#ifndef HTTP_MESSAGE_H
#define HTTP_MESSAGE_H

#include <string>
#include <unordered_map>

#include "HttpMethods.h"
#include "HttpVersions.h"

// Abstract base class representing both HTTP Request and Response
class HttpMessage {
protected:
    HttpMethod method;
    std::string hostname;
    std::string path;
    HttpVersions version;
    std::unordered_map<std::string, std::string> headers;

public:
    // Constructor and virtual destructor
    HttpMessage() = default;
    virtual ~HttpMessage() = default;

    // Setters
    void setHeader(const std::string& headerName, const std::string& headerContent);
    void setVersion(const std::string& versionStr);
    void setMethod(const std::string& methodName);

    // Getters
    HttpMethod getMethod() const;
    std::string getHeader(const std::string& headerName) const;
    HttpVersions getVersion() const;
};

#endif // HTTP_MESSAGE_H
