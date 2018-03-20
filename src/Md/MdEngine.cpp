//
//
// Author : huziang
// This is a cpp file, complete the function in class MdEngine

#include "MdEngine.h"
#include "OutputAdapter/Frame.h"
#include "OutputAdapter/OutputAdapter.h"

// struct Frame{
//     short source;
//     short msg_type;
//     short error_id;
//     short rtn_type;
//     int length;
//     char data[500];
// };

Frame parseTo(WZMarketDataField &pDepthMarketData) {
  Frame frame = {};
  frame.source = WZ_SOURCE_CTP;
  frame.msg_type = WZ_MSG_TYPE_MARKET_DATA;
  frame.error_id = WZ_ERROR_ID_SUCCESS;
  frame.rtn_type = 0;
  frame.length = sizeof(pDepthMarketData);
  memcpy(&frame.data, &pDepthMarketData, frame.length);
  return frame;
}

void MdEngine::SetOutput(OutputAdapter* _output) {
  output = _output;
}

void MdEngine::RtnDepthMarketData(WZMarketDataField* pDepthMarketData) {
  if (output != NULL) {
    Frame frame = parseTo(*pDepthMarketData);
    output->send(frame);
  }
}