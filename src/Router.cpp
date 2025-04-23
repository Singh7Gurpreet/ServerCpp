#include "Router.h"

// Used pointer previously but gpt gave me non
// pointer method to use which is good
Router& Router::getRouter() {
    static Router instance;
    return instance;
}

void Router::add(const std::string& path,
   std::function<void(HttpRequest&)> handler) {
    routes[path] = handler;
}

void Router::handleRequest(HttpRequest& request) {
  std::string path = request.getPath();
  if(routes.find(request.getPath()) != routes.end()) {
    routes[path](request);
  } else {
    throw RouteNotFound("Route " + path + " not available");
  }
}