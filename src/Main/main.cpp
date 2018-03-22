//
//
// Author : huziang
// This is main.cpp file by md server

#define CONTRACT_NUM 1000
#define CONTRACT_LEN 8

#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <thread>
#include "WZUtil/iniparser.h"
#include "CustomMdSpi.h"
#include "WZUtil/TcpPiper.h"
#include "WZUtil/UDPPiper.h"
#include "MessageQueue.h"
using std::thread;


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
MessageQueue *que;


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
  CIni ini;
  ini.OpenFile(filepath, "r");
  strcpy(MdAddr, (ini.GetStr("Addr", "Md")));
  strcpy(InvestorID, ini.GetStr("UsrInfo", "UserID"));
  strcpy(Password, ini.GetStr("UsrInfo", "Password"));
  strcpy(contractsfile, ini.GetStr("CtaInfo", "ContractsFile"));
  contracts = new char*[CONTRACT_NUM];
  for (int i = 0; i < CONTRACT_NUM; i++) {
    contracts[i] = new char[CONTRACT_LEN];
  }
  contractsnum = processInstrumentIDList(contracts, contractsfile);
}

void testInit() {
#ifdef DEBUG
  mytime = new Time();
  mytime->Init();
#else
#endif
}

void writeFile(WZMarketDataField *pDepthMarketData){
  char filePath[100] = {'\0'};
  std::cout << pDepthMarketData->InstrumentID << std::endl;
  sprintf(filePath, "%s_market_data.csv", pDepthMarketData->InstrumentID);
  std::ofstream fout;
  fout.open(filePath, std::ios::app);
  fout << pDepthMarketData->InstrumentID << "," << pDepthMarketData->TradingDay << "," << pDepthMarketData->LastPrice << "," << pDepthMarketData->Volume << std::endl;
  fout.close();
}

void writeThread(){
  for(int index = 0; index < contractsnum; index++){
    char filePath[100] = {'\0'};
    sprintf(filePath, "%s_market_data.csv", contracts[index]);
    std::ofstream fout;
    fout.open(filePath, std::ios::app);
    fout << "code" << "," << "date" << "," << "last price" << "," << "volume" << std::endl;
    fout.close();
  }
  WZMarketDataField *pDepthMarketData = new WZMarketDataField;
  que = new MessageQueue(sizeof(*pDepthMarketData), 600);
  while(1){
    if(que->receive(pDepthMarketData)){
      writeFile(pDepthMarketData);
    }
  }
}

int main(int argc, char* argv[])
{
  // if argv isn't "-f CONFIG_FILE", print help
  if (argc != 3 || strcmp(argv[1], "-f") != 0) {
    printf("Usage : ./mdserver -f CONFIG_FILE\n"
      "\tCONFIG_FILE : initial file path (.ini)\n");
    exit(1);
  }

  // if this file can't read
  if (access(argv[2], R_OK) == -1) {
    perror("Not have a such file or this file is not readable!");
    exit(1);
  }

  readInit(argv[2]);
  thread wtr(writeThread);

  MdEngine *engine = new CustomMdSpi(InvestorID, Password, MdAddr);
  WZPiper *udppiper = new UDPPiper();
  udppiper->set_config_info(argv[2]);
  udppiper->init_as_client();
  //WZPiper *tcppiper = new TcpPiper();

  engine->SetOutput(udppiper);

  cout << "初始化行情..." << endl;
  engine->Init();
  sleep(1);

  // test class init
  // testInit();

  engine->ReqSubscribeMarketData(contracts, contractsnum);
  wtr.join();
  engine->Join();

  engine->Release();

  return 0;
}
