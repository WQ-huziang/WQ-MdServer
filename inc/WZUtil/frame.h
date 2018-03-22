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
    short dest;
    int length;
    char data[500];
};

///////////////////////////////////
// source: 数据来源
///////////////////////////////////
//ctp
#define WZ_SOURCE_CTP          0
//xtp
#define WZ_SOURCE_XTP          1

typedef short WZSourceType;

///////////////////////////////////
// msg_type: 数据类型
///////////////////////////////////
//行情数据
#define WZ_MSG_TYPE_MARKET_DATA          0
//下单数据
#define WZ_MSG_TYPE_ORDER_INSERT         1
//撤单数据
#define WZ_MSG_TYPE_ORDER_ACTION         2
//订单变化数据
#define WZ_MSG_TYPE_ON_ORDER             3
//订单成交数据
#define WZ_MSG_TYPE_ON_TRADE             4

typedef short WZMsgType;

///////////////////////////////////
// error_id: 数据类型
///////////////////////////////////
//成功
#define WZ_ERROR_ID_SUCCESS          0
//异常
#define WZ_ERROR_ID_ERROR            1

typedef short WZErrorId;

///////////////////////////////////
// rtn_type: 用来二级区分msg_type, 暂时用不着
///////////////////////////////////
// 统一
#define WZ_RTN_TYPE 0

typedef short WZRtnType;


#endif //STRATEGY_FRAME_H
