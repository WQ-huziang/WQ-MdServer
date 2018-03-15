#include <iostream>
#include <string>
#include <thread>
#include <memory.h>
#include "CustomTradeSpi.h"
using namespace std;

extern int requestID;
extern CThostFtdcTraderApi *pTradeUserApi;//交易接口指针
extern TThostFtdcPriceType gLimitPrice;
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

CustomTradeSpi::CustomTradeSpi(TThostFtdcInvestorIDType uid, TThostFtdcPasswordType password, TThostFtdcInstrumentIDType IntrumentID) {
	strcpy(InvestorID, uid);
	strcpy(Password, password);
	strcpy(TradeInstrumentID, IntrumentID);
}

///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void CustomTradeSpi::OnFrontConnected() {
	cout << "网络连接成功，正在登录..." << endl;
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BrokerID);
	strcpy(req.UserID, InvestorID);
	strcpy(req.Password, Password);
	int ret = pTradeUserApi->ReqUserLogin(&req, requestID);
	if (!ret) {
		cout << "发送登录请求成功！" << endl;
	}
	else {
		cout << "发送登录请求失败" << endl;
	}
};

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
///@param nReason 错误原因
///        0x1001 网络读失败
///        0x1002 网络写失败
///        0x2001 接收心跳超时
///        0x2002 发送心跳失败
///        0x2003 收到错误报文
void CustomTradeSpi::OnFrontDisconnected(int nReason) {
	cout << "连接失败，错误码：" << nReason << endl;
};

///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
void CustomTradeSpi::OnHeartBeatWarning(int nTimeLapse) {
	cout << "网络心跳超时，距上次连接时间：" << nTimeLapse << endl;
};

///登录请求响应
void CustomTradeSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!pRspInfo->ErrorID) {
		trade_lock = true;
		cout << "登陆成功" << endl;
		cout << "交易日:" << pRspUserLogin->TradingDay << endl;
		cout << "登录时间:" << pRspUserLogin->LoginTime << endl;
		cout << "用户名:" << pRspUserLogin->UserID << endl;
		cout << "经济商:" << pRspUserLogin->BrokerID << endl;

		//保存会话信息
		trade_front_id = pRspUserLogin->FrontID;
		session_id = pRspUserLogin->SessionID;
		strcpy(max_order_ref, pRspUserLogin->MaxOrderRef);

		//发送投资者结算结果确认请求
		CThostFtdcSettlementInfoConfirmField settlementConfirmReq;
		memset(&settlementConfirmReq, 0, sizeof(settlementConfirmReq));
		strcpy(settlementConfirmReq.BrokerID, BrokerID);
		strcpy(settlementConfirmReq.InvestorID, InvestorID);
		static int requestID = 0;
		int ret = pTradeUserApi->ReqSettlementInfoConfirm(&settlementConfirmReq, requestID);
		if (!ret) {
			cout << "发送投资者结算结果确认请求成功" << endl;
		}
		else {
			cout << "发送投资者结算结果确认请求失败" << endl;
		}
	}
};

///登出请求响应
void CustomTradeSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!pRspInfo->ErrorID) {
		trade_lock = false;
		cout << "账户登出成功" << endl;
		cout << "经纪商：" << pUserLogout->BrokerID << endl;
		cout << "账户名：" << pUserLogout->UserID << endl;
		pTradeUserApi->Release();
	}
	else {
		cout << "登出失败" << endl;
	}
};

///报单录入请求响应
void CustomTradeSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (pInputOrder != nullptr && !pRspInfo->ErrorID) {
		cout << "报单录入成功" << endl;
		cout << "合约代码：" << pInputOrder->InstrumentID << endl;
		cout << "价格：" << pInputOrder->LimitPrice << endl;
		cout << "数量：" << pInputOrder->VolumeTotalOriginal << endl;
		cout << "开仓方向：" << pInputOrder->Direction << endl;
	}
	else {
		cout << "报单录入失败，错误代码：" << pRspInfo->ErrorID << ": " << pRspInfo->ErrorMsg << endl;
	}
};

///报单操作请求响应
void CustomTradeSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!pRspInfo->ErrorID) {
		cout << "报单操作成功" << endl;
		cout << "合约代码：" << pInputOrderAction->InstrumentID << endl;
		cout << "操作标志：" << pInputOrderAction->ActionFlag << endl;
	}
	else {
		cout << "报单操作失败" << endl;
	}
};

///投资者结算结果确认响应
void CustomTradeSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (!pRspInfo->ErrorID) {
		cout << "结算结果请求成功" << endl;
		///经纪公司代码
		cout << "经纪商：" << pSettlementInfoConfirm->BrokerID << endl;
		///投资者代码
		cout << "账户名：" << pSettlementInfoConfirm->InvestorID << endl;
		///确认日期
		cout << "确认日期：" << pSettlementInfoConfirm->ConfirmDate << endl;
		///确认时间
		cout << "确认时间：" << pSettlementInfoConfirm->ConfirmTime << endl;

		//发送查询合约请求
		CThostFtdcQryInstrumentField instrumentReq;
		memset(&instrumentReq, 0, sizeof(instrumentReq));
		strcpy(instrumentReq.InstrumentID, TradeInstrumentID);
		static int requestID = 0;
		int ret = pTradeUserApi->ReqQryInstrument(&instrumentReq, requestID);
		if (!ret) {
			cout << "发送合约查询请求成功" << endl;
		}
		else {
			cout << "发送合约查询请求失败" << endl;
		}
	}
};

///请求查询投资者持仓响应
void CustomTradeSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (pRspInfo != nullptr && !pRspInfo->ErrorID) {
		cout << "查询投资者持仓成功" << endl;
		if (pInvestorPosition != NULL) {
			cout << "合约代码：" << pInvestorPosition->InstrumentID << endl;
			cout << "开仓价格：" << pInvestorPosition->OpenAmount << endl;
			cout << "开仓量：" << pInvestorPosition->OpenVolume << endl;
			cout << "开仓方向：" << pInvestorPosition->PosiDirection << endl;
			cout << "占用保证金：" << pInvestorPosition->UseMargin << endl;

			//下单请求
			if (trade_lock) {
				cout << "发送报单请求" << endl;
				ReqOrderInsert();
			}

			/*
			//策略交易
			if (trade_lock) {
				//to do
			}
			*/

		}
		else {
			cout << "该合约未持仓" << endl;
		}
	}
	else if(pRspInfo == nullptr && pInvestorPosition != nullptr){

		cout << "查询投资者持仓成功" << endl;
		if (pInvestorPosition != NULL) {
			cout << "合约代码：" << pInvestorPosition->InstrumentID << endl;
			cout << "开仓价格：" << pInvestorPosition->OpenAmount << endl;
			cout << "开仓量：" << pInvestorPosition->OpenVolume << endl;
			cout << "开仓方向：" << pInvestorPosition->PosiDirection << endl;
			cout << "占用保证金：" << pInvestorPosition->UseMargin << endl;

			//下单请求
			if (trade_lock) {
				cout << "发送报单请求" << endl;
				ReqOrderInsert();
			}

			/*
			//策略交易
			if (trade_lock) {
			//to do
			}
			*/

		}
		else {
			cout << "该合约未持仓" << endl;
		}
	}
	else if (pInvestorPosition == nullptr && pRspInfo == nullptr) {
		cout << "无持仓信息" << endl;

		//下单请求
		if (trade_lock) {
			cout << "发送报单请求" << endl;
			ReqOrderInsert();
		}
	}
	else {
		cout << "查询投资者持仓失败" << endl;
	}
};

///请求查询资金账户响应
void CustomTradeSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (pRspInfo != nullptr && !pRspInfo->ErrorID) {
		cout << "查询投资者资金账户成功" << endl;
		cout << "账户名：" << pTradingAccount->AccountID << endl;
		cout << "可用资金：" << pTradingAccount->Available << endl;
		cout << "可取资金：" << pTradingAccount->WithdrawQuota << endl;
		cout << "当前保证金：" << pTradingAccount->CurrMargin << endl;
		cout << "平仓盈亏：" << pTradingAccount->CloseProfit << endl;

		//请求查询投资者持仓
		CThostFtdcQryInvestorPositionField positionReq;
		memset(&positionReq, 0, sizeof(positionReq));
		strcpy(positionReq.BrokerID, BrokerID);
		strcpy(positionReq.InvestorID, InvestorID);
		strcpy(positionReq.InstrumentID, TradeInstrumentID);
		static int requestID = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		int ret = pTradeUserApi->ReqQryInvestorPosition(&positionReq, requestID);
		if (!ret) {
			cout << "发送投资者持仓查询成功" << endl;
		}
		else {
			cout << "发送投资者持仓查询失败，错误代码：" << ret << endl;
		}
	}
	else if (pRspInfo == nullptr && pTradingAccount != nullptr) {
		cout << "查询投资者资金账户成功" << endl;
		cout << "账户名：" << pTradingAccount->AccountID << endl;
		cout << "可用资金：" << pTradingAccount->Available << endl;
		cout << "可取资金：" << pTradingAccount->WithdrawQuota << endl;
		cout << "当前保证金：" << pTradingAccount->CurrMargin << endl;
		cout << "平仓盈亏：" << pTradingAccount->CloseProfit << endl;

		//请求查询投资者持仓
		CThostFtdcQryInvestorPositionField positionReq;
		memset(&positionReq, 0, sizeof(positionReq));
		strcpy(positionReq.BrokerID, BrokerID);
		strcpy(positionReq.InvestorID, InvestorID);
		strcpy(positionReq.InstrumentID, TradeInstrumentID);
		static int requestID = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		int ret = pTradeUserApi->ReqQryInvestorPosition(&positionReq, requestID);
		if (!ret) {
			cout << "发送投资者持仓查询成功" << endl;
		}
		else {
			cout << "发送投资者持仓查询失败" << ret << endl;
		}
	}
	else {
		cout << "查询资金账户失败" << pRspInfo->ErrorID << endl;
	}
};

///请求查询合约响应
void CustomTradeSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (pRspInfo != nullptr && !pRspInfo->ErrorID) {
		cout << "查询合约成功" << endl;
		cout << "交易所代码：" << pInstrument->ExchangeID << endl;
		cout << "合约代码：" << pInstrument->InstrumentID << endl;
		cout << "合约所在交易所代码：" << pInstrument->ExchangeInstID << endl;
		cout << "执行价：" << pInstrument->StrikePrice << endl;
		cout << "到期日：" << pInstrument->EndDelivDate << endl;
		cout << "当前交易状态：" << pInstrument->IsTrading << endl;

		//请求查询投资者账户
		CThostFtdcQryTradingAccountField tradingAccountReq;
		memset(&tradingAccountReq, 0, sizeof(tradingAccountReq));
		strcpy(tradingAccountReq.BrokerID, BrokerID);
		strcpy(tradingAccountReq.InvestorID, InvestorID);
		static int requestID = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		int ret = pTradeUserApi->ReqQryTradingAccount(&tradingAccountReq, requestID);
		if (!ret) {
			cout << "发送资金账户查询成功" << endl;
		}
		else {
			cout << "发送资金账户查询失败，错误代码：" << ret << endl;
		}
	}
	else if (pRspInfo == nullptr) {
		//请求查询投资者账户
		CThostFtdcQryTradingAccountField tradingAccountReq;
		memset(&tradingAccountReq, 0, sizeof(tradingAccountReq));
		strcpy(tradingAccountReq.BrokerID, BrokerID);
		strcpy(tradingAccountReq.InvestorID, InvestorID);
		static int requestID = 0;
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		int ret = pTradeUserApi->ReqQryTradingAccount(&tradingAccountReq, requestID);
		if (!ret) {
			cout << "发送资金账户查询成功" << endl;
		}
		else {
			cout << "发送资金账户查询失败，错误代码：" << ret << endl;
		}
	}
	else {
		cout << "查询合约失败" << endl;
	}
};

///报单通知
void CustomTradeSpi::OnRtnOrder(CThostFtdcOrderField *pOrder) {
	char status[10];
	sprintf(status, "%d", pOrder->OrderSubmitStatus);
	int orderState = atoi(status) - 48;//0已提交，3已接受
	cout << "收到报单应答" << endl;

	if ((pOrder->SessionID == session_id) && (pOrder->FrontID == trade_front_id) && (strcmp(pOrder->OrderRef, max_order_ref) == 0)) {
		if ((pOrder->OrderStatus != THOST_FTDC_OST_AllTraded) && (pOrder->OrderStatus != THOST_FTDC_OST_Canceled) && (pOrder->OrderStatus != THOST_FTDC_OST_PartTradedNotQueueing)) {
			cout << "等待成交中" << endl;
		}
		else if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled) {
			cout << "撤单成功" << endl;
			ReqUserLogout();
		}
	}
};

///成交通知
void CustomTradeSpi::OnRtnTrade(CThostFtdcTradeField *pTrade) {
	cout << "报单成功成交" << endl;
	cout << "成交时间：" << pTrade->TradeTime << endl;
	cout << "合约代码：" << pTrade->InstrumentID << endl;
	cout << "成交价格：" << pTrade->Price << endl;
	cout << "成交量：" << pTrade->Volume << endl;
	cout << "开平仓方向：" << pTrade->Direction << endl;
};

//发送报单请求
void CustomTradeSpi::ReqOrderInsert() {
	CThostFtdcInputOrderField orderInsert;
	memset(&orderInsert, 0, sizeof(orderInsert));
	strcpy(orderInsert.BrokerID, BrokerID); //经纪商代码
	strcpy(orderInsert.InvestorID, InvestorID); //投资人代码
	strcpy(orderInsert.InstrumentID, TradeInstrumentID); //交易合约
	strcpy(orderInsert.OrderRef, max_order_ref); //报单引用

	orderInsert.Direction = THOST_FTDC_D_Buy; //买卖方向
	orderInsert.CombOffsetFlag[0] = THOST_FTDC_OF_Open; //组合开平标志：开仓
	orderInsert.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation; //组合投机套保标志
	orderInsert.VolumeTotalOriginal = 1; //数量
	orderInsert.VolumeCondition = THOST_FTDC_VC_AV; //成交类型：任何数量
	orderInsert.MinVolume = 1; //最小成交量：1
	orderInsert.ForceCloseReason = THOST_FTDC_FCC_NotForceClose; //强平原因：非强平
	orderInsert.IsAutoSuspend = 0; //自动挂起标志：否
	orderInsert.UserForceClose = 0; //用户强评标志：否

	//限价单
	orderInsert.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	orderInsert.LimitPrice = gLimitPrice;
	orderInsert.TimeCondition = THOST_FTDC_TC_GFD; //有效期类型：当日有效
	orderInsert.ContingentCondition = THOST_FTDC_CC_Immediately; //触发条件

	static int requestID = 0;
	int ret = pTradeUserApi->ReqOrderInsert(&orderInsert, ++requestID);
	//cout << ret << endl;
	if (!ret) {
		cout << "发送报单录入请求成功" << endl;
	}
	else {
		cout << "发送报单录入请求失败，错误代码：" << ret << endl;
	}
}

void CustomTradeSpi::ReqUserLogout() {
	CThostFtdcUserLogoutField logoutReq;
	memset(&logoutReq, 0, sizeof(logoutReq));
	strcpy(logoutReq.BrokerID, BrokerID);
	strcpy(logoutReq.UserID, InvestorID);
	static int requestID = 0;
	int ret = pTradeUserApi->ReqUserLogout(&logoutReq, requestID);
	if (!ret) {
		cout << "发出登出请求成功" << endl;
	}
	else {
		cout << "发出登出请求失败，错误代码：" << ret << endl;
	}
}
