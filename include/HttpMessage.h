#ifndef HTTP_MESSAGE_H
#define HTTP_MESSAGE_H

#include <string>

#include "HttpMethods.h"

// this is abstract class of http request and response 
// so I m going to store every data in differnt different variable 
// but I am confused what should be the best practice for this ? 

class HttpMessage {
  HttpMethod method;
  std::string hostname;

};

#endif