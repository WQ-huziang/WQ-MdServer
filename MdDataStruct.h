/*
 * @Author: w2w 
 * @Date: 2018-02-28 10:57:55 
 * @Last Modified by:   w2w 
 * @Last Modified time: 2018-02-28 10:57:55 
 */

#ifndef BASE_DATA_STRUCT
#define BASE_DATA_STRUCT

#include "adapter/Constant.h"
#include "util/SocketConverter.h"

typedef char char_19[19];
typedef char char_21[21];
typedef char char_64[64];
typedef char char_7[7];
typedef char char_9[9];
typedef char char_30[30];
typedef char char_31[31];
typedef char char_16[16];
typedef char char_13[13];
typedef char char_2[2];
typedef char char_11[11];

struct WZMarketDataField
{
	char_13  	TradingDay;            //½»Ò×ÈÕ
	char_31  	InstrumentID;          //ºÏÔ¼´úÂë
	char_9   	ExchangeID;            //½»Ò×Ëù´úÂë
	char_64  	ExchangeInstID;        //ºÏÔ¼ÔÚ½»Ò×ËùµÄ´úÂë
	double   	LastPrice;             //×îÐÂ¼Û
	double   	PreSettlementPrice;    //ÉÏ´Î½áËã¼Û
	double   	PreClosePrice;         //×òÊÕÅÌ
	double   	PreOpenInterest;       //×ò³Ö²ÖÁ¿
	double   	OpenPrice;             //½ñ¿ªÅÌ
	double   	HighestPrice;          //×î¸ß¼Û
	double   	LowestPrice;           //×îµÍ¼Û
	int      	Volume;                //ÊýÁ¿
	double   	Turnover;              //³É½»½ð¶î
	double   	OpenInterest;          //³Ö²ÖÁ¿
	double   	ClosePrice;            //½ñÊÕÅÌ
	double   	SettlementPrice;       //±¾´Î½áËã¼Û
	double   	UpperLimitPrice;       //ÕÇÍ£°å¼Û
	double   	LowerLimitPrice;       //µøÍ£°å¼Û
	double   	PreDelta;              //×òÐéÊµ¶È
	char_13  	UpdateTime;            //×îºóÐÞ¸ÄÊ±¼ä
	int      	UpdateMillisec;        //×îºóÐÞ¸ÄºÁÃë
	double   	BidPrice1;             //ÉêÂò¼ÛÒ»
	int      	BidVolume1;            //ÉêÂòÁ¿Ò»
	double   	AskPrice1;             //ÉêÂô¼ÛÒ»
	int      	AskVolume1;            //ÉêÂôÁ¿Ò»

	char undefined[300];

	static void toString(char *buf, const WZMarketDataField &ori) {
		char *temp = buf;
		temp = toBuf(temp, (char*)ori.TradingDay);
		temp = toBuf(temp, (char*)ori.InstrumentID);
		temp = toBuf(temp, (char*)ori.ExchangeID);
		temp = toBuf(temp, (char*)ori.ExchangeInstID);
		temp = toBuf(temp, ori.LastPrice);
		temp = toBuf(temp, ori.PreSettlementPrice);
		temp = toBuf(temp, ori.PreClosePrice);
		temp = toBuf(temp, ori.PreOpenInterest);
		temp = toBuf(temp, ori.OpenPrice);
		temp = toBuf(temp, ori.HighestPrice);
		temp = toBuf(temp, ori.LowestPrice);
		temp = toBuf(temp, ori.Volume);
		temp = toBuf(temp, ori.Turnover);
		temp = toBuf(temp, ori.OpenInterest);
		temp = toBuf(temp, ori.ClosePrice);
		temp = toBuf(temp, ori.SettlementPrice);
		temp = toBuf(temp, ori.UpperLimitPrice);
		temp = toBuf(temp, ori.LowerLimitPrice);
		temp = toBuf(temp, ori.PreDelta);
		temp = toBuf(temp, (char*)ori.UpdateTime);
		temp = toBuf(temp, ori.UpdateMillisec);
		temp = toBuf(temp, ori.BidPrice1);
		temp = toBuf(temp, ori.BidVolume1);
		temp = toBuf(temp, ori.AskPrice1);
		temp = toBuf(temp, ori.AskVolume1);
	}

	static void fromString(WZMarketDataField &ori, char *buf) {
		char *temp = buf;
		temp = fromBuf(temp, (char*)ori.TradingDay);
		temp = fromBuf(temp, (char*)ori.InstrumentID);
		temp = fromBuf(temp, (char*)ori.ExchangeID);
		temp = fromBuf(temp, (char*)ori.ExchangeInstID);
		temp = fromBuf(temp, ori.LastPrice);
		temp = fromBuf(temp, ori.PreSettlementPrice);
		temp = fromBuf(temp, ori.PreClosePrice);
		temp = fromBuf(temp, ori.PreOpenInterest);
		temp = fromBuf(temp, ori.OpenPrice);
		temp = fromBuf(temp, ori.HighestPrice);
		temp = fromBuf(temp, ori.LowestPrice);
		temp = fromBuf(temp, ori.Volume);
		temp = fromBuf(temp, ori.Turnover);
		temp = fromBuf(temp, ori.OpenInterest);
		temp = fromBuf(temp, ori.ClosePrice);
		temp = fromBuf(temp, ori.SettlementPrice);
		temp = fromBuf(temp, ori.UpperLimitPrice);
		temp = fromBuf(temp, ori.LowerLimitPrice);
		temp = fromBuf(temp, ori.PreDelta);
		temp = fromBuf(temp, (char*)ori.UpdateTime);
		temp = fromBuf(temp, ori.UpdateMillisec);
		temp = fromBuf(temp, ori.BidPrice1);
		temp = fromBuf(temp, ori.BidVolume1);
		temp = fromBuf(temp, ori.AskPrice1);
		temp = fromBuf(temp, ori.AskVolume1);
	}
};

struct WZL2OrderField
{
	char_9   	OrderTime;             //Î¯ÍÐÊ±¼ä£¨Ãë£©
	char_9   	ExchangeID;            //½»Ò×Ëù´úÂë
	char_31  	InstrumentID;          //ºÏÔ¼´úÂë
	double   	Price;                 //Î¯ÍÐ¼Û¸ñ
	double   	Volume;                //Î¯ÍÐÊýÁ¿
	char_2   	OrderKind;             //±¨µ¥ÀàÐÍ

	char undefined[300];

	static void toString(char *buf, const WZL2OrderField &ori) {
		char *temp = buf;
		temp = toBuf(temp, (char*)ori.OrderTime);
		temp = toBuf(temp, (char*)ori.ExchangeID);
		temp = toBuf(temp, (char*)ori.InstrumentID);
		temp = toBuf(temp, ori.Price);
		temp = toBuf(temp, ori.Volume);
		temp = toBuf(temp, (char*)ori.OrderKind);
	}

	static void fromString(WZL2OrderField &ori, char *buf) {
		char *temp = buf;
		temp = fromBuf(temp, (char*)ori.OrderTime);
		temp = fromBuf(temp, (char*)ori.ExchangeID);
		temp = fromBuf(temp, (char*)ori.InstrumentID);
		temp = fromBuf(temp, ori.Price);
		temp = fromBuf(temp, ori.Volume);
		temp = fromBuf(temp, (char*)ori.OrderKind);
	}
};



// struct WZL2MarketDataField
// {
// 	char_9   	TradingDay;            //½»Ò×ÈÕ
// 	char_9   	TimeStamp;             //Ê±¼ä´Á
// 	char_9   	ExchangeID;            //½»Ò×Ëù´úÂë
// 	char_31  	InstrumentID;          //ºÏÔ¼´úÂë
// 	double   	PreClosePrice;         //×òÊÕÅÌ¼Û
// 	double   	OpenPrice;             //½ñ¿ªÅÌ¼Û
// 	double   	ClosePrice;            //ÊÕÅÌ¼Û
// 	double   	IOPV;                  //¾»Öµ¹ÀÖµ
// 	double   	YieldToMaturity;       //µ½ÆÚÊÕÒæÂÊ
// 	double   	AuctionPrice;          //¶¯Ì¬²Î¿¼¼Û¸ñ
// 	char     	TradingPhase;          //½»Ò×½×¶Î
// 	char     	OpenRestriction;       //¿ª²ÖÏÞÖÆ
// 	double   	HighPrice;             //×î¸ß¼Û
// 	double   	LowPrice;              //×îµÍ¼Û
// 	double   	LastPrice;             //×îÐÂ¼Û
// 	double   	TradeCount;            //³É½»±ÊÊý
// 	double   	TotalTradeVolume;      //³É½»×ÜÁ¿
// 	double   	TotalTradeValue;       //³É½»×Ü½ð¶î
// 	double   	OpenInterest;          //³Ö²ÖÁ¿
// 	double   	TotalBidVolume;        //Î¯ÍÐÂòÈë×ÜÁ¿
// 	double   	WeightedAvgBidPrice;   //¼ÓÈ¨Æ½¾ùÎ¯Âò¼Û
// 	double   	AltWeightedAvgBidPrice;   //Õ®È¯¼ÓÈ¨Æ½¾ùÎ¯Âò¼Û
// 	double   	TotalOfferVolume;      //Î¯ÍÐÂô³ö×ÜÁ¿
// 	double   	WeightedAvgOfferPrice;   //¼ÓÈ¨Æ½¾ùÎ¯Âô¼Û
// 	double   	AltWeightedAvgOfferPrice;   //Õ®È¯¼ÓÈ¨Æ½¾ùÎ¯Âô¼Û¸ñ
// 	int      	BidPriceLevel;         //Âò¼ÛÉî¶È
// 	int      	OfferPriceLevel;       //Âô¼ÛÉî¶È
// 	double   	BidPrice1;             //ÉêÂò¼ÛÒ»
// 	double   	BidVolume1;            //ÉêÂòÁ¿Ò»
// 	int      	BidCount1;             //Êµ¼ÊÂò×ÜÎ¯ÍÐ±ÊÊýÒ»
// 	double   	BidPrice2;             //ÉêÂò¼Û¶þ
// 	double   	BidVolume2;            //ÉêÂòÁ¿¶þ
// 	int      	BidCount2;             //Êµ¼ÊÂò×ÜÎ¯ÍÐ±ÊÊý¶þ
// 	double   	BidPrice3;             //ÉêÂò¼ÛÈý
// 	double   	BidVolume3;            //ÉêÂòÁ¿Èý
// 	int      	BidCount3;             //Êµ¼ÊÂò×ÜÎ¯ÍÐ±ÊÊýÈý
// 	double   	BidPrice4;             //ÉêÂò¼ÛËÄ
// 	double   	BidVolume4;            //ÉêÂòÁ¿ËÄ
// 	int      	BidCount4;             //Êµ¼ÊÂò×ÜÎ¯ÍÐ±ÊÊýËÄ
// 	double   	BidPrice5;             //ÉêÂò¼ÛÎå
// 	double   	BidVolume5;            //ÉêÂòÁ¿Îå
// 	int      	BidCount5;             //Êµ¼ÊÂò×ÜÎ¯ÍÐ±ÊÊýÎå
// 	double   	BidPrice6;             //ÉêÂò¼ÛÁù
// 	double   	BidVolume6;            //ÉêÂòÁ¿Áù
// 	int      	BidCount6;             //Êµ¼ÊÂò×ÜÎ¯ÍÐ±ÊÊýÁù
// 	double   	BidPrice7;             //ÉêÂò¼ÛÆß
// 	double   	BidVolume7;            //ÉêÂòÁ¿Æß
// 	int      	BidCount7;             //Êµ¼ÊÂò×ÜÎ¯ÍÐ±ÊÊýÆß
// 	double   	BidPrice8;             //ÉêÂò¼Û°Ë
// 	double   	BidVolume8;            //ÉêÂòÁ¿°Ë
// 	int      	BidCount8;             //Êµ¼ÊÂò×ÜÎ¯ÍÐ±ÊÊý°Ë
// 	double   	BidPrice9;             //ÉêÂò¼Û¾Å
// 	double   	BidVolume9;            //ÉêÂòÁ¿¾Å
// 	int      	BidCount9;             //Êµ¼ÊÂò×ÜÎ¯ÍÐ±ÊÊý¾Å
// 	double   	BidPriceA;             //ÉêÂò¼ÛÊ®
// 	double   	BidVolumeA;            //ÉêÂòÁ¿Ê®
// 	int      	BidCountA;             //Êµ¼ÊÂò×ÜÎ¯ÍÐ±ÊÊýÊ®
// 	double   	OfferPrice1;           //ÉêÂô¼ÛÒ»
// 	double   	OfferVolume1;          //ÉêÂôÁ¿Ò»
// 	int      	OfferCount1;           //Êµ¼ÊÂô×ÜÎ¯ÍÐ±ÊÊýÒ»
// 	double   	OfferPrice2;           //ÉêÂô¼Û¶þ
// 	double   	OfferVolume2;          //ÉêÂôÁ¿¶þ
// 	int      	OfferCount2;           //Êµ¼ÊÂô×ÜÎ¯ÍÐ±ÊÊý¶þ
// 	double   	OfferPrice3;           //ÉêÂô¼ÛÈý
// 	double   	OfferVolume3;          //ÉêÂôÁ¿Èý
// 	int      	OfferCount3;           //Êµ¼ÊÂô×ÜÎ¯ÍÐ±ÊÊýÈý
// 	double   	OfferPrice4;           //ÉêÂô¼ÛËÄ
// 	double   	OfferVolume4;          //ÉêÂôÁ¿ËÄ
// 	int      	OfferCount4;           //Êµ¼ÊÂô×ÜÎ¯ÍÐ±ÊÊýËÄ
// 	double   	OfferPrice5;           //ÉêÂô¼ÛÎå
// 	double   	OfferVolume5;          //ÉêÂôÁ¿Îå
// 	int      	OfferCount5;           //Êµ¼ÊÂô×ÜÎ¯ÍÐ±ÊÊýÎå
// 	double   	OfferPrice6;           //ÉêÂô¼ÛÁù
// 	double   	OfferVolume6;          //ÉêÂôÁ¿Áù
// 	int      	OfferCount6;           //Êµ¼ÊÂô×ÜÎ¯ÍÐ±ÊÊýÁù
// 	double   	OfferPrice7;           //ÉêÂô¼ÛÆß
// 	double   	OfferVolume7;          //ÉêÂôÁ¿Æß
// 	int      	OfferCount7;           //Êµ¼ÊÂô×ÜÎ¯ÍÐ±ÊÊýÆß
// 	double   	OfferPrice8;           //ÉêÂô¼Û°Ë
// 	double   	OfferVolume8;          //ÉêÂôÁ¿°Ë
// 	int      	OfferCount8;           //Êµ¼ÊÂô×ÜÎ¯ÍÐ±ÊÊý°Ë
// 	double   	OfferPrice9;           //ÉêÂô¼Û¾Å
// 	double   	OfferVolume9;          //ÉêÂôÁ¿¾Å
// 	int      	OfferCount9;           //Êµ¼ÊÂô×ÜÎ¯ÍÐ±ÊÊý¾Å
// 	double   	OfferPriceA;           //ÉêÂô¼ÛÊ®
// 	double   	OfferVolumeA;          //ÉêÂôÁ¿Ê®
// 	int      	OfferCountA;           //Êµ¼ÊÂô×ÜÎ¯ÍÐ±ÊÊýÊ®
// 	char_7   	InstrumentStatus;      //ºÏÔ¼×´Ì¬
// 	double   	PreIOPV;               //×ò¾»Öµ¹ÀÖµ
// 	double   	PERatio1;              //ÊÐÓ¯ÂÊÒ»
// 	double   	PERatio2;              //ÊÐÓ¯ÂÊ¶þ
// 	double   	UpperLimitPrice;       //ÕÇÍ£¼Û
// 	double   	LowerLimitPrice;       //µøÍ£¼Û
// 	double   	WarrantPremiumRatio;   //È¨Ö¤Òç¼ÛÂÊ
// 	double   	TotalWarrantExecQty;   //È¨Ö¤Ö´ÐÐ×ÜÊýÁ¿
// 	double   	PriceDiff1;            //ÉýµøÒ»
// 	double   	PriceDiff2;            //Éýµø¶þ
// 	double   	ETFBuyNumber;          //ETFÉê¹º±ÊÊý
// 	double   	ETFBuyAmount;          //ETFÉê¹ºÊýÁ¿
// 	double   	ETFBuyMoney;           //ETFÉê¹º½ð¶î
// 	double   	ETFSellNumber;         //ETFÊê»Ø±ÊÊý
// 	double   	ETFSellAmount;         //ETFÊê»ØÊýÁ¿
// 	double   	ETFSellMoney;          //ETFÊê»Ø½ð¶î
// 	double   	WithdrawBuyNumber;     //ÂòÈë³·µ¥±ÊÊý
// 	double   	WithdrawBuyAmount;     //ÂòÈë³·µ¥ÊýÁ¿
// 	double   	WithdrawBuyMoney;      //ÂòÈë³·µ¥½ð¶î
// 	double   	TotalBidNumber;        //ÂòÈë×Ü±ÊÊý
// 	double   	BidTradeMaxDuration;   //ÂòÈëÎ¯ÍÐ³É½»×î´óµÈ´ýÊ±¼ä
// 	double   	NumBidOrders;          //Âò·½Î¯ÍÐ¼ÛÎ»Êý
// 	double   	WithdrawSellNumber;    //Âô³ö³·µ¥±ÊÊý
// 	double   	WithdrawSellAmount;    //Âô³ö³·µ¥ÊýÁ¿
// 	double   	WithdrawSellMoney;     //Âô³ö³·µ¥½ð¶î
// 	double   	TotalOfferNumber;      //Âô³ö×Ü±ÊÊý
// 	double   	OfferTradeMaxDuration;   //Âô³öÎ¯ÍÐ³É½»×î´óµÈ´ýÊ±¼ä
// 	double   	NumOfferOrders;        //Âô·½Î¯ÍÐ¼ÛÎ»Êý
// };

// struct WZL2IndexField
// {
// 	char_9   	TradingDay;            //½»Ò×ÈÕ
// 	char_9   	TimeStamp;             //ÐÐÇéÊ±¼ä£¨Ãë£©
// 	char_9   	ExchangeID;            //½»Ò×Ëù´úÂë
// 	char_31  	InstrumentID;          //Ö¸Êý´úÂë
// 	double   	PreCloseIndex;         //Ç°ÊÕÅÌÖ¸Êý
// 	double   	OpenIndex;             //½ñ¿ªÅÌÖ¸Êý
// 	double   	CloseIndex;            //½ñÈÕÊÕÅÌÖ¸Êý
// 	double   	HighIndex;             //×î¸ßÖ¸Êý
// 	double   	LowIndex;              //×îµÍÖ¸Êý
// 	double   	LastIndex;             //×îÐÂÖ¸Êý
// 	double   	TurnOver;              //²ÎÓë¼ÆËãÏàÓ¦Ö¸ÊýµÄ³É½»½ð¶î£¨Ôª£©
// 	double   	TotalVolume;           //²ÎÓë¼ÆËãÏàÓ¦Ö¸ÊýµÄ½»Ò×ÊýÁ¿£¨ÊÖ£©
// };



// struct WZL2TradeField
// {
// 	char_9   	TradeTime;             //³É½»Ê±¼ä£¨Ãë£©
// 	char_9   	ExchangeID;            //½»Ò×Ëù´úÂë
// 	char_31  	InstrumentID;          //ºÏÔ¼´úÂë
// 	double   	Price;                 //³É½»¼Û¸ñ
// 	double   	Volume;                //³É½»ÊýÁ¿
// 	char_2   	OrderKind;             //±¨µ¥ÀàÐÍ
// 	char_2   	OrderBSFlag;           //ÄÚÍâÅÌ±êÖ¾
// };

// struct WZBarMarketDataField
// {
// 	char_9   	TradingDay;            //½»Ò×ÈÕ
// 	char_31  	InstrumentID;          //ºÏÔ¼´úÂë
// 	double   	UpperLimitPrice;       //ÕÇÍ£°å¼Û
// 	double   	LowerLimitPrice;       //µøÍ£°å¼Û
// 	char_13  	StartUpdateTime;       //Ê×tickÐÞ¸ÄÊ±¼ä
// 	int      	StartUpdateMillisec;   //Ê×tick×îºóÐÞ¸ÄºÁÃë
// 	char_13  	EndUpdateTime;         //Î²tick×îºóÐÞ¸ÄÊ±¼ä
// 	int      	EndUpdateMillisec;     //Î²tick×îºóÐÞ¸ÄºÁÃë
// 	double   	Open;                  //¿ª
// 	double   	Close;                 //ÊÕ
// 	double   	Low;                   //µÍ
// 	double   	High;                  //¸ß
// 	double   	Volume;                //Çø¼ä½»Ò×Á¿
// 	double   	StartVolume;           //³õÊ¼×Ü½»Ò×Á¿
// };

// struct WZQryPositionField
// {
// 	char_11  	BrokerID;              //¾­¼Í¹«Ë¾´úÂë
// 	char_19  	InvestorID;            //Í¶×ÊÕß´úÂë
// 	char_31  	InstrumentID;          //ºÏÔ¼´úÂë
// 	char_9   	ExchangeID;            //½»Ò×Ëù´úÂë
// };

// struct WZRspPositionField
// {
// 	char_31              	InstrumentID;          //ºÏÔ¼´úÂë
// 	int                  	YdPosition;            //ÉÏÈÕ³Ö²Ö
// 	int                  	Position;              //×Ü³Ö²Ö
// 	char_11              	BrokerID;              //¾­¼Í¹«Ë¾´úÂë
// 	char_19              	InvestorID;            //Í¶×ÊÕß´úÂë
// 	double               	PositionCost;          //³Ö²Ö³É±¾
// 	WZHedgeFlagType      	HedgeFlag;             //Í¶»úÌ×±£±êÖ¾
// 	WZPosiDirectionType  	PosiDirection;         //³Ö²Ö¶à¿Õ·½Ïò
// };

// struct WZInputOrderField
// {
// 	char_11                    	BrokerID;              //¾­¼Í¹«Ë¾´úÂë
// 	char_16                    	UserID;                //ÓÃ»§´úÂë
// 	char_19                    	InvestorID;            //Í¶×ÊÕß´úÂë
// 	char_21                    	BusinessUnit;          //ÒµÎñµ¥Ôª
// 	char_9                     	ExchangeID;            //½»Ò×Ëù´úÂë
// 	char_31                    	InstrumentID;          //ºÏÔ¼´úÂë
// 	char_21                    	OrderRef;              //±¨µ¥ÒýÓÃ
// 	double                     	LimitPrice;            //¼Û¸ñ
// 	int                        	Volume;                //ÊýÁ¿
// 	int                        	MinVolume;             //×îÐ¡³É½»Á¿
// 	WZTimeConditionType        	TimeCondition;         //ÓÐÐ§ÆÚÀàÐÍ
// 	WZVolumeConditionType      	VolumeCondition;       //³É½»Á¿ÀàÐÍ
// 	WZOrderPriceTypeType       	OrderPriceType;        //±¨µ¥¼Û¸ñÌõ¼þ
// 	WZDirectionType            	Direction;             //ÂòÂô·½Ïò
// 	WZOffsetFlagType           	OffsetFlag;            //¿ªÆ½±êÖ¾
// 	WZHedgeFlagType            	HedgeFlag;             //Í¶»úÌ×±£±êÖ¾
// 	WZForceCloseReasonType     	ForceCloseReason;      //Ç¿Æ½Ô­Òò
// 	double                     	StopPrice;             //Ö¹Ëð¼Û
// 	int                        	IsAutoSuspend;         //×Ô¶¯¹ÒÆð±êÖ¾
// 	WZContingentConditionType  	ContingentCondition;   //´¥·¢Ìõ¼þ
// 	char_30                    	MiscInfo;              //Î¯ÍÐ×Ô¶¨Òå±êÇ©
// };

// struct WZRtnOrderField
// {
// 	char_11                	BrokerID;              //¾­¼Í¹«Ë¾´úÂë
// 	char_16                	UserID;                //ÓÃ»§´úÂë
// 	char_11                	ParticipantID;         //»áÔ±´úÂë
// 	char_19                	InvestorID;            //Í¶×ÊÕß´úÂë
// 	char_21                	BusinessUnit;          //ÒµÎñµ¥Ôª
// 	char_31                	InstrumentID;          //ºÏÔ¼´úÂë
// 	char_21                	OrderRef;              //±¨µ¥ÒýÓÃ
// 	char_11                	ExchangeID;            //½»Ò×Ëù´úÂë
// 	double                 	LimitPrice;            //¼Û¸ñ
// 	int                    	VolumeTraded;          //½ñ³É½»ÊýÁ¿
// 	int                    	VolumeTotal;           //Ê£ÓàÊýÁ¿
// 	int                    	VolumeTotalOriginal;   //ÊýÁ¿
// 	WZTimeConditionType    	TimeCondition;         //ÓÐÐ§ÆÚÀàÐÍ
// 	WZVolumeConditionType  	VolumeCondition;       //³É½»Á¿ÀàÐÍ
// 	WZOrderPriceTypeType   	OrderPriceType;        //±¨µ¥¼Û¸ñÌõ¼þ
// 	WZDirectionType        	Direction;             //ÂòÂô·½Ïò
// 	WZOffsetFlagType       	OffsetFlag;            //¿ªÆ½±êÖ¾
// 	WZHedgeFlagType        	HedgeFlag;             //Í¶»úÌ×±£±êÖ¾
// 	WZOrderStatusType      	OrderStatus;           //±¨µ¥×´Ì¬
// 	int                    	RequestID;             //ÇëÇó±àºÅ
// };

// struct WZRtnTradeField
// {
// 	char_11           	BrokerID;              //¾­¼Í¹«Ë¾´úÂë
// 	char_16           	UserID;                //ÓÃ»§´úÂë
// 	char_19           	InvestorID;            //Í¶×ÊÕß´úÂë
// 	char_21           	BusinessUnit;          //ÒµÎñµ¥Ôª
// 	char_31           	InstrumentID;          //ºÏÔ¼´úÂë
// 	char_21           	OrderRef;              //±¨µ¥ÒýÓÃ
// 	char_11           	ExchangeID;            //½»Ò×Ëù´úÂë
// 	char_21           	TradeID;               //³É½»±àºÅ
// 	char_31           	OrderSysID;            //±¨µ¥±àºÅ
// 	char_11           	ParticipantID;         //»áÔ±´úÂë
// 	char_21           	ClientID;              //¿Í»§´úÂë
// 	double            	Price;                 //¼Û¸ñ
// 	int               	Volume;                //ÊýÁ¿
// 	char_13           	TradingDay;            //½»Ò×ÈÕ
// 	char_13           	TradeTime;             //³É½»Ê±¼ä
// 	WZDirectionType   	Direction;             //ÂòÂô·½Ïò
// 	WZOffsetFlagType  	OffsetFlag;            //¿ªÆ½±êÖ¾
// 	WZHedgeFlagType   	HedgeFlag;             //Í¶»úÌ×±£±êÖ¾
// };

// struct WZOrderActionField
// {
// 	char_11  	BrokerID;              //¾­¼Í¹«Ë¾´úÂë
// 	char_19  	InvestorID;            //Í¶×ÊÕß´úÂë
// 	char_31  	InstrumentID;          //ºÏÔ¼´úÂë
// 	char_11  	ExchangeID;            //½»Ò×Ëù´úÂë
// 	char_16  	UserID;                //ÓÃ»§´úÂë
// 	char_21  	OrderRef;              //±¨µ¥ÒýÓÃ
// 	char_31  	OrderSysID;            //±¨µ¥±àºÅ
// 	int      	RequestID;             //ÇëÇó±àºÅ
// 	char     	ActionFlag;            //±¨µ¥²Ù×÷±êÖ¾
// 	double   	LimitPrice;            //¼Û¸ñ
// 	int      	VolumeChange;          //ÊýÁ¿±ä»¯
// 	int      	KfOrderID;             //KfÏµÍ³ÄÚ¶©µ¥ID
// };

// struct WZQryAccountField
// {
// 	char_11  	BrokerID;              //¾­¼Í¹«Ë¾´úÂë
// 	char_19  	InvestorID;            //Í¶×ÊÕß´úÂë
// };

// struct WZRspAccountField
// {
// 	char_11  	BrokerID;              //¾­¼Í¹«Ë¾´úÂë
// 	char_19  	InvestorID;            //Í¶×ÊÕß´úÂë
// 	double   	PreMortgage;           //ÉÏ´ÎÖÊÑº½ð¶î
// 	double   	PreCredit;             //ÉÏ´ÎÐÅÓÃ¶î¶È
// 	double   	PreDeposit;            //ÉÏ´Î´æ¿î¶î
// 	double   	preBalance;            //ÉÏ´Î½áËã×¼±¸½ð
// 	double   	PreMargin;             //ÉÏ´ÎÕ¼ÓÃµÄ±£Ö¤½ð
// 	double   	Deposit;               //Èë½ð½ð¶î
// 	double   	Withdraw;              //³ö½ð½ð¶î
// 	double   	FrozenMargin;          //¶³½áµÄ±£Ö¤½ð£¨±¨µ¥Î´³É½»¶³½áµÄ±£Ö¤½ð£©
// 	double   	FrozenCash;            //¶³½áµÄ×Ê½ð£¨±¨µ¥Î´³É½»¶³½áµÄ×Ü×Ê½ð£©
// 	double   	FrozenCommission;      //¶³½áµÄÊÖÐø·Ñ£¨±¨µ¥Î´³É½»¶³½áµÄÊÖÐø·Ñ£©
// 	double   	CurrMargin;            //µ±Ç°±£Ö¤½ð×Ü¶î
// 	double   	CashIn;                //×Ê½ð²î¶î
// 	double   	Commission;            //ÊÖÐø·Ñ
// 	double   	CloseProfit;           //Æ½²ÖÓ¯¿÷
// 	double   	PositionProfit;        //³Ö²ÖÓ¯¿÷
// 	double   	Balance;               //½áËã×¼±¸½ð
// 	double   	Available;             //¿ÉÓÃ×Ê½ð
// 	double   	WithdrawQuota;         //¿ÉÈ¡×Ê½ð
// 	double   	Reserve;               //»ù±¾×¼±¸½ð
// 	char_9   	TradingDay;            //½»Ò×ÈÕ
// 	double   	Credit;                //ÐÅÓÃ¶î¶È
// 	double   	Mortgage;              //ÖÊÑº½ð¶î
// 	double   	ExchangeMargin;        //½»Ò×Ëù±£Ö¤½ð
// 	double   	DeliveryMargin;        //Í¶×ÊÕß½»¸î±£Ö¤½ð
// 	double   	ExchangeDeliveryMargin;   //½»Ò×Ëù½»¸î±£Ö¤½ð
// 	double   	ReserveBalance;        //±£µ×ÆÚ»õ½áËã×¼±¸½ð
// 	double   	Equity;                //µ±ÈÕÈ¨Òæ
// 	double   	MarketValue;           //ÕË»§ÊÐÖµ
// };

#endif
