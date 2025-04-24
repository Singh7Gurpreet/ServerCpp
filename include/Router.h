#pragma once

#include <unordered_map>
#include <functional>
#include <string>
#include <unistd.h>
#include <sys/socket.h>

#include "HttpRequest.h"
#include "HttpMethods.h"

#include "RouteNotFoundException.h"

using RouteHandler = std::function<void(HttpRequest&)>;

class Router {
private:
    // Nested map: HttpMethod -> path -> handler
    std::unordered_map<
        HttpMethod,
        std::unordered_map<std::string, RouteHandler>
    > routesMap;

    // Singleton instance
    Router() {}
    ~Router() {}
    Router(const Router&) = delete;
    Router& operator=(const Router&) = delete;

public:
    // Singleton access
    static Router& getRouter();

    // Core route method
    void route(HttpMethod method, const std::string& path, RouteHandler handler);

    // HTTP method shortcuts
    void get(const std::string& path, RouteHandler handler);
    void post(const std::string& path, RouteHandler handler);
    void put(const std::string& path, RouteHandler handler);
    void patch(const std::string& path, RouteHandler handler);

    // Call the appropriate route handler
    void handleRequest(char buffer[], int clientSocket);
};
