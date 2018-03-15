#ifndef TCPOUTPUTADAPTER_H
#define TCPOUTPUTADAPTER_H
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "OutputAdapter.h"
#include "frame.h"

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