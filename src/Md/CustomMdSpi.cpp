//
//
// Author : huziang
// This is a cpp file, complete the function in class CustomMdSpi

#include "CustomMdSpi.h"
#include <memory.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcMdApi.h"
#include "MessageQueue.h"
#include "WZUtil/Logger.h"

#ifdef DEBUG
#include "test.h"
extern Time *mytime;
#endif

// using std::LOG(INFO);
using std::endl;

extern int requestID;
extern MessageQueue *que;
extern Logger *logger;

CustomMdSpi::CustomMdSpi(TThostFtdcInvestorIDType uid,
                         TThostFtdcPasswordType password,
                         char mdaddr[],
                         char datadirpath[]) {
  strcpy(Password, password);
  strcpy(InvestorID, uid);
  pUserApi = CThostFtdcMdApi::CreateFtdcMdApi(datadirpath);
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
  mytime->WriteName(pDepthMarketData->InstrumentID);
  mytime->WriteStart();
  char info[50];
  DLOG(DEBUG) << "===== Get Depth Market Data =====";
  DLOG(DEBUG) << "Trading Day: " << pDepthMarketData->TradingDay;
  DLOG(DEBUG) << "Exchange ID: " << pDepthMarketData->ExchangeID;
  DLOG(DEBUG) << "Instrument ID: " << pDepthMarketData->InstrumentID;
  sprintf(info, "Last Price: %lf", pDepthMarketData->LastPrice);
  DLOG(DEBUG) << info;
  sprintf(info, "Volume: %lf", pDepthMarketData->Volume);
  DLOG(DEBUG) << info;
  sprintf(info, "Turnover: %lf", pDepthMarketData->Turnover);
  DLOG(DEBUG) << info;
#endif

  TSMarketDataField pTSDepthMarketData;
  pTSDepthMarketData = parserFrom(*pDepthMarketData);
  this->RtnDepthMarketData(&pTSDepthMarketData);
  /*此处可将数据存入数据库*/
  que->send(&pTSDepthMarketData);

#ifdef DEBUG
  mytime->WriteEnd();
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