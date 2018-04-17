#ifndef WZUTILS_LOGGER_H_
#define WZUTILS_LOGGER_H_

#include "logging.h"
#include "wzdatastruct.h"
#include "tsdatastruct.h"
#include "frame.h"
#include "iniparser.h"

class Logger
{
public:
  Logger(char *programname);
  ~Logger();
  void ParseConfigInfo(char *configFilePath);
  void Debug(string);
  void Info(string);
  void Warn(string);
  void Error(string);
  void Fatal(string);
  void Debug(char*);
  void Info(char*);
  void Warn(char*);
  void Error(char*);
  void Fatal(char*);
  void Info(WZMarketDataField md);
  void Info(WZInputOrderField inputOrder);
  void Info(WZOrderActionField orderAction);
  void Info(WZRtnOrderField rtnOrder);
  void Info(WZRtnTradeField rtnTrade);
  void Info(Frame f);
  void Info(TSMarketDataField md);
  void Info(TSInputOrderField inputorder);
  void Info(TSOrderActionField orderaction);
  void Info(TSRtnOrderField rtnOrder);
  void Info(TSRtnTradeField rtnTrade);
};

#endif // WZUTILS_LOGGER_H_
