#pragma once

#include <unordered_map>
#include <functional>

#include "HttpRequest.h"
#include "RouteNotFound.h"

class Router {
  private:
      std::unordered_map<std::string, std::function<void(HttpRequest&)>> routes;

      Router() {}
      ~Router() {}
      Router(const Router&) = delete;
      Router& operator=(const Router&) = delete;
  
  public:

      static Router& getRouter();
      void add(const std::string& path, 
        std::function<void(HttpRequest&)> handler);
      void handleRequest(HttpRequest&);
  };