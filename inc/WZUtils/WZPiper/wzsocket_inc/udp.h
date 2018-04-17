//
// Author: luojunbin
//
#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "frame.h"
#include "iniparser.h"
#include "wzpiper.hpp"

#define MAXEPOLLSIZE 10
#define MAXLISTENQUEUE 10

#define LOGGER

#ifdef LOGGER
#include <glog/logging.h>
#endif

class UdpSocket
{
public:
	UdpSocket();
	~UdpSocket();

	/************************************************* 
	Function: init
	Description: init tcpsocket, set config information
	InputParameter: 
		file_path: config file path
		piperMode: WZ_PIPER_SERVER-0; WZ_PIPER_CLIENT-1
		blockMode: WZ_PIPER_BLOCK-0; WZ_PIPER_NBLOCK-1
	Return: 0-succeed; 1-failed
	*************************************************/
	int init(char file_path[256], int piperMode, int blockMode);

	/************************************************* 
	Function: Recv
	Description: read configure file and init the IPC according to the value of isCLient
	InputParameter: receive a frame from piper
		frame: read receive datum from piper to frame
	Return: size of receive data(positive) if receive succeed, -1 if failed
	*************************************************/
	int Recv(Frame &md);

	/************************************************* 
	Function: Send
	Description: read configure file and init the IPC according to the value of isCLient
	InputParameter: send a frame to piper
		frame: the datum to send to piper
	Return: 0 if send succeed, -1 if failed
	*************************************************/
	int Send(Frame &md);

private:

	/************************************************* 
	Function: Bind
	Description: bind socket_fd to sockaddr_in when init as server
	InputParameter: none
	Return: 0 if send succeed, -1 if failed
	*************************************************/
	int Bind();

	/************************************************* 
	Function: Connect
	Description: connect socket_fd to sockaddr_in when init as client
	InputParameter: none
	Return: 0 if send succeed, -1 if failed
	*************************************************/
	int Connect();

	/************************************************* 
	Function: addEvent
	Description: call epoll_ctl to add socket_fd to listen_queue
	InputParameter: 
		sockfd: the socket_fd to be added
		state: event state
	Return: 0 if send succeed, -1 if failed
	*************************************************/
	int addEvent(int sockfd, int state);

private:
	char ip[256];
	int port;

	int udpfd;
	int epollfd;

	bool isClient;
	bool isSocketBlocking;
	int isEpollBlocking;

	struct sockaddr_in addr;
	struct epoll_event events[MAXEPOLLSIZE];
};

#endif
