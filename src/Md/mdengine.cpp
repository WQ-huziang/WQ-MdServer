/***************************************************************************
Copyright(C) 2018, Wizard Quant
Author: huziang
Description: This is a cpp file, complete the function in class MdEngine
Date: 2018年5月3日 星期四 下午3:28
****************************************************************************/

#include "mdengine.h"
#include "frame.h"
#include "tsdatastruct.h"
#include "FM2TSparser.h"

void MdEngine::SetOutput(MemEngine<Frame, 1024, 1024> *_output) {
  output = _output;
}

void MdEngine::RtnDepthMarketData(TSMarketDataField* pDepthMarketData) {
  if (output != NULL) {
    parseTo(this->frame, *pDepthMarketData);
    output->Send(this->frame);
  }
}