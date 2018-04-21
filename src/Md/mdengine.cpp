//
//
// Author : huziang
// This is a cpp file, complete the function in class MdEngine

#include "mdengine.h"
#include "frame.h"
#include "tsdatastruct.h"
#include "FM2TSparser.h"

// Frame parseTo(TSMarketDataField &pDepthMarketData) {

//   Frame frame = {};
//   frame.source = WZ_SOURCE_CTP;
//   frame.msg_type = WZ_MSG_TYPE_MARKET_DATA;
//   frame.error_id = WZ_ERROR_ID_SUCCESS;
//   frame.rtn_type = 0;
//   frame.length = sizeof(pDepthMarketData);
//   memcpy(&frame.data.market, &pDepthMarketData, frame.length);


//   return frame;
// }

void MdEngine::SetOutput(WZPiper<UdpSocket> *_output) {
  output = _output;
}

void MdEngine::RtnDepthMarketData(TSMarketDataField* pDepthMarketData) {
  if (output != NULL) {
    Frame frame;
    parseTo(frame, *pDepthMarketData);
    output->Send(frame);
  }
}