#include "ctpwzadapter.h"
#include "wzconstant.h"
#include "wzdatastruct.h"

class MdEngine{

public:
	virtual void reqUserLogin() = 0;
	virtual void reqSubscribeMarketData() = 0;
	virtual void rtnDepthMarketData(WZMarketDataField* pDepthMarketData) = 0;
	//virtual void storeData() = 0;

	void sendMdData(WZMarketDataField pDepthMarketData);

private:
	bool tag = false;
};