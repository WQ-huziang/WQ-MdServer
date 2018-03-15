#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <memory.h>
#include "TcpOutputAdapter.h"

TcpOutputAdapter::TcpOutputAdapter(int TcpHton, char TcpAddr[]){
	this->TcpHton = TcpHton;
	strcpy(this->TcpAddr, TcpAddr);
}

void TcpOutputAdapter::init(){
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&this->si, sizeof(this->si));
	this->si.sin_family = AF_INET;
	this->si.sin_port = htons(this->TcpHton);
	inet_pton(AF_INET, this->TcpAddr, &this->si.sin_addr);

	int ret = connect(this->sock, (struct sockaddr*)&this->si, sizeof(this->si));
	if(ret < 0){
		perror("connection error");
		exit(1);
	}
}

void TcpOutputAdapter::send(Frame dataframe){
	TcpOutputAdapter::init();
	int ret = write(this->sock, (char*)&dataframe, sizeof(dataframe));
	cout << errno << endl;
	if(!ret){
		cout << "error: " << endl;
	} else {
		cout << "sending successfully" << endl;
	}
}

void TcpOutputAdapter::Close(){
	close(this->sock);
}