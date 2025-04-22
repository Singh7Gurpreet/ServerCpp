#include "HttpVersions.h"

std::string getHttpVersionString(HttpVersion version) {
  switch(version) {
    case HTTP_1_0:
      return "HTTP/1.0";
    case HTTP_1_1:
      return "HTTP/1.1";
    case HTTP_2_0:
      return "HTTP/2.0";
    case HTTP_3_0:
      return "HTTP/3.0";
    default:
      throw VersionNotFound("Invalid http version");
  }
}