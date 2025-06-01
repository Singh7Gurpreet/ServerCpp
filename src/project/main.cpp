#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <streambuf>

#include "ServerFactory.h"
#include "Exceptions.h"
#include "Router.h"

using namespace std;

std::string cachedHtml;
std::once_flag cacheInitialized;

std::string readFileOnce(const std::string& filepath) {
    std::call_once(cacheInitialized, [&]() {
        std::ifstream file(filepath);
        if (file) {
            cachedHtml.assign((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
        } else {
            cachedHtml = "<h1>Error loading file</h1>";
        }
    });
    return cachedHtml;
}

int main() {
    Router& router = Router::getRouter();

// Inside your router setup
router.get("/", [&](HttpRequest& req) {
    std::string htmlContent = readFileOnce("./src/project/index.html");

    req.response.setBody(std::move(htmlContent))
                .setContentType(HttpContentType::TEXT_HTML)
                .setStatus(HttpStatusCode::OK);
});


    try{
    auto server = ServerFactory::create(ServerType::HTTP,ServerFlags::MULTITHREADED|ServerFlags::EVENTS_BASED);
    server->kickStart(3001,[&](){
        std::cout << "Listening on port 3000...\n";
    });
} catch (Exceptions& e) {
    e.logError();
}
}

