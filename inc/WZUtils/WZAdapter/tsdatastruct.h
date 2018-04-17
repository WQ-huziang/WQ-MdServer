//
// Created by w2w on 18-3-19.
//

#ifndef WZUTILS_TSDATASTRUCT_H
#define WZUTILS_TSDATASTRUCT_H

#include "wzconstant.h"

struct TSAlertField
{
    char        warning;               // warning type
    char_31     InstrumentID;          //合约代码
};

struct TSMarketDataField
{
    char_13     TradingDay;            //交易日
    char_31     InstrumentID;          //合约代码
    double      LastPrice;             //最新价
    double      PreSettlementPrice;    //上次结算价
    double      PreClosePrice;         //昨收盘
    double      PreOpenInterest;       //昨持仓量
    double      OpenPrice;             //今开盘
    double      HighestPrice;          //最高价
    double      LowestPrice;           //最低价
    int         Volume;                //数量
    double      Turnover;              //成交金额
    double      OpenInterest;          //持仓量
    // double      ClosePrice;            //今收盘
    // double      SettlementPrice;       //本次结算价
    double      UpperLimitPrice;       //涨停板价
    double      LowerLimitPrice;       //跌停板价
    char_13     UpdateTime;            //最后修改时间
    int         UpdateMillisec;        //最后修改毫秒
    double      BidPrice1;             //申买价一
    int         BidVolume1;            //申买量一
    double      AskPrice1;             //申卖价一
    int         AskVolume1;            //申卖量一
};

struct TSInputOrderField
{
    WZOrderType                 OrderType;
    char_31                     InstrumentID;          //合约代码
    double                      LimitPrice;            //价格
    int                         Volume;                //数量
    WZDirectionType             Direction;             //买卖方向
    WZOffsetFlagType            OffsetFlag;            //开平标志
};


struct TSOrderActionField
{
    char_31     InstrumentID;          //合约代码
    char_21     OrderRef;              //报单引用
    char        ActionFlag;            //报单操作标志
    double      LimitPrice;            //价格
    int         VolumeChange;          //数量变化
};


struct TSRtnOrderField
{
    char_31                 InstrumentID;          //合约代码
    char_21                 OrderRef;              //报单引用
    double                  LimitPrice;            //价格
    int                     VolumeTraded;          //今成交数量
    int                     VolumeTotal;           //剩余数量
    int                     VolumeTotalOriginal;   //数量
    WZDirectionType         Direction;             //买卖方向
    WZOffsetFlagType        OffsetFlag;            //开平标志
    WZOrderStatusType       OrderStatus;           //报单状态
};

struct TSRtnTradeField
{
    char_31             InstrumentID;          //合约代码
    char_21             OrderRef;              //报单引用
    double              Price;                 //价格
    int                 Volume;                //数量
    char_13             TradingDay;            //交易日
    char_13             TradeTime;             //成交时间
    WZDirectionType     Direction;             //买卖方向
    WZOffsetFlagType    OffsetFlag;            //开平标志
};




#endif // WZUTILS_TSDATASTRUCT_H
