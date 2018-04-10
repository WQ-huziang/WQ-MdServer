#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "WZUtil/frame.h"
#include "wzdatastruct.h"
#include "transportstruct.h"
//#include "ThostFtdcUserApiStruct.h"

inline void parserTo(const TSAlertField &alert, Frame &f) {
  f.source = WZ_SOURCE_CTP;
  f.msg_type = WZ_MSG_TYPE_ALERT_DATA;
  f.rtn_type = WZ_RTN_TYPE;
  f.data.alert = alert;
}

inline struct Frame parserTo(const TSInputOrderField req){
  Frame f;
  f.source = WZ_SOURCE_CTP;
  f.msg_type = WZ_MSG_TYPE_ORDER_INSERT;
  f.rtn_type = WZ_RTN_TYPE;
  f.data.insert = req;
  return f;
}

inline struct Frame parserTo(const TSOrderActionField req){
  Frame f;
  f.source = WZ_SOURCE_CTP;
  f.msg_type = WZ_MSG_TYPE_ORDER_ACTION;
  f.rtn_type = WZ_RTN_TYPE;
  f.data.action = req;
  return f;
}

inline struct Frame parserTo(const TSRtnOrderField req){
  Frame f;
  f.source = WZ_SOURCE_CTP;
  f.msg_type = WZ_MSG_TYPE_ON_ORDER;
  f.rtn_type = WZ_RTN_TYPE;
  f.data.order = req;
  return f;
}

inline struct Frame parserTo(const TSMarketDataField req){
  Frame f;
  f.source = WZ_SOURCE_CTP;
  f.msg_type = WZ_MSG_TYPE_MARKET_DATA;
  f.rtn_type = WZ_RTN_TYPE;
  f.data.market = req;
  return f;
}

inline struct Frame parserTo(const TSRtnTradeField req){
  Frame f;
  f.source = WZ_SOURCE_CTP;
  f.msg_type = WZ_MSG_TYPE_ON_TRADE;
  f.rtn_type = WZ_RTN_TYPE;
  f.data.trade = req;
  return f;
}


#endif
