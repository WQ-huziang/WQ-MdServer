//
//
// Author : luojunbin
//

#ifndef DATAPARSE_H_
#define DATAPARSE_H_

#include <iostream>
#include <string>
#include <map>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "wzdatastruct.h"
#include "transportstruct.h"

using namespace rapidjson;
using std::map;
using std::vector;
using std::string;
using std::pair;

inline int parseTo(map<string, string> &my_map, string &json)
{
  Document doc;
  doc.Parse((char*)json.c_str());

  pair<string, string> tmp;
  char num_value[1024];
  for (Value::ConstMemberIterator it = doc.MemberBegin();
      it != doc.MemberEnd(); ++it) {
    if (it->value.IsString())
    {
      tmp.first = it->name.GetString();
      tmp.second = it->value.GetString();
      my_map.insert(tmp);
    }

  }
  return 0;
}

inline int parseFrom(map<string, string> &my_map, TSMarketDataField &res)
{
  char num_value[1024];

  my_map.insert(pair<string, string>("TradingDay", res.TradingDay));
  my_map.insert(pair<string, string>("InstrumentID", res.InstrumentID));

  sprintf(num_value, "%lf", res.LastPrice);
  my_map.insert(pair<string, string>("LastPrice", num_value));
  sprintf(num_value, "%lf", res.PreSettlementPrice);
  my_map.insert(pair<string, string>("PreSettlementPrice", num_value));
  sprintf(num_value, "%lf", res.PreClosePrice);
  my_map.insert(pair<string, string>("PreClosePrice", num_value));
  sprintf(num_value, "%lf", res.PreOpenInterest);
  my_map.insert(pair<string, string>("PreOpenInterest", num_value));
  sprintf(num_value, "%lf", res.OpenPrice);
  my_map.insert(pair<string, string>("OpenPrice", num_value));
  sprintf(num_value, "%lf", res.HighestPrice);
  my_map.insert(pair<string, string>("HighestPrice", num_value));
  sprintf(num_value, "%lf", res.LowestPrice);
  my_map.insert(pair<string, string>("LowestPrice", num_value));
  sprintf(num_value, "%d", res.Volume);
  my_map.insert(pair<string, string>("Volume", num_value));
  sprintf(num_value, "%lf", res.Turnover);
  my_map.insert(pair<string, string>("Turnover", num_value));
  sprintf(num_value, "%lf", res.OpenInterest);
  my_map.insert(pair<string, string>("OpenInterest", num_value));
  // sprintf(num_value, "%lf", res.ClosePrice);
  // my_map.insert(pair<string, string>("ClosePrice", num_value));

  // sprintf(num_value, "%lf", res.SettlementPrice);
  // my_map.insert(pair<string, string>("SettlementPrice", num_value));
  sprintf(num_value, "%lf", res.UpperLimitPrice);
  my_map.insert(pair<string, string>("UpperLimitPrice", num_value));
  sprintf(num_value, "%lf", res.LowerLimitPrice);
  my_map.insert(pair<string, string>("LowerLimitPrice", num_value));

  my_map.insert(pair<string, string>("UpdateTime", res.UpdateTime));
  sprintf(num_value, "%d", res.UpdateMillisec);
  my_map.insert(pair<string, string>("UpdateMillisec", num_value));
  sprintf(num_value, "%lf", res.BidPrice1);
  my_map.insert(pair<string, string>("BidPrice1", num_value));
  sprintf(num_value, "%d", res.BidVolume1);
  my_map.insert(pair<string, string>("BidVolume1", num_value));
  sprintf(num_value, "%lf", res.AskPrice1);
  my_map.insert(pair<string, string>("AskPrice1", num_value));
  sprintf(num_value, "%d", res.AskVolume1);
  my_map.insert(pair<string, string>("AskVolume1", num_value));
  return 0;
}

inline int parseFrom(map<string, string> &my_map, WZRtnOrderField &res)
{
  char num_value[1024];

  my_map.insert(pair<string, string> ("BrokerID", res.BrokerID));
  my_map.insert(pair<string, string> ("UserID", res.UserID));
  my_map.insert(pair<string, string> ("ParticipantID", res.ParticipantID));
  my_map.insert(pair<string, string> ("InvestorID", res.InvestorID));
  my_map.insert(pair<string, string> ("BusinessUnit", res.BusinessUnit));
  my_map.insert(pair<string, string> ("InstrumentID", res.InstrumentID));
  my_map.insert(pair<string, string> ("OrderRef", res.OrderRef));
  my_map.insert(pair<string, string> ("ExchangeID", res.ExchangeID));

  sprintf(num_value, "%lf", res.LimitPrice);
  my_map.insert(pair<string, string> ("LimitPrice", num_value));
  sprintf(num_value, "%d", res.VolumeTraded);
  my_map.insert(pair<string, string> ("VolumeTraded", num_value));
  sprintf(num_value, "%d", res.VolumeTotal);
  my_map.insert(pair<string, string> ("VolumeTotal", num_value));
  sprintf(num_value, "%d", res.VolumeTotalOriginal);
  my_map.insert(pair<string, string> ("VolumeTotalOriginal", num_value));
  sprintf(num_value, "%c", res.TimeCondition);
  my_map.insert(pair<string, string> ("TimeCondition", num_value));
  sprintf(num_value, "%c", res.VolumeCondition);
  my_map.insert(pair<string, string> ("VolumeCondition", num_value));
  sprintf(num_value, "%c", res.OrderPriceType);
  my_map.insert(pair<string, string> ("OrderPriceType", num_value));
  sprintf(num_value, "%c", res.Direction);
  my_map.insert(pair<string, string> ("Direction", num_value));
  sprintf(num_value, "%c", res.OffsetFlag);
  my_map.insert(pair<string, string> ("OffsetFlag", num_value));
  sprintf(num_value, "%c", res.HedgeFlag);
  my_map.insert(pair<string, string> ("HedgeFlag", num_value));
  sprintf(num_value, "%c", res.OrderStatus);
  my_map.insert(pair<string, string> ("OrderStatus", num_value));
  sprintf(num_value, "%d", res.RequestID);
  my_map.insert(pair<string, string> ("RequestID", num_value));

  return 0;
}

inline int parseFrom(map<string, string> &my_map, TSRtnOrderField &res)
{
  char num_value[1024];
  my_map.insert(pair<string, string> ("InstrumentID", res.InstrumentID));
  my_map.insert(pair<string, string> ("OrderRef", res.OrderRef));

  sprintf(num_value, "%lf", res.LimitPrice);
  my_map.insert(pair<string, string> ("LimitPrice", num_value));
  sprintf(num_value, "%d", res.VolumeTraded);
  my_map.insert(pair<string, string> ("VolumeTraded", num_value));
  sprintf(num_value, "%d", res.VolumeTotal);
  my_map.insert(pair<string, string> ("VolumeTotal", num_value));
  sprintf(num_value, "%d", res.VolumeTotalOriginal);
  my_map.insert(pair<string, string> ("VolumeTotalOriginal", num_value));

  sprintf(num_value, "%c", res.Direction);
  my_map.insert(pair<string, string> ("Direction", num_value));
  sprintf(num_value, "%c", res.OffsetFlag);
  my_map.insert(pair<string, string> ("OffsetFlag", num_value));
  sprintf(num_value, "%c", res.OrderStatus);
  my_map.insert(pair<string, string> ("OrderStatus", num_value));

  return 0;
}

inline int parseFrom(map<string, string> &my_map, WZRtnTradeField &res)
{
  char num_value[1024];

  my_map.insert(pair<string, string> ("BrokerID", res.BrokerID));
  my_map.insert(pair<string, string> ("UserID", res.UserID));
  my_map.insert(pair<string, string> ("InvestorID", res.InvestorID));
  my_map.insert(pair<string, string> ("BusinessUnit", res.BusinessUnit));
  my_map.insert(pair<string, string> ("InstrumentID", res.InstrumentID));
  my_map.insert(pair<string, string> ("OrderRef", res.OrderRef));
  my_map.insert(pair<string, string> ("ExchangeID", res.ExchangeID));
  my_map.insert(pair<string, string> ("TradeID", res.TradeID));
  my_map.insert(pair<string, string> ("OrderSysID", res.OrderSysID));
  my_map.insert(pair<string, string> ("ParticipantID", res.ParticipantID));
  my_map.insert(pair<string, string> ("ClientID", res.ClientID));

  sprintf(num_value, "%lf", res.Price);
  my_map.insert(pair<string, string> ("Price", num_value));
  sprintf(num_value, "%d", res.Volume);
  my_map.insert(pair<string, string> ("Volume", num_value));

  my_map.insert(pair<string, string> ("TradingDay", res.TradingDay));
  my_map.insert(pair<string, string> ("TradeTime", res.TradeTime));

  sprintf(num_value, "%c", res.Direction);
  my_map.insert(pair<string, string> ("Direction", num_value));
  sprintf(num_value, "%c", res.OffsetFlag);
  my_map.insert(pair<string, string> ("OffsetFlag", num_value));
  sprintf(num_value, "%c", res.HedgeFlag);
  my_map.insert(pair<string, string> ("HedgeFlag", num_value));

  return 0;
}

inline int parseFrom(map<string, string> &my_map, TSRtnTradeField &res)
{
  char num_value[1024];

  my_map.insert(pair<string, string> ("InstrumentID", res.InstrumentID));
  my_map.insert(pair<string, string> ("OrderRef", res.OrderRef));

  sprintf(num_value, "%lf", res.Price);
  my_map.insert(pair<string, string> ("Price", num_value));
  sprintf(num_value, "%d", res.Volume);
  my_map.insert(pair<string, string> ("Volume", num_value));


  my_map.insert(pair<string, string> ("TradingDay", res.TradingDay));
  my_map.insert(pair<string, string> ("TradeTime", res.TradeTime));

  sprintf(num_value, "%c", res.Direction);
  my_map.insert(pair<string, string> ("Direction", num_value));
  sprintf(num_value, "%c", res.OffsetFlag);
  my_map.insert(pair<string, string> ("OffsetFlag", num_value));

  return 0;
}

#endif