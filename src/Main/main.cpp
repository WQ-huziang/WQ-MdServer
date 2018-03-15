//
//
// Author : huziang
// This is main.cpp file by md server

#define CONTRACT_NUM 100
#define CONTRACT_LEN 8

#include <unistd.h>
#include <iostream>
#include <cstring>
#include "IniConfig.h"
#include "CustomMdSpi.h"
#include "OutputAdapter/UdpOutputAdapter.h"
#include "OutputAdapter/TcpOutputAdapter.h"

int requestID;
int contractsnum;
char **contracts;
TThostFtdcInvestorIDType InvestorID;
TThostFtdcPasswordType Password;
char MdAddr[30];

int processInstrumentIDList(char *list[], const char pInstrumentIDList[]) {
  if (pInstrumentIDList[0] == '\0') {
    return 0;
  }

  // split string
  int sum = 0;
  char str[strlen(pInstrumentIDList) + 1];
  strcpy(str, pInstrumentIDList);
  char *begin = str;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ') {
      str[i] = '\0';
      strcpy(list[sum++], begin);
      begin = str + i + 1;
    }
  }

  // get last string
  strcpy(list[sum++], begin);
  return sum;
}

void readIni(){
  IniConfig* ini = new IniConfig("../config.ini");
  ini->readIni();
  strcpy(MdAddr, (ini->getObject("Addr", "Md", "false").c_str()));
  strcpy(InvestorID, (ini->getObject("UsrInfo", "UserID", "false").c_str()));
  strcpy(Password, (ini->getObject("UsrInfo", "Password", "false").c_str()));
  contracts = new char*[CONTRACT_NUM];
  for (int i = 0; i < CONTRACT_NUM; i++) {
    contracts[i] = new char[CONTRACT_LEN];
  }
  contractsnum = processInstrumentIDList(contracts, (ini->getObject("CtaInfo", "Contracts", "").c_str()));
  for (int i = 0; i < contractsnum; i++) {
    printf("%s\n", contracts[i]);
  }
}

int main(int argn, char* argv[])
{
  readIni();

  MdEngine *engine = new CustomMdSpi(InvestorID, Password, MdAddr);
  OutputAdapter *udpadapter = new UdpOutputAdapter(12345, "127.0.0.1");
  OutputAdapter *tcpadapter = new TcpOutputAdapter(12345, "127.0.0.1");
  engine->setOutput(tcpadapter);
  cout << "初始化行情..." << endl;

  while (true) {
    sleep(100);
  }

  return 0;
}
