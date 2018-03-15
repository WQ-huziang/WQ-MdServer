//
// Created by w2w on 18-3-15.
//

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

///////////////////////////////////
// source: Êý¾ÝÀ´Ô´
///////////////////////////////////
//ctp
#define WZ_SOURCE_CTP          0
//xtp
#define WZ_SOURCE_XTP          1

typedef short WZSourceType;

///////////////////////////////////
// msg_type: Êý¾ÝÀàÐÍ
///////////////////////////////////
//ÐÐÇéÊý¾Ý
#define WZ_MSG_TYPE_MARKET_DATA          0
//ÏÂµ¥Êý¾Ý
#define WZ_MSG_TYPE_ORDER_INSERT         1
//³·µ¥Êý¾Ý
#define WZ_MSG_TYPE_ORDER_ACTION         2
//¶©µ¥±ä»¯Êý¾Ý
#define WZ_MSG_TYPE_ON_ORDER             3
//¶©µ¥³É½»Êý¾Ý
#define WZ_MSG_TYPE_ON_TRADE             4

typedef short WZMsgType;

///////////////////////////////////
// error_id: Êý¾ÝÀàÐÍ
///////////////////////////////////
//³É¹¦
#define WZ_ERROR_ID_SUCCESS          0
//Òì³£
#define WZ_ERROR_ID_ERROR            1

typedef short WZErrorId;


///////////////////////////////////
// source: Êý¾ÝÀ´Ô´
///////////////////////////////////
//ctp
#define WZ_SOURCE_CTP          0
//xtp
#define WZ_SOURCE_XTP          1

typedef short WZSourceType;

///////////////////////////////////
// rtn_type: ÓÃÀ´¶þ¼¶Çø·Ömsg_type, ÔÝÊ±ÓÃ²»×Å
///////////////////////////////////
// Í³Ò»
#define WZ_RTN_TYPE 0

typedef short WZRtnType;


#endif //STRATEGY_FRAME_H
