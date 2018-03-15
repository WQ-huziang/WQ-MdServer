//
//
// Author: lijiaheng
// this is a base virtual class used in main.cpp

#ifndef MDSERVER_MDENGINE_H_
#define MDSERVER_MDENGINE_H_

#include "ctpwzadapter.h"
#include "wzconstant.h"
#include "wzdatastruct.h"

class OutputAdapter;

class MdEngine {
 public:
  MdEngine(OutputAdapter* _output = NULL)
      : output(_output) {}
  virtual void reqSubscribeMarketData() = 0;
  void setOutput(OutputAdapter* _output);
  void rtnDepthMarketData(WZMarketDataField* pDepthMarketData);

 private:
  DISALLOW_COPY_AND_ASSIGN(MdEngine);
  OutputAdapter* output;
};

#endif  // MDSERVER_MDENGINE_H_