#pragma once
#include <iostream>
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
using namespace std;
/*
extern TThostFtdcBrokerIDType BROKERID;//经纪商代码
extern TThostFtdcInvestorIDType USERID;//投资者账号
extern TThostFtdcPasswordType PASSWORD;//投资者密码
extern CThostFtdcTraderApi *g_pTradeUserApi;//交易接口指针
extern TThostFtdcInstrumentIDType g_pTradeInstrumentID;//所交易的合约代码
extern int requestId;

TThostFtdcFrontIDType trade_front_id;//前置编号
TThostFtdcSessionIDType session_id;//会话编号
TThostFtdcOrderRefType max_order_ref;//报单编号
*/

class CustomTradeSpi : public CThostFtdcTraderSpi {

public:
	CustomTradeSpi(TThostFtdcInvestorIDType uid, TThostFtdcPasswordType password, TThostFtdcInstrumentIDType IntrumentID);
	void OnFrontConnected();
	void OnFrontDisconnected(int nReason);
	void OnHeartBeatWarning(int nTimeLapse);
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRtnOrder(CThostFtdcOrderField *pOrder);
	void OnRtnTrade(CThostFtdcTradeField *pTrade);
	void ReqOrderInsert();
	void ReqUserLogout();

public:
	bool trade_lock = false;//交易锁，根据登录状态判断是否能进行交易。false：不能交易，true：可以交易

private:
	TThostFtdcBrokerIDType BrokerID = "9999";//经纪商代码
	TThostFtdcInvestorIDType InvestorID;//投资者账号
	TThostFtdcPasswordType Password;//投资者密码
	TThostFtdcInstrumentIDType TradeInstrumentID;//所交易的合约代码
	//int requestID;

	TThostFtdcFrontIDType trade_front_id;//前置编号
	TThostFtdcSessionIDType session_id;//会话编号
	TThostFtdcOrderRefType max_order_ref;//报单编号
};