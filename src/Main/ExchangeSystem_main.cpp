#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include "CustomMdSpi.h"
#include "CustomTradeSpi.h"
#include "IniConfig.h"
#include "ctpwzadapter.h"
#include "wzconstant.h"
#include "wzdatastruct.h"
#include "OutputAdapter.h"
#include <iostream>
#include <cstring>
using namespace std;

//#pragma comment(lib, "thostmduserapi.lib")
//#pragma comment(lib, "thosttraderapi.lib")

int requestID;
CThostFtdcTraderApi *pTradeUserApi = NULL;
CThostFtdcMdApi *pUserApi = NULL;
char TradeAddr[] = "tcp://180.168.146.187:10001";
char MdAddr[] = "tcp://180.168.146.187:10011";
int ContractsNum = 1;
char *Contracts[100];
TThostFtdcPriceType gLimitPrice;
char_19 InvestorID;
char Password[41];
OutputAdapter* opa;
char Filepath[] = {"test.txt"};
char UdpAddr[] = {"127.0.0.1"};
char TcpAddr[] = {"127.0.0.1"};

void readIni(){
	IniConfig* ini = new IniConfig("config.ini");
	ini->readIni();
	strcpy(TradeAddr, (ini->getObject("Addr", "Td", "false").c_str()));
	strcpy(MdAddr, (ini->getObject("Addr", "Md", "false").c_str()));
	strcpy(InvestorID, (ini->getObject("UsrInfo", "UserID", "false").c_str()));
	strcpy(Password, (ini->getObject("UsrInfo", "Password", "false").c_str()));
}

int main(int argn, char* argv[])
{
	
	readIni();
	Contracts[0] = argv[1];
	cout << "用户id：" << InvestorID << endl;

	opa = new OutputAdapter;
	opa->setUdpHtons(8888);

	cout << "初始化行情..." << endl;
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
	CustomMdSpi *pMd = new CustomMdSpi(Password, InvestorID);
	pUserApi->RegisterSpi(pMd);
	pUserApi->RegisterFront(MdAddr);
	pUserApi->Init();

	pUserApi->Join();
	delete pMd;
	pUserApi->Release();
	
    return 0;
}
