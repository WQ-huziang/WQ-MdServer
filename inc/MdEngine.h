//
//
// Author: lijiaheng
// this is a base virtual class used in main.cpp

#ifndef MDSERVER_MDENGINE_H_
#define MDSERVER_MDENGINE_H_

#include "wzconstant.h"
#include "tsdatastruct.h"
#include "wzsocket_inc/udp.h"

class MdEngine {
 public:
  MdEngine(WZPiper<UdpSocket>* _output = NULL)
      : output(_output) {}
  virtual void Init() = 0;
  virtual void Join() = 0;
  virtual void Release() = 0;
  virtual void ReqSubscribeMarketData(char *contracts[], int contractsnum) = 0;
  void SetOutput(WZPiper<UdpSocket> *_output);
  void RtnDepthMarketData(TSMarketDataField* pDepthMarketData);

 private:
  // DISALLOW_COPY_AND_ASSIGN(MdEngine);
  WZPiper<UdpSocket> *output;
};

#endif  // MDSERVER_MDENGINE_H_
