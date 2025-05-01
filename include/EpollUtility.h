#ifndef __APPLE__

#define MAX_EVENTS 20002

#include <sys/epoll.h>
#include <unistd.h>
#include <vector>
#include <cassert>
#include <iostream>

class EpollUtility{
  static int EpollFileDescriptor;
  std::vector<struct epoll_event> events;
  EpollUtility();
  ~EpollUtility();
  EpollUtility(const EpollUtility&) = delete;
  EpollUtility& operator=(const EpollUtility&) = delete;
  public:
  static EpollUtility& getEpollInstance();  
  int getReadyEvents();
  void addNewFileDescriptor(const int &fileDescriptor, struct epoll_event& events);
  void modifyFileDescriptor(const int &fileDescriptor, struct epoll_event& events);
  void removeFileDescriptor(const int &fileDescriptor);
  void addForRead(const int &fileDescriptor);
  std::vector<struct epoll_event>& getEvents();
};

#endif