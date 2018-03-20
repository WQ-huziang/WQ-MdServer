//
//
// Author : huziang
// This is main.cpp file by md server

#define CONTRACT_NUM 1000
#define CONTRACT_LEN 8

#include <unistd.h>
#include <iostream>
#include <cstring>
#include "IniConfig.h"
#include "CustomMdSpi.h"
#include "OutputAdapter/UdpOutputAdapter.h"
#include "OutputAdapter/TcpOutputAdapter.h"

#ifdef DEBUG
#include "test.h"
Time *mytime;
#endif

int requestID;
int contractsnum;
char **contracts;
TThostFtdcInvestorIDType InvestorID;
TThostFtdcPasswordType Password;
char contractsfile[50];
char MdAddr[50];
int port;

// int splitList(char *list[], const char strs[], const char deli = '\n') {
//   if (strs[0] == '\0') {
//     return 0;
//   }

//   // split string
//   int sum = 0;
//   char str[strlen(strs) + 1];
//   strcpy(str, strs);
//   char *begin = str;
//   for (int i = 0; str[i] != '\0'; i++) {
//     if (str[i] == deli) {
//       str[i] = '\0';
//       strcpy(list[sum++], begin);
//       begin = str + i + 1;
//     }
//   }

//   // get last string
//   strcpy(list[sum++], begin);
//   return sum;
// }

int processInstrumentIDList(char *list[], const char *filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "No such file %s\n", filename);
  }

  int num = 0;
  while (fscanf(fp, "%s", list[num++]) != -1);
  fclose(fp);
  return num - 1;
}

void readInit(char *filepath){
  IniConfig* ini = new IniConfig(filepath);
  ini->readIni();
  strcpy(MdAddr, (ini->getObject("Addr", "Md", "false").c_str()));
  port = atoi((ini->getObject("Addr", "Port", "12345").c_str()));
  strcpy(InvestorID, (ini->getObject("UsrInfo", "UserID", "false").c_str()));
  strcpy(Password, (ini->getObject("UsrInfo", "Password", "false").c_str()));
  strcpy(contractsfile, (ini->getObject("CtaInfo", "ContractsFile", "").c_str()));
  contracts = new char*[CONTRACT_NUM];
  for (int i = 0; i < CONTRACT_NUM; i++) {
    contracts[i] = new char[CONTRACT_LEN];
  }
  contractsnum = processInstrumentIDList(contracts, contractsfile);
}

void testInit() {
#ifdef DEBUG
  mytime = new Time();
  mytime->SetMap(contracts, contractsnum);
#else
#endif
}

int main(int argc, char* argv[])
{
  if (argc != 3 || strcmp(argv[1], "-f") != 0) {
    printf("Usage : ./mdserver -f CONFIG_FILE\n"
      "\tCONFIG_FILE : initial file path (.ini)\n");
    return 0;
  }

  readInit(argv[2]);

  MdEngine *engine = new CustomMdSpi(InvestorID, Password, MdAddr);
  OutputAdapter *udpadapter = new UdpOutputAdapter(port, "127.0.0.1");
  OutputAdapter *tcpadapter = new TcpOutputAdapter(port, "127.0.0.1");
  udpadapter->init();
  engine->SetOutput(udpadapter);

  cout << "初始化行情..." << endl;
  engine->Init();
  sleep(1);

  // test class init
  testInit();

  engine->ReqSubscribeMarketData(contracts, contractsnum);
  engine->Release();

  return 0;
}
