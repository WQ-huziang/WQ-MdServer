//
//
// Author : huziang
// this is a class send alert message

#ifndef MDSERVER_ALERT_H_
#define MDSERVER_ALERT_H_

#include <vector>
#include "wzdatastruct.h"
#include "WZUtil/UDPPiper.h"
#include "DataEngine.h"

typedef void (*Func)(TSMarketDataField&,DataEngine&,WZPiper&);

class Alert {
 public:
  void addTrigger(const Func func);
  void delTrigger(const Func func);
  void setOutput(WZPiper *_output) { output = _output; }
  void setDataEngine(DataEngine *_db) { mydb = _db; }
  void exec(TSMarketDataField &);
 private:
  DataEngine *mydb;
  WZPiper *output;
  std::vector<Func> funcs;
};

#endif  // MDSERVER_ALERT_H_