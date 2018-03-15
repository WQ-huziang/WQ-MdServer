//
//
// Author : lijiaheng
// This is a tcp output class

#ifndef TCPOUTPUTADAPTER_H
#define TCPOUTPUTADAPTER_H

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "OutputAdapter/OutputAdapter.h"
#include "OutputAdapter/Frame.h"

class TcpOutputAdapter:public OutputAdapter{

public:
  TcpOutputAdapter(int TcpHton, char TcpAddr[]);
  void init();
  void send(Frame dataframe);
  void Close();

private:
  Frame dataframe;

  int TcpHton;
  char TcpAddr[100];

  int sock;
  struct sockaddr_in si;
};

#endif