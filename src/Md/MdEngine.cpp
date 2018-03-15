//
//
// Author : huziang
// This is a cpp file, complete the function in class MdEngine

#include "MdEngine.h"
#include "Frame.h"
#include "OutputAdapter.h"

void setOutput(OutputAdapter* _output) {
  output = _output;
}

void MdEngine::rtnDepthMarketData(WZMarketDataField* pDepthMarketData) {
  if (output != NULL) {
    Frame frame = parseTo(pDepthMarketData);
    output.write(frame);
  }
}