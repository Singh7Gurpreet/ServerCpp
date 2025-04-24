#include "HttpContentType.h"

std::string getContentTypeString(HttpContentType contentType)
{
  switch(contentType) {
    case TEXT_PLAIN: return "text/plain";
    case TEXT_HTML: return "text/html";
    case TEXT_CSS: return "text/css";
    case APPLICATION_JAVASCRIPT: return "application/javascript";
    case APPLICATION_PDF: return "application/pdf";
    case APPLICATION_JSON: return "application/json";
    default: throw ContentTypeNotFound("Not a valid supported Content Type");
  }
  return "Content Type Not found";
}