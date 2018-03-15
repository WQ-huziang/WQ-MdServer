#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <memory.h>
#include "MdEngine.h"
#include "OutputAdapter.h"
#include "frame.h"
using namespace std;

extern OutputAdapter* opa;

void MdEngine::sendMdData(WZMarketDataField pDepthMarketData){
	
	int cfd = socket(AF_INET, SOCK_DGRAM, 0);

	int broadcast=1;
	setsockopt(cfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

	struct sockaddr_in si = opa->UdpOutputAdapter();
	
	Frame MdFrame;
	short msg_type = 1;
	int data_length = sizeof(pDepthMarketData);
	MdFrame.msg_type = msg_type;
	MdFrame.length = data_length;
	MdFrame.error_id = 1;
	MdFrame.rtn_type = 1;
	MdFrame.source = 1;
	memcpy(MdFrame.data, (char *)&pDepthMarketData, 500);
	char *buff = new char[sizeof(MdFrame)];
	memcpy(buff, &MdFrame, sizeof(MdFrame));
	
	int ret = sendto(cfd, (char *)&MdFrame, sizeof(MdFrame), 0, (struct sockaddr*)&si, sizeof(si));
	if(!ret){
		std::cout << "sending successfully" << std::endl;
	}
	else{
		std::cout << "error: " << errno << std::endl;
	}
	close(cfd);

}