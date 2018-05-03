//
//
// Author : huziang
// This is a cpp file, complete the function in class MdEngine

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