#ifdef __APPLE__

#include "KqueueHandler.h"

KqueueHandler::KqueueHandler(int n) {
  this->kq = kqueue();
  pool = new ThreadPool<std::function<void()>>(n);
  if(kq == -1) {
    throw KqueueException("Failed to create kqueue");
  }
  this->events.resize(MAX_EVENTS);
}

KqueueHandler::~KqueueHandler() {
  delete pool;
  pool = nullptr;
  close(kq);
  close(socketId);
}

void KqueueHandler::registerChanges(int socketId) {
  this->socketId = socketId;
  EV_SET(&change, socketId, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, nullptr);
  int k = kevent(kq, &change, 1, nullptr, 0, nullptr);
  if(k == -1) {
    throw KqueueException("Failed to register event");
  }
}

void KqueueHandler::processEvents(HttpTcpServer& server) {
  int nevents = kevent(this->kq, nullptr, 0, this->events.data(), MAX_EVENTS, nullptr);
  if (nevents == -1) {
      throw KqueueException("Error in waiting for events");
  }

  for (int i = 0; i < nevents; ++i) {
    if (events[i].filter == EVFILT_READ) {
        if (events[i].ident == (uintptr_t)socketId) {
            // New connection waiting on server socket
            sockaddr_in clientAddr{};
            socklen_t clientSize = sizeof(clientAddr);
            int clientSocket = accept(socketId, (sockaddr*)&clientAddr, &clientSize);

            if (clientSocket >= 0) {
                // Make client socket non-blocking
                fcntl(clientSocket, F_SETFL, O_NONBLOCK);

                // Register clientSocket to kqueue for EVFILT_READ
                struct kevent newEvent;
                EV_SET(&newEvent, clientSocket, EVFILT_READ, EV_ADD, 0, 0, NULL);
                kevent(kq, &newEvent, 1, NULL, 0, NULL);

                std::cout << "Accepted and registered new client socket: " << clientSocket << std::endl;
            }
        } 
        else {
            // Data available to read on clientSocket
            int clientSocket = (int)events[i].ident;

            pool->addWork([clientSocket, &server]() mutable {
                char buffer[1024];
                while (true) {
                    ssize_t bytes = read(clientSocket, buffer, sizeof(buffer));
                    if (bytes > 0) {
                        try{
                        server.getRouter().handleRequest(buffer, clientSocket);
                        } catch (Exceptions& e) {
                            e.logError();
                        }
                    } else if (bytes == 0) {
                        // client closed connection
                        // close(clientSocket);
                        break;
                    } else {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            // no more data for now
                            break;
                        } else {
                            // real error
                            perror("read");
                            // close(clientSocket);
                            break;
                        }
                    }
                }
            });
        }
    }
}

}

#endif