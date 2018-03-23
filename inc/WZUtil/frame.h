//
// Created by w2w on 18-3-15.
//

#ifndef STRATEGY_FRAME_H
#define STRATEGY_FRAME_H

#include "transportstruct.h"

struct Frame{
    short source;
    short msg_type;
    short error_id;
    short rtn_type;
    short dest;
    int length;
    union Data{
        TSInputOrderField insert;
        TSOrderActionField action;
        TSRtnOrderField order;
        TSRtnTradeField trade;
        TSMarketDataField market;
    } data;
};

struct ReqFrame{
    char source;
    char msg_type;
    char error_id;
    char rtn_type;
    int length;
    union ReqData{
        TSInputOrderField insert;
        TSOrderActionField action;
    } req_data;
};

/* 用的比较少，所以还没用简化的TS的形式 */
struct RspFrame{
    char source;
    char msg_type;
    char error_id;
    char rtn_type;
    int length;
    union RspData{
        WZRspAccountField account;
        WZRspPositionField position;
    } rsp_data;
};

struct RtnFrame{
    char source;
    char msg_type;
    char error_id;
    char rtn_type;
    int length;
    union RtnData{
        TSRtnOrderField order;
        TSRtnTradeField trade;
    } rtn_data;
};

struct MarketDataFrame{
    char source;
    char msg_type;
    char error_id;
    char rtn_type;
    int length;
    TSMarketDataField market_data;
//    union MarketData{
//        TSMarketDataField
//    } market_data;
};
//
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
// source: 数据来源
///////////////////////////////////
//ctp
#define WZ_SOURCE_CTP          0
//xtp
#define WZ_SOURCE_XTP          1

typedef short WZSourceType;

///////////////////////////////////
// rtn_type: 用来二级区分msg_type, 暂时用不着
///////////////////////////////////
// 统一
#define WZ_RTN_TYPE 0

typedef short WZRtnType;

///////////////////////////////////
// OrderType: 单的类型
///////////////////////////////////
//市价单
#define WZ_Order_Market          '0'
//限价单
#define WZ_Order_Limit         '1'
//fok
#define WZ_Order_Fok          '2'
//fak
#define WZ_Order_Fak          '3'

typedef char WZOrderType;

#endif //STRATEGY_FRAME_H
