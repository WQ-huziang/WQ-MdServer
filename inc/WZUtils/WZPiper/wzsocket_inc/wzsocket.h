//
// Author: luojunbin
//

#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "frame.h"

using namespace std;


#define MAXEPOLLSIZE 10
#define MAXLISTENQUEUE 10

class WZSocket
{
public:
  WZSocket();
  ~WZSocket();
  int epollInit();
  int Recv(Frame &md);
  int Send(Frame &md);

private:
  int addEvent(int sockfd, int state);
  int sockAccept(int eventfd);

protected:
  char ip[256];
  int port;

  int tcpfd;
  int udpfd;
  int epollfd;

  struct sockaddr_in addr;
  struct epoll_event events[MAXEPOLLSIZE];

  int server_client_flag;
};

#endif