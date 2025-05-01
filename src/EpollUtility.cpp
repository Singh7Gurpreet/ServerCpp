#ifndef ___APPLE__

#include "EpollUtility.h"

int EpollUtility::EpollFileDescriptor = -1e9;

EpollUtility::EpollUtility() {
  events.resize(MAX_EVENTS);
}

EpollUtility& EpollUtility::getEpollInstance() {
  static EpollUtility instance;
  if(EpollFileDescriptor == -1e9) {
    EpollFileDescriptor = epoll_create1(0);
  }
  assert(EpollFileDescriptor > 0);
  return instance;
}

EpollUtility::~EpollUtility() {
  assert(close(EpollFileDescriptor) == 0);
}

void EpollUtility::addNewFileDescriptor(const int &fileDescriptor, struct epoll_event& events) {
  int returnValue = epoll_ctl(EpollFileDescriptor,EPOLL_CTL_ADD,fileDescriptor,&events);
  assert(returnValue == 0 );
}

void EpollUtility::modifyFileDescriptor(const int &fileDescriptor, struct epoll_event& events) {
  int returnValue = epoll_ctl(EpollFileDescriptor,EPOLL_CTL_MOD,fileDescriptor,&events);
  assert(returnValue == 0);
}

void EpollUtility::removeFileDescriptor(const int &fileDescriptor) {
  int returnValue = epoll_ctl(EpollFileDescriptor,EPOLL_CTL_DEL,fileDescriptor,nullptr);
  // assert(returnValue == 0);
}

int EpollUtility::getReadyEvents() {
  int returnValue = epoll_wait(EpollFileDescriptor,events.data(),events.size(),0);
  assert(returnValue != -1);
  return returnValue;
}

std::vector<struct epoll_event>& EpollUtility::getEvents() {
  return this->events;
}

void EpollUtility::addForRead(const int& fileDescriptor) {
  epoll_event event;
  event.data.fd = fileDescriptor;
  event.events = EPOLLIN;

  addNewFileDescriptor(fileDescriptor,event);
}


#endif