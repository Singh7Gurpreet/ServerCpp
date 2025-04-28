#pragma once

/*
// this should be contructor
int kq = kqueue(); // Create kqueue FD
struct kevent change;
EV_SET(&change, socket_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL); // Want to read

kevent(kq, &change, 1, NULL, 0, NULL); // Register interest

//rest of the part should be in listen()
struct kevent events[MAX_EVENTS];
int n = kevent(kq, NULL, 0, events, MAX_EVENTS, NULL); // Wait for events
// Loop over 'events' array to handle events

*/
class EventHandler{

  public:
  EventHandler() = default;
  ~EventHandler() = default;
  void listen();
};