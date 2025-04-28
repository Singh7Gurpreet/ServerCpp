#pragma once

#include <memory>

#include "Server.h"
#include "HttpTcpServer.h"
#include "ServerEnums.h"
#include "SingleThreadServerStrategy.h"
#include "ServerNotFoundException.h"
#include "MultiThreadServerStrategy.h"
#include "KqueueThreadedAcceptStrategy.h"

/*
Why factory design pattern for server?

In future we might implement different variations
of servers but they all would have common thing
listen function which accepts port and then can proceed
to interact with client in their respective way.
So, for ease of future scalablity I used this design
pattern. :)
*/

class ServerFactory {
public:
    static std::unique_ptr<Server> create(ServerType type, int flag);
};