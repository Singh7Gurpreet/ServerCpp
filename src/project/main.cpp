#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#include "ServerFactory.h"
#include "Exceptions.h"

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
    try{
    auto server = ServerFactory::create(ServerType::HTTP);
    server->kickStart(3000,[&](){
        std::cout << "Listening on port 3000...";
    });
} catch (Exceptions& e) {
    e.logError();
}
}
