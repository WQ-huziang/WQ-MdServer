/*
 * @Author: w2w 
 * @Date: 2018-02-27 21:41:24 
 * @Last Modified by: w2w
 * @Last Modified time: 2018-02-28 12:03:10
 */
#ifndef CTP_WZ_ADAPTER_H
#define CTP_WZ_ADAPTER_H

// #include <wzdatastruct.h>
#include <string.h>
#include "transportstruct.h"

#include <ThostFtdcUserApiStruct.h>

inline struct TSMarketDataField parserFrom(const CThostFtdcDepthMarketDataField &req){
	TSMarketDataField rtn;
	strcpy(rtn.TradingDay, req.TradingDay);
	strcpy(rtn.InstrumentID, req.InstrumentID);
	rtn.LastPrice = req.LastPrice;
	rtn.PreSettlementPrice = req.PreSettlementPrice;
	rtn.PreClosePrice = req.PreClosePrice;
	rtn.PreOpenInterest = req.PreOpenInterest;
	rtn.OpenPrice = req.OpenPrice;
	rtn.HighestPrice = req.HighestPrice;
	rtn.LowestPrice = req.LowestPrice;
	rtn.Volume = req.Volume;
	rtn.Turnover = req.Turnover;
	rtn.OpenInterest = req.OpenInterest;
	rtn.ClosePrice = req.ClosePrice;
	rtn.SettlementPrice = req.SettlementPrice;
	rtn.UpperLimitPrice = req.UpperLimitPrice;
	rtn.LowerLimitPrice = req.LowerLimitPrice;
	strcpy(rtn.UpdateTime, req.UpdateTime);
	rtn.UpdateMillisec = req.UpdateMillisec;
	rtn.BidPrice1 = req.BidPrice1;
	rtn.BidVolume1 = req.BidVolume1;
	rtn.AskPrice1 = req.AskPrice1;
	rtn.AskVolume1 = req.AskVolume1;
	return rtn;
}
/*
inline struct WZQryPositionField parseFrom(const struct CThostFtdcQryInvestorPositionField& ori)
{
	struct WZQryPositionField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	return res;
}

inline struct CThostFtdcQryInvestorPositionField parseTo(const struct WZQryPositionField& lf)
{
	struct CThostFtdcQryInvestorPositionField res = {};
	memcpy(res.BrokerID, lf.BrokerID, 11);
	memcpy(res.InvestorID, lf.InvestorID, 13);
	memcpy(res.InstrumentID, lf.InstrumentID, 31);
	return res;
}

inline struct WZRspPositionField parseFrom(const struct CThostFtdcInvestorPositionField& ori)
{
	struct WZRspPositionField res = {};
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	res.YdPosition = (int)(ori.Position - ori.TodayPosition);
	res.Position = ori.Position;
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	res.PositionCost = ori.PositionCost;
	res.HedgeFlag = ori.HedgeFlag;
	res.PosiDirection = ori.PosiDirection;
	return res;
}

inline struct WZInputOrderField parseFrom(const struct CThostFtdcInputOrderField& ori)
{
	struct WZInputOrderField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.UserID, ori.UserID, 16);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	memcpy(res.BusinessUnit, ori.BusinessUnit, 21);
	memcpy(res.ExchangeID, ori.ExchangeID, 9);
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	memcpy(res.OrderRef, ori.OrderRef, 13);
	res.LimitPrice = ori.LimitPrice;
	res.Volume = ori.VolumeTotalOriginal;
	res.MinVolume = ori.MinVolume;
	res.TimeCondition = ori.TimeCondition;
	res.VolumeCondition = ori.VolumeCondition;
	res.OrderPriceType = ori.OrderPriceType;
	res.Direction = ori.Direction;
	res.OffsetFlag = ori.CombOffsetFlag[0];
	res.HedgeFlag = ori.CombHedgeFlag[0];
	res.ForceCloseReason = ori.ForceCloseReason;
	res.StopPrice = ori.StopPrice;
	res.IsAutoSuspend = ori.IsAutoSuspend;
	res.ContingentCondition = ori.ContingentCondition;
	return res;
}

inline struct CThostFtdcInputOrderField parseTo(const struct WZInputOrderField& WZ)
{
	struct CThostFtdcInputOrderField res = {};
	memcpy(res.BrokerID, WZ.BrokerID, 11);
	memcpy(res.UserID, WZ.UserID, 16);
	memcpy(res.InvestorID, WZ.InvestorID, 13);
	memcpy(res.BusinessUnit, WZ.BusinessUnit, 21);
	memcpy(res.ExchangeID, WZ.ExchangeID, 9);
	memcpy(res.InstrumentID, WZ.InstrumentID, 31);
	memcpy(res.OrderRef, WZ.OrderRef, 13);
	res.LimitPrice = WZ.LimitPrice;
	res.VolumeTotalOriginal = WZ.Volume;
	res.MinVolume = WZ.MinVolume;
	res.TimeCondition = WZ.TimeCondition;
	res.VolumeCondition = WZ.VolumeCondition;
	res.OrderPriceType = WZ.OrderPriceType;
	res.Direction = WZ.Direction;
	res.CombOffsetFlag[0] = WZ.OffsetFlag;
	res.CombHedgeFlag[0] = WZ.HedgeFlag;
	res.ForceCloseReason = WZ.ForceCloseReason;
	res.StopPrice = WZ.StopPrice;
	res.IsAutoSuspend = WZ.IsAutoSuspend;
	res.ContingentCondition = WZ.ContingentCondition;
	// 自己加的
	strcpy(res.GTDDate, "");
	return res;
}

inline struct WZRtnOrderField parseFrom(const struct CThostFtdcOrderField& ori)
{
	struct WZRtnOrderField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.UserID, ori.UserID, 16);
	memcpy(res.ParticipantID, ori.ParticipantID, 11);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	memcpy(res.BusinessUnit, ori.BusinessUnit, 21);
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	memcpy(res.OrderRef, ori.OrderRef, 13);
	memcpy(res.ExchangeID, ori.ExchangeID, 9);
	res.LimitPrice = ori.LimitPrice;
	res.VolumeTraded = ori.VolumeTraded;
	res.VolumeTotal = ori.VolumeTotal;
	res.VolumeTotalOriginal = ori.VolumeTotalOriginal;
	res.TimeCondition = ori.TimeCondition;
	res.VolumeCondition = ori.VolumeCondition;
	res.OrderPriceType = ori.OrderPriceType;
	res.Direction = ori.Direction;
	res.OffsetFlag = ori.CombOffsetFlag[0];
	res.HedgeFlag = ori.CombHedgeFlag[0];
	res.OrderStatus = ori.OrderStatus;
	res.RequestID = ori.RequestID;
	return res;
}

inline struct WZRtnTradeField parseFrom(const struct CThostFtdcTradeField& ori)
{
	struct WZRtnTradeField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.UserID, ori.UserID, 16);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	memcpy(res.BusinessUnit, ori.BusinessUnit, 21);
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	memcpy(res.OrderRef, ori.OrderRef, 13);
	memcpy(res.ExchangeID, ori.ExchangeID, 9);
	memcpy(res.TradeID, ori.TradeID, 21);
	memcpy(res.OrderSysID, ori.OrderSysID, 21);
	memcpy(res.ParticipantID, ori.ParticipantID, 11);
	memcpy(res.ClientID, ori.ClientID, 11);
	res.Price = ori.Price;
	res.Volume = ori.Volume;
	memcpy(res.TradingDay, ori.TradingDay, 13);
	memcpy(res.TradeTime, ori.TradeTime, 9);
	res.Direction = ori.Direction;
	res.OffsetFlag = ori.OffsetFlag;
	res.HedgeFlag = ori.HedgeFlag;
	return res;
}

inline struct WZOrderActionField parseFrom(const struct CThostFtdcInputOrderActionField& ori)
{
	struct WZOrderActionField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	memcpy(res.InstrumentID, ori.InstrumentID, 31);
	memcpy(res.ExchangeID, ori.ExchangeID, 9);
	memcpy(res.UserID, ori.UserID, 16);
	memcpy(res.OrderRef, ori.OrderRef, 13);
	memcpy(res.OrderSysID, ori.OrderSysID, 21);
	res.RequestID = ori.RequestID;
	res.ActionFlag = ori.ActionFlag;
	res.LimitPrice = ori.LimitPrice;
	res.VolumeChange = ori.VolumeChange;
	return res;
}

inline struct CThostFtdcInputOrderActionField parseTo(const struct WZOrderActionField& WZ)
{
	struct CThostFtdcInputOrderActionField res = {};
	memcpy(res.BrokerID, WZ.BrokerID, 11);
	memcpy(res.InvestorID, WZ.InvestorID, 13);
	memcpy(res.InstrumentID, WZ.InstrumentID, 31);
	memcpy(res.ExchangeID, WZ.ExchangeID, 9);
	memcpy(res.UserID, WZ.UserID, 16);
	memcpy(res.OrderRef, WZ.OrderRef, 13);
	memcpy(res.OrderSysID, WZ.OrderSysID, 21);
	res.RequestID = WZ.RequestID;
	res.ActionFlag = WZ.ActionFlag;
	res.LimitPrice = WZ.LimitPrice;
	res.VolumeChange = WZ.VolumeChange;
	return res;
}

inline struct WZQryAccountField parseFrom(const struct CThostFtdcQryTradingAccountField& ori)
{
	struct WZQryAccountField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.InvestorID, ori.InvestorID, 13);
	return res;
}

inline struct CThostFtdcQryTradingAccountField parseTo(const struct WZQryAccountField& lf)
{
	struct CThostFtdcQryTradingAccountField res = {};
	memcpy(res.BrokerID, lf.BrokerID, 11);
	memcpy(res.InvestorID, lf.InvestorID, 13);
	return res;
}

inline struct WZRspAccountField parseFrom(const struct CThostFtdcTradingAccountField& ori)
{
	struct WZRspAccountField res = {};
	memcpy(res.BrokerID, ori.BrokerID, 11);
	memcpy(res.InvestorID, ori.AccountID, 13);
	res.PreMortgage = ori.PreMortgage;
	res.PreCredit = ori.PreCredit;
	res.PreDeposit = ori.PreDeposit;
	res.preBalance = ori.PreBalance;
	res.PreMargin = ori.PreMargin;
	res.Deposit = ori.Deposit;
	res.Withdraw = ori.Withdraw;
	res.FrozenMargin = ori.FrozenMargin;
	res.FrozenCash = ori.FrozenCash;
	res.FrozenCommission = ori.FrozenCommission;
	res.CurrMargin = ori.CurrMargin;
	res.CashIn = ori.CashIn;
	res.Commission = ori.Commission;
	res.CloseProfit = ori.CloseProfit;
	res.PositionProfit = ori.PositionProfit;
	res.Balance = ori.Balance;
	res.Available = ori.Available;
	res.WithdrawQuota = ori.WithdrawQuota;
	res.Reserve = ori.Reserve;
	memcpy(res.TradingDay, ori.TradingDay, 9);
	res.Credit = ori.Credit;
	res.Mortgage = ori.Mortgage;
	res.ExchangeMargin = ori.ExchangeMargin;
	res.DeliveryMargin = ori.DeliveryMargin;
	res.ExchangeDeliveryMargin = ori.ExchangeDeliveryMargin;
	res.ReserveBalance = ori.ReserveBalance;
	res.Equity = ori.PreBalance - ori.PreCredit - ori.PreMortgage + ori.Mortgage - ori.Withdraw + ori.Deposit + ori.CloseProfit + ori.PositionProfit + ori.CashIn - ori.Commission ;
	return res;
}


*/
#endif
