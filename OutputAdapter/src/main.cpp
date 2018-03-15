#include <iostream>
#include <memory.h>
#include "OutputAdapter.h"
#include "TcpOutputAdapter.h"
#include "UdpOutputAdapter.h"
#include "frame.h"

int main() {

	char addr[] = {"127.0.0.1"};
	OutputAdapter* opa = new TcpOutputAdapter(8001, addr);
	Frame frame;
	char buf[50] = {"66666"};
	cout << buf << endl;
	frame.source = 1;
	frame.msg_type = 1;
	frame.error_id = 1;
	frame.rtn_type = 1;
	frame.length = sizeof(buf);
	memcpy(frame.data, buf, 500);

	opa->send(frame);
	opa->Close();

	return 0;
}