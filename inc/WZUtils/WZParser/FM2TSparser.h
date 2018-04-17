#ifndef FM2TSPARSER_H
#define FM2TSPARSER_H

#include <string.h>
#include "frame.h"
#include "tsdatastruct.h"

inline void parseTo(Frame &f, const TSInputOrderField &req){
  f.source = WZ_ID_S0;
  f.dest = WZ_ID_CTP;
  f.length = sizeof(TSInputOrderField);
  f.msg_type = WZ_MSG_TYPE_ORDER_INSERT;
  f.rtn_type = WZ_RTN_TYPE;
  f.error_id = WZ_ERROR_ID_SUCCESS;
  memcpy(&f.data.insert, &req, sizeof(TSInputOrderField));
}

inline void parseTo(Frame &f, const TSOrderActionField &req){
  f.source = WZ_ID_S0;
  f.dest = WZ_ID_CTP;
  f.length = sizeof(TSInputOrderField);
  f.msg_type = WZ_MSG_TYPE_ORDER_ACTION;
  f.rtn_type = WZ_RTN_TYPE;
  f.error_id = WZ_ERROR_ID_SUCCESS;
  memcpy(&f.data.action, &req, sizeof(TSOrderActionField));
}

inline void parseTo(Frame &f, const TSRtnOrderField &req){
  f.source = WZ_ID_S0;
  f.dest = WZ_ID_CTP;
  f.length = sizeof(TSInputOrderField);
  f.msg_type = WZ_MSG_TYPE_ON_ORDER;
  f.rtn_type = WZ_RTN_TYPE;
  f.error_id = WZ_ERROR_ID_SUCCESS;
  memcpy(&f.data.order, &req, sizeof(TSRtnOrderField));
}

inline void parseTo(Frame &f, const TSMarketDataField &req){
  f.source = WZ_ID_S0;
  f.dest = WZ_ID_CTP;
  f.length = sizeof(TSInputOrderField);
  f.msg_type = WZ_MSG_TYPE_MARKET_DATA;
  f.rtn_type = WZ_RTN_TYPE;
  f.error_id = WZ_ERROR_ID_SUCCESS;
  memcpy(&f.data.market, &req, sizeof(TSMarketDataField));
}

inline void parseTo(Frame &f, const TSRtnTradeField &req){
  f.source = WZ_ID_S0;
  f.dest = WZ_ID_CTP;
  f.length = sizeof(TSInputOrderField);
  f.msg_type = WZ_MSG_TYPE_ON_TRADE;
  f.rtn_type = WZ_RTN_TYPE;
  f.error_id = WZ_ERROR_ID_SUCCESS;
  memcpy(&f.data.trade, &req, sizeof(TSRtnTradeField));
}


#endif  // FM2TSPARSER_H
