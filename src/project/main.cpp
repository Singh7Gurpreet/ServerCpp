#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#include "ServerFactory.h"
#include "Exceptions.h"
#include "Router.h"

using namespace std;

int main() {
    Router& router = Router::getRouter();

    router.get("/",[&](HttpRequest& req) {
        req.response.setBody("<h1>Hello World from layers of abstraction</h1>")
                    .setContentType(HttpContentType::APPLICATION_JSON)
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

