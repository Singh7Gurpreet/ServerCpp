#ifndef HTTP_VERSIONS_H
#define HTTP_VERSIONS_H


#include "VersionNotFound.h"
#include <string>

enum HttpVersion {
  HTTP_1_0,
  HTTP_1_1,
  HTTP_2_0,
  HTTP_3_0
};

std::string getHttpVersionString(HttpVersion version);

#endif