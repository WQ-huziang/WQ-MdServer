#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Frame.h"

class OutputAdapter{

public:
  OutputAdapter();
  void setFilePath(char *filepath);
  void setUdpHtons(int htons);
  void setTcpHtons(int htons);
  void setUdpAddr(char *addr);
  void setTcpAddr(char *addr);
  int getUdpSock();
  int getTcpSock();
  struct sockaddr_in UdpOutputAdapter();
  void TcpOutputAdapter();
  const char* getFilePath();
  virtual void write(Frame &frame) = 0;

private:
  int UdpHtons;
  char UdpAddr[100];

  int TcpHtons;
  char TcpAddr[100];

  char FilePath[100];

  int SockTcp;
  int SockUdp;
};