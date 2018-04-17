//
// Created by w2w on 18-3-15.
//

#ifndef WZUTILS_FRAME_H
#define WZUTILS_FRAME_H

#include "tsdatastruct.h"

struct Frame{
    short source;
    short dest;
    short msg_type;
    short error_id;
    short rtn_type;
    int length;
    union Data{
        TSInputOrderField insert;
        TSOrderActionField action;
        TSRtnOrderField order;
        TSRtnTradeField trade;
        TSMarketDataField market;
        TSAlertField alert;
    } data;
};

///////////////////////////////////
// source, dest: 数据来源 & 数据去向
///////////////////////////////////
//ctp
#define WZ_ID_CTP          0
//xtp
#define WZ_ID_XTP          1
//Strategy
#define WZ_ID_S0          100
#define WZ_ID_S1          101
#define WZ_ID_S2          102
#define WZ_ID_S3          103
typedef short WZProcessID;

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
//错误信息
#define WZ_MSG_ERROR                     404
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

#endif // WZUTILS_FRAME_H
