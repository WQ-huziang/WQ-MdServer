#ifndef TS2WZPARSER_H_
#define TS2WZPARSER_H_

#include "tsdatastruct.h"
#include "ThostFtdcUserApiStruct.h"

inline void parseFrom(struct  TSRtnOrderField &rtn, const WZRtnOrderField &req){
	memset(&rtn, 0, sizeof(rtn));
	strcpy(rtn.InstrumentID, req.InstrumentID);
	strcpy(rtn.OrderRef, req.OrderRef);
	rtn.LimitPrice = req.LimitPrice;
	rtn.VolumeTraded = req.VolumeTraded;
	rtn.VolumeTotal = req.VolumeTotal;
	rtn.VolumeTotalOriginal = req.VolumeTotalOriginal;
	rtn.Direction = req.Direction;
	rtn.OffsetFlag = req.OffsetFlag;
	rtn.OrderStatus = req.OrderStatus;
}; 

inline void parseFrom(struct TSRtnTradeField &rtn, const WZRtnTradeField &req) {
	memset(&rtn, 0, sizeof(rtn));
	strcpy(rtn.InstrumentID, req.InstrumentID);
	strcpy(rtn.OrderRef, req.OrderRef);
	rtn.Price = req.Price;
	rtn.Volume = req.Volume;
	strcpy(rtn.TradingDay, req.TradingDay);
	strcpy(rtn.TradeTime, req.TradeTime);
	rtn.Direction = req.Direction;
	rtn.OffsetFlag = req.OffsetFlag;
}


#endif