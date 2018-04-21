//
//
// Author : huziang
// this include alert functions

#ifndef MDSERVER_ALERTTHREAD_H_
#define MDSERVER_ALERTTHREAD_H_

#include <vector>
#include <cstring>
#include "alert.h"
#include "MongodbEngine.h"
#include "WZUtil/UDPPiper.h"
#include "alertthread.h"
#include "Parser.h"
#include "transportstruct.h"
#include "MessageQueue.h"
using std::vector;

Alert *alertengine;
MessageQueue *alertque;
extern DataEngine *db;
extern WZPiper *udppiper;

inline void timeToInt(const char *time, int &ti) {
  int hour, min, sec;
  sscanf(time, "%d:%d:%d", &hour, &min, &sec);
  ti = hour * 3600 + min * 60 + sec;
}

inline void intToTime(const int ti, char *time) {
  sprintf(time, "%d:%d:%d", ti / 3600, (ti % 3600) / 60, ti % 60);
}

void triggerUpperLimit(TSMarketDataField &md, DataEngine &db, WZPiper &output);
void triggerLowerLimit(TSMarketDataField &md, DataEngine &db, WZPiper &output);
void triggerRiseAlert(TSMarketDataField &md, DataEngine &db, WZPiper &output);
void triggerFallAlert(TSMarketDataField &md, DataEngine &db, WZPiper &output);

void alertThread() {
  TSMarketDataField *pDepthMarketData = new TSMarketDataField;
  alertque = new MessageQueue(sizeof(*pDepthMarketData), 600);
  alertengine = new Alert();
  alertengine->setOutput(udppiper);
  alertengine->setDataEngine(db);

  // add trigger
  alertengine->addTrigger(triggerUpperLimit);
  alertengine->addTrigger(triggerLowerLimit);
  alertengine->addTrigger(triggerRiseAlert);
  alertengine->addTrigger(triggerFallAlert);

  while(1){
    if(alertque->receive(pDepthMarketData)){
      alertengine->exec(*pDepthMarketData);
    }
  }
}

void triggerUpperLimit(TSMarketDataField &md, DataEngine &db, WZPiper &output) {
  if (md.LastPrice >= md.UpperLimitPrice) {
    TSAlertField alert;
    strcpy(md.InstrumentID, alert.InstrumentID);
    strcat(alert.InstrumentID, " is upper limit!");
    Frame f;
    parserTo(alert, f);
    output.do_write(f);
  }
}

void triggerLowerLimit(TSMarketDataField &md, DataEngine &db, WZPiper &output) {
  if (md.LastPrice <= md.LowerLimitPrice) {
    TSAlertField alert;
    strcpy(md.InstrumentID, alert.InstrumentID);
    strcat(alert.InstrumentID, " is lower limit!");
    Frame f;
    parserTo(alert, f);
    output.do_write(f);
  }
}

void triggerRiseAlert(TSMarketDataField &md, DataEngine &db, WZPiper &output) {
  map<string, string> value;
  vector<KeyValue> kvs;
  char begintime[20];
  char endtime[20];
  int ti;
  timeToInt(md.UpdateTime, ti);
  intToTime(ti - 330, begintime);
  intToTime(ti - 270, endtime);
  kvs.push_back(KeyValue("UpdateTime", begintime, endtime));
  int res = db.find_one(value, kvs, md.InstrumentID);
  if (res && md.LastPrice > atof(value["LastPrice"].c_str()) * 1.04) {
    TSAlertField alert;
    strcpy(md.InstrumentID, alert.InstrumentID);
    strcat(alert.InstrumentID, " is upper to much!!");
    Frame f;
    parserTo(alert, f);
    output.do_write(f);
  }
}

void triggerFallAlert(TSMarketDataField &md, DataEngine &db, WZPiper &output) {
  map<string, string> value;
  vector<KeyValue> kvs;
  char begintime[20];
  char endtime[20];
  int ti;
  timeToInt(md.UpdateTime, ti);
  intToTime(ti - 330, begintime);
  intToTime(ti - 270, endtime);
  kvs.push_back(KeyValue("UpdateTime", begintime, endtime));
  int res = db.find_one(value, kvs, md.InstrumentID);
  if (res && md.LastPrice < atof(value["LastPrice"].c_str()) * 0.96) {
    TSAlertField alert;
    strcpy(md.InstrumentID, alert.InstrumentID);
    strcat(alert.InstrumentID, " is lower to much!!");
    Frame f;
    parserTo(alert, f);
    output.do_write(f);
  }
}

#endif  // MDSERVER_ALERTTHREAD_H_