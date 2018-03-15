#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <memory.h>
#include "MdEngine.h"
#include "OutputAdapter.h"
using namespace std;

extern OutputAdapter* opa;

void MdEngine::sendMdData(WZMarketDataField pDepthMarketData){
	
	int cfd = socket(AF_INET, SOCK_DGRAM, 0);

	int broadcast=1;
	setsockopt(cfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

	struct sockaddr_in si = opa->UdpOutputAdapter();
	
	// struct sockaddr_in si;
	// si.sin_port = htons(8888);
	// si.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//usleep(3000);
	//char buf[20];
	//memset(buf, 0, sizeof(buf));
	//strcpy(buf, "aaa");
	//cout << buf << endl;
	int ret = sendto(cfd, (char *)&pDepthMarketData, sizeof(pDepthMarketData), 0, (struct sockaddr*)&si, sizeof(si));
	//int ret = sendto(cfd, buf, 20, 0, (struct sockaddr*)&si, sizeof(si));
	if(!ret){
		std::cout << "sending successfully" << std::endl;
	}
	else{
		std::cout << "error: " << errno << std::endl;
	}
	close(cfd);

}