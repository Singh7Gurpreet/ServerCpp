#pragma once

#include <memory>
#include "EventsHandler.h"

#ifdef __APPLE__
#include "KqueueThreadedAcceptStrategy.h"
#elif defined(__linux__)
#include "EpollThreadedAcceptStrategy.h"
#endif

class EventHandlerFactory{
  public:
  static std::unique_ptr<ServerStartStrategy> create();
};
