

#include <glog/logging.h>
#include <wzadapter/wzdatastruct.h>
#include "WZUtil/iniparser.h"

class Logger
{
public:
	Logger(char *programname);
	~Logger();
	void ParseConfigInfo(char *configFilePath);
	void Debug(char *buffer);
	void Info(char *buffer);
	void Warn(char *buffer);
	void Error(char *buffer);
	void Fatal(char *buffer);
	void Info(WZMarketDataField md);
	void Info(WZInputOrderField inputOrder);             
	void Info(WZOrderActionField orderAction);
	void Info(WZRtnOrderField rtnOrder);
	void Info(WZRtnTradeField rtnTrade);

};
