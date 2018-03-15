#include "OutputAdapter.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
using namespace std;

OutputAdapter::OutputAdapter(){
	this->UdpHtons = 8888;
	this->TcpHtons = 8000;
	strcpy(this->FilePath, "data.csv");
	strcpy(this->UdpAddr, "127.0.0.1");
	strcpy(this->TcpAddr, "127.0.0.1");
}

void OutputAdapter::setFilePath(char *filepath){
	strcpy(this->FilePath, filepath);
}

void OutputAdapter::setUdpHtons(int htons){
	this->UdpHtons = htons;
}

void OutputAdapter::setTcpHtons(int htons){
	this->TcpHtons = htons;
}

void OutputAdapter::setUdpAddr(char *addr){
	strcpy(this->UdpAddr, addr);
}

void OutputAdapter::setTcpAddr(char *addr){
	strcpy(this->TcpAddr, addr);
}

int OutputAdapter::getUdpSock(){
	return this->SockUdp;
}
int OutputAdapter::getTcpSock(){
	return this->SockTcp;
}

struct sockaddr_in OutputAdapter::UdpOutputAdapter(){
	this->SockUdp = socket(AF_INET, SOCK_DGRAM, 0);

	int broadcast=1;
	setsockopt(SockUdp, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(this->UdpHtons);
	si.sin_addr.s_addr = inet_addr(this->UdpAddr);

	return si;
}

const char* OutputAdapter::getFilePath(){
	return this->FilePath;
}

void OutputAdapter::TcpOutputAdapter(){
	SockTcp = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in si;

	bzero(&si, sizeof(si));
    si.sin_family = AF_INET;
    inet_pton(AF_INET, this->TcpAddr, &si.sin_addr);
    si.sin_port = htons(this->TcpHtons);
	
	connect(SockTcp, (struct sockaddr *)&si, sizeof(si));
}
