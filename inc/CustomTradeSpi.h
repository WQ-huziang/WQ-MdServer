#pragma once
#include <iostream>
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
using namespace std;
/*
extern TThostFtdcBrokerIDType BROKERID;//�����̴���
extern TThostFtdcInvestorIDType USERID;//Ͷ�����˺�
extern TThostFtdcPasswordType PASSWORD;//Ͷ��������
extern CThostFtdcTraderApi *g_pTradeUserApi;//���׽ӿ�ָ��
extern TThostFtdcInstrumentIDType g_pTradeInstrumentID;//�����׵ĺ�Լ����
extern int requestId;

TThostFtdcFrontIDType trade_front_id;//ǰ�ñ��
TThostFtdcSessionIDType session_id;//�Ự���
TThostFtdcOrderRefType max_order_ref;//�������
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
	bool trade_lock = false;//�����������ݵ�¼״̬�ж��Ƿ��ܽ��н��ס�false�����ܽ��ף�true�����Խ���

private:
	TThostFtdcBrokerIDType BrokerID = "9999";//�����̴���
	TThostFtdcInvestorIDType InvestorID;//Ͷ�����˺�
	TThostFtdcPasswordType Password;//Ͷ��������
	TThostFtdcInstrumentIDType TradeInstrumentID;//�����׵ĺ�Լ����
	//int requestID;

	TThostFtdcFrontIDType trade_front_id;//ǰ�ñ��
	TThostFtdcSessionIDType session_id;//�Ự���
	TThostFtdcOrderRefType max_order_ref;//�������
};