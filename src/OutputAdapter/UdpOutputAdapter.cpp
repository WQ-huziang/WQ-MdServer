//
//
// Author : lijiaheng
// This is the cpp file

#include "OutputAdapter/UdpOutputAdapter.h"
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

UdpOutputAdapter::UdpOutputAdapter(int UdpHton, char UdpAddr[]){
  this->UdpHton = UdpHton;
  strcpy(this->UdpAddr, UdpAddr);
}

void UdpOutputAdapter::init(){
  this->sock = socket(AF_INET, SOCK_DGRAM, 0);

  int broadcast=1;
  setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

  this->si.sin_family = AF_INET;
  this->si.sin_port = htons(this->UdpHton);
  this->si.sin_addr.s_addr = inet_addr(this->UdpAddr);
}

void UdpOutputAdapter::send(Frame dataframe){
  UdpOutputAdapter::init();
  this->dataframe = dataframe;
  int ret = sendto(this->sock, (char *)&this->dataframe, sizeof(this->dataframe), 0, (struct sockaddr*)&this->si, sizeof(this->si));
  if(!ret || !errno){
    std::cout << "sending successfully" << std::endl;
  } else {
    std::cout << "error: " << errno << std::endl;
  }
}

void UdpOutputAdapter::Close(){
  close(this->sock);
}