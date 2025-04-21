#pragma once

/*
Developer's Note

I(Gurpreet) havent added all the supported 
content types enums I want it be minimal
can be added more later on as per requirements
*/

#include <string>
#include "ContentTypeNotFound.h"

enum HttpContentType {
  TEXT_PLAIN,
  TEXT_HTML,
  TEXT_CSS,
  APPLICATION_JAVASCRIPT,
  APPLICATION_PDF
};

/*

Function that returns string value of the
HttpContentType enums like if I use
HttpResponse.setContentType(TEXT_PLAIN) it 
will set content type header to text/plain

*/

std::string getContentTypeString(HttpContentType contentType);