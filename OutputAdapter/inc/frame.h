#ifndef STRATEGY_FRAME_H
#define STRATEGY_FRAME_H

struct Frame{
	short source;
	short msg_type;
	short error_id;
	short rtn_type;
	int length;
	char data[500];
};

#endif