/***************************************************************************
Copyright(C) 2018, Wizard Quant
Author: huziang
Description: This is a cpp file, complete the function in class CustomMdSpi
Date: 2018年5月3日 星期四 下午3:27
****************************************************************************/

#include "custommdspi.h"
#include <memory.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcMdApi.h"
#include "logger.h"
#include "TS2CTPparser.h"
#include "timer.h"
#include "fqueue.h"

#ifdef DEBUG
unsigned long long recvtime[TIMES];
unsigned long long sendtime[TIMES];
static long timenum = 0;
static long beginnum = 0;
#endif

using std::endl;
using std::string;

int requestID = 0;
extern FQueue<TSMarketDataField*> que;
extern Logger *logger;

/***************************************************************************
Description: This is a small memory pool, without delete and lock,
            please quickly get data, or this data will be covered
****************************************************************************/
TSMarketDataField memorypool[1024];
int memorypooladdr = 0;
TSMarketDataField *pTSDepthMarketData;
inline TSMarketDataField* newTSMarketDataField() {
  memorypooladdr = memorypooladdr == 1024 - 1 ? 0 : memorypooladdr + 1;
  return memorypool + memorypooladdr; 
}

void CustomMdSpi::ReqSubscribeMarketData(char *contracts[], int contractsnum){
  int ret = pUserApi->SubscribeMarketData(contracts, contractsnum);
  if (!ret) {
    LOG(INFO) << "发送行情请求成功";
  }
  else {
    LOG(INFO) << "发送行情请求失败";
  }
}

void CustomMdSpi::ReqUserLogin(){
  CThostFtdcReqUserLoginField req;
  memset(&req, 0, sizeof(req));
  strcpy(req.BrokerID, BrokerID);
  strcpy(req.UserID, InvestorID);
  strcpy(req.Password, Password);
  int ret = pUserApi->ReqUserLogin(&req, requestID++);
  if (!ret) {
    LOG(INFO) << "发送登录请求成功！";
  }
  else {
    LOG(INFO) << "发送登录请求失败";
  }
}

//登录检测
void CustomMdSpi::OnFrontConnected() {
  LOG(INFO) << "连接成功，正在登录...";
  ReqUserLogin();
};

void CustomMdSpi::OnFrontDisconnected(int nReason) {
  char info[50];
  sprintf(info, "连接失败，错误码：%d", nReason);
  LOG(INFO) << info;
};

///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
void CustomMdSpi::OnHeartBeatWarning(int nTimeLapse) {
  char info[50];
  sprintf(info, "超时，距上次连接时间：%d", nTimeLapse);
  LOG(INFO) << info;
};


///登录请求响应,并发送行情请求
void CustomMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (!pRspInfo->ErrorID) {
    LOG(INFO) << "登录成功";
    LOG(INFO) << "交易日:" << pRspUserLogin->TradingDay;
    LOG(INFO) << "登录时间:" << pRspUserLogin->LoginTime;
    LOG(INFO) << "用户名:" << pRspUserLogin->UserID;
    LOG(INFO) << "经济商:" << pRspUserLogin->BrokerID;
  }
  else {
    LOG(INFO) << "登录失败，错误信息：" << pRspInfo->ErrorMsg;
  }
};

///登出请求响应
void CustomMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (!pRspInfo->ErrorID) {
    LOG(INFO) << "账户登出成功";
    LOG(INFO) << "经纪商：" << pUserLogout->BrokerID;
    LOG(INFO) << "账户名：" << pUserLogout->UserID;
  }
  else {
    LOG(INFO) << "账户登出失败";
  }
};

///错误应答
void CustomMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (pRspInfo->ErrorID) {
    LOG(INFO) << "错误应答，错误信息：" << pRspInfo->ErrorMsg;
  }
};

///订阅行情应答
void CustomMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (!pRspInfo->ErrorID) {
    LOG(INFO) << "行情订阅成功";
    LOG(INFO) << "合约代码：" << pSpecificInstrument->InstrumentID;
    /*此处可将数据存入数据库*/
    /*      to do       */
  }
  else {
    LOG(INFO) << "行情订阅失败";
  }
};

///取消订阅行情应答
void CustomMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (!pRspInfo->ErrorID) {
    LOG(INFO) << "取消订阅行情成功";
    LOG(INFO) << "合约代码：" << pSpecificInstrument->InstrumentID;
  }
  else {
    LOG(INFO) << "取消行情订阅成功";
  }
};

///订阅询价应答
void CustomMdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (!pRspInfo->ErrorID) {
    LOG(INFO) << "询价订阅成功";
    LOG(INFO) << "合约代码：" << pSpecificInstrument->InstrumentID;
  }
  else {
    LOG(INFO) << "询价订阅失败";
  }
};

///取消订阅询价应答
void CustomMdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (!pRspInfo->ErrorID) {
    LOG(INFO) << "取消询价订阅成功";
    LOG(INFO) << "合约代码：";
  }
  else {
    LOG(INFO) << "取消询价订阅失败";
  }
};

///深度行情通知
void CustomMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
#ifdef DEBUG
  if (timenum == TIMES) {
    return;
  }
  recvtime[timenum] = getTimeByTSC();
  // std::cerr << "===== Get Depth Market Data =====" << endl;
  // std::cerr << "Num: " << timenum << endl;

  // std::cerr << "Trading Day: " << pDepthMarketData->TradingDay << endl;
  // std::cerr << "Exchange ID: " << pDepthMarketData->ExchangeID << endl;
  // std::cerr << "Instrument ID: " << pDepthMarketData->InstrumentID << endl;
  // std::cerr << "Last Price: " << pDepthMarketData->LastPrice << endl;
  // std::cerr << "Volume: " << pDepthMarketData->Volume << endl;
  // std::cerr << "Turnover: " << pDepthMarketData->Turnover << endl;
#endif

  // get TS's pointer, and transform CTP to TS
  pTSDepthMarketData = newTSMarketDataField();
  parseFrom(*pTSDepthMarketData, *pDepthMarketData);
  
  // send data to other processes
  this->RtnDepthMarketData(pTSDepthMarketData);

  // send data to other threads
  que.push(pTSDepthMarketData);

#ifdef DEBUG
  sendtime[timenum++] = getTimeByTSC();
#endif
};

///询价通知
void CustomMdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
  LOG(INFO) << "询价结果";
  ///交易日
  LOG(INFO) << pForQuoteRsp->TradingDay;
  ///合约代码
  LOG(INFO) << pForQuoteRsp->InstrumentID;
  ///询价编号
  LOG(INFO) << pForQuoteRsp->ForQuoteSysID;
  ///询价时间
  LOG(INFO) << pForQuoteRsp->ForQuoteTime;
  ///业务日期
  LOG(INFO) << pForQuoteRsp->ActionDay;
  ///交易所代码
  LOG(INFO) << pForQuoteRsp->ExchangeID;
};

CustomMdSpi::CustomMdSpi(TThostFtdcInvestorIDType uid,
                         TThostFtdcPasswordType password,
                         char *mdaddr, 
                         char *datadir) {
  strcpy(Password, password);
  strcpy(InvestorID, uid);
  strcpy(BrokerID, "9999");
  pUserApi = CThostFtdcMdApi::CreateFtdcMdApi(datadir);
  pUserApi->RegisterSpi(this);
  pUserApi->RegisterFront(mdaddr);
}

void CustomMdSpi::Init() {
  pUserApi->Init();
}

void CustomMdSpi::Join(){
  pUserApi->Join();
}

void CustomMdSpi::Release() {
  pUserApi->Release();
}
