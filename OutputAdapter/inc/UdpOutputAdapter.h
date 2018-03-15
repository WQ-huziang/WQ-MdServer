#ifndef UDPADAPTER_H
#define UDPADAPTER_H
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "OutputAdapter.h"
#include "frame.h"

class UdpOutputAdapter:public OutputAdapter{

public:
	UdpOutputAdapter(int UdpHton, char UdpAddr[]);
	void init();
	void send(Frame dataframe);
	void Close();

private:
	Frame dataframe;
	
	int UdpHton;
	char UdpAddr[100];

	int sock;
	struct sockaddr_in si;
};

#endif