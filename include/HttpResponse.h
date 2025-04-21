#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "HttpMessage.h"
#include "HttpStatusCode.h"
#include "Generatable.h"
#include "HttpVersions.h"
#include "HttpContentType.h"

// will h

class HttpResponse : Generatable{
  HttpStatusCode status;
  int bodyLength; 
  HttpContentType contentType;
  std::string body;
  int lengthOfResponse;

  public:
    HttpResponse& setStatus(HttpStatusCode);
    HttpResponse& setContentType(HttpContentType);

    //What if I need to setBody for larger objects how can I 
    // do it with this function like argument is wrong I think so 
    // because it is a string
    //Response by Gpt wether to use char *data with lenght
    //Or use move semantics && which is just similar to move
    // function in string
    HttpResponse& setBody(std::string&& content);

    char* generateResponse();
    int length();
};


#endif //HTTP_RESPONSE_H