//
//
// Author: lijiaheng
// this is a base virtual class used in main.cpp

#ifndef MDSERVER_MDENGINE_H_
#define MDSERVER_MDENGINE_H_

#include "tsdatastruct.h"
#include "wzmem_inc/memengine.hpp"

class MdEngine {
 public:
  MdEngine(MemEngine<Frame, 1024, 1024>* _output = NULL)
      : output(_output) {}
  virtual void Init() = 0;
  virtual void Join() = 0;
  virtual void Release() = 0;
  virtual void ReqSubscribeMarketData(char *contracts[], int contractsnum) = 0;
  void SetOutput(MemEngine<Frame, 1024, 1024> *_output);
  void RtnDepthMarketData(TSMarketDataField* pDepthMarketData);

 private:
  // DISALLOW_COPY_AND_ASSIGN(MdEngine);
  MemEngine<Frame, 1024, 1024> *output;
  Frame frame;
};

#endif  // MDSERVER_MDENGINE_H_
