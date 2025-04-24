#include "Router.h"

Router& Router::getRouter() {
  static Router instance;
  return instance;
}

void Router::route(HttpMethod method, const std::string& path, RouteHandler handler) {
    routesMap[method][path] = handler;
}

void Router::get(const std::string& path, RouteHandler handler) {
    route(HttpMethod::GET, path, handler);
}

void Router::post(const std::string& path, RouteHandler handler) {
    route(HttpMethod::POST, path, handler);
} 

void Router::put(const std::string& path, RouteHandler handler) {
    route(HttpMethod::PUT, path, handler);
}

void Router::patch(const std::string& path, RouteHandler handler) {
  route(HttpMethod::PATCH, path, handler);
}

void Router::handleRequest(char buffer[], int clientSocket) {
    HttpRequest request(buffer);

    HttpMethod currentMethod = request.getMethod();
    std::string currentPath = request.getPath();

    if(routesMap[currentMethod].find(currentPath) == routesMap[currentMethod].end()) {
        throw RouteNotFoundException("Route " + currentPath + " not found in routes");
    }

    routesMap[currentMethod][currentPath](request);

    char* response = request.response.generateResponse();
    send(clientSocket,response,request.response.length(),0);
}
