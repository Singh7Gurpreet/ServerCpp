#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#include "HttpRequest.h"

using namespace std;

int main() {
    int socketId = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in pr{};
    pr.sin_family = AF_INET;
    pr.sin_port = htons(3000);
    pr.sin_addr.s_addr = INADDR_ANY;

    bind(socketId, (sockaddr*)&pr, sizeof(pr));
    listen(socketId, 5);

    cout << "HTTP server running at http://localhost:3000\n";

    while (true) {
        sockaddr_in clientAddr{};
        socklen_t clientSize = sizeof(clientAddr);
        int clientSocket = accept(socketId, (sockaddr*)&clientAddr, &clientSize);

        if (clientSocket >= 0) {
            cout << "Client connected\n";
            HttpRequest h1;
            // Optional: read incoming request
            char buffer[1024] = {0};
            read(clientSocket, buffer, sizeof(buffer));
            h1.parse(buffer);
            h1.handleRequest();
            // Send HTTP response
            h1.response.setBody("<h1>Hello from server!</h1>").setContentType(TEXT_HTML).setStatus(OK);
            /*const char* httpResponse =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: 28\r\n"
                "\r\n"
                "<h1>Hello from server!</h1>\n";
            */
            char *p = h1.response.generateResponse();
            cout << p << endl;
            send(clientSocket, p, h1.response.length(), 0);
            delete p;
            p = nullptr;
            close(clientSocket);
        }
    }

    close(socketId);
    return 0;
}
