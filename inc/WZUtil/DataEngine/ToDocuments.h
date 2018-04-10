//
//
// Author : huziang
// this is a file include function struct to document

// struct TSMarketDataField
// {
//     char_13    TradingDay;            //交易日
//     char_31    InstrumentID;          //合约代码
//     double     LastPrice;             //最新价
//     double     PreSettlementPrice;    //上次结算价
//     double     PreClosePrice;         //昨收盘
//     double     PreOpenInterest;       //昨持仓量
//     double     OpenPrice;             //今开盘
//     double     HighestPrice;          //最高价
//     double     LowestPrice;           //最低价
//     int        Volume;                //数量
//     double     Turnover;              //成交金额
//     double     OpenInterest;          //持仓量
//     double     ClosePrice;            //今收盘
//     double     SettlementPrice;       //本次结算价
//     double     UpperLimitPrice;       //涨停板价
//     double     LowerLimitPrice;       //跌停板价
//     char_13    UpdateTime;            //最后修改时间
//     int        UpdateMillisec;        //最后修改毫秒
//     double     BidPrice1;             //申买价一
//     int        BidVolume1;            //申买量一
//     double     AskPrice1;             //申卖价一
//     int        AskVolume1;            //申卖量一
// };

#ifndef WZUTIL_TODOCUMENT_H_
#define WZUTIL_TODOCUMENT_H_

#include <iostream>
#include <map>
#include <string>
#include "DataEngine.h"
using std::map;
using std::vector;
using bsoncxx::builder::stream::document;

inline void keyvalueToDocument(const KeyValue &kv, document &doc) {
    if(kv.sides){
      if(kv.maxvalue != "" && kv.minvalue == ""){
        doc << kv.key << bsoncxx::builder::stream::open_document
            << "$lte" << kv.maxvalue
            << bsoncxx::builder::stream::close_document;
      }
      else if(kv.maxvalue == "" && kv.minvalue != ""){
        doc << kv.key << bsoncxx::builder::stream::open_document
            << "$gte" << kv.minvalue
            << bsoncxx::builder::stream::close_document;
      }
    }
    else{
      if(kv.maxvalue != ""){
        doc << kv.key << bsoncxx::builder::stream::open_document
            << "$gte" << kv.minvalue
            << "$lte" << kv.maxvalue
            << bsoncxx::builder::stream::close_document;
      } else {
        doc << kv.key << kv.minvalue;
      }
    }
}

void toDocument(const map<string, string> &md, document &doc) {
  for (auto &it : md) {
    doc << it.first << it.second;
  }
}

void toDocument(const vector<map<string, string>> & vmd, vector<bsoncxx::document::value> & docvs) {
  document doc {};
  for (auto &md : vmd) {
    toDocument(md, doc);
    docvs.push_back(doc << bsoncxx::builder::stream::finalize);
    doc.clear();
  }
}

/// key: column name
/// value: lowerbound & upperbound
/// ID: instrument id
void toDocument(const vector<KeyValue> &find, const char ID[20], document &doc) {
  if (strlen(ID) != 0) {
    doc << "InstrumentID" << ID;
  }
  for(auto &it : find){
    keyvalueToDocument(it, doc);
  }
}

//update one
void toDocument(const KeyValue &find, const vector<KeyValue> & value, document &doc_find, document &doc_update){
  if (find.maxvalue != "") {
    keyvalueToDocument(find, doc_find);
  }

  for(auto &it : value){
    doc_update << "$set" << bsoncxx::builder::stream::open_document
               << it.key << it.minvalue
               << bsoncxx::builder::stream::close_document;
  }
}


#endif  // WZUTIL_TODOCUMENT_H_
