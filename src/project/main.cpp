#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#include "ServerFactory.h"
#include "Exceptions.h"
#include "Router.h"

using namespace std;

/*
POST /users/signUp HTTP/1.1
Content-Type: application/json
User-Agent: PostmanRuntime/7.42.0
Accept: *//*
Postman-Token: c4e95e2a-fcbe-42dc-ae21-36a6621ca24f
Host: localhost:3000
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Content-Length: 43

{
    "Data" : 313213,
    "Name" : 20000
}
*/

int main() {
    Router& router = Router::getRouter();

    router.get("/",[&](HttpRequest& req) {
        req.response.setBody("<h1>Hello World from layers of abstraction</h1>")
                    .setContentType(HttpContentType::APPLICATION_JSON)
                    .setStatus(HttpStatusCode::OK);
    });

    try{
    auto server = ServerFactory::create(ServerType::HTTP,ServerFlags::MULTITHREADED|ServerFlags::EVENTS_BASED);
    server->kickStart(3000,[&](){
        std::cout << "Listening on port 3000...\n";
    });
} catch (Exceptions& e) {
    e.logError();
}
}
