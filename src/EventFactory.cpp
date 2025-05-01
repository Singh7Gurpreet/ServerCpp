#include "EventHandlerFactory.h"

std::unique_ptr<ServerStartStrategy> EventHandlerFactory::create() {
  #ifdef __APPLE__
  // If we are on macOS, use KqueueThreadedAcceptStrategy
  return std::make_unique<KqueueThreadedAcceptStrategy>(4);
  #elif defined(__linux__)
  // If we are on Linux, use EpollThreadedAcceptStrategy
  return std::make_unique<EpollThreadedAcceptStrategy>();
  #else
  // If OS not supported
  return nullptr;
  #endif
}