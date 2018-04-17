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
#include <stdio.h>
#include "iniparser.h"
#include "CustomMdSpi.h"
#include "wzsocket_inc/udp.h"
#include "MessageQueue.h"
#include "logger.h"
#include "tsdatastruct.h"
#include "mongodbengine.h"
#include "dataparse.h"
using std::thread;

#ifdef DEBUG
#include "test.h"
Time *mytime;
static long num = 0;
#endif

int requestID;
int contractsnum;
char **contracts;
TThostFtdcInvestorIDType InvestorID;
TThostFtdcPasswordType Password;
char contractsfile[50];
char MdAddr[50];
MessageQueue *que;
Logger *logger;

WZPiper<UdpSocket> *udppiper;

DataEngine *db;
vector<map<string, string>> mds;
map<string, string> md;

int processInstrumentIDList(char *list[], const char *filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    char info[50];
    sprintf(info, "No such file %s", filename);
    logger->Error(info);
    return 0;
  }

  int num = 0;
  while (fscanf(fp, "%s", list[num++]) != -1);
  fclose(fp);
  return num - 1;
}

void readInit(char *progname, char *filepath){
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

  // logger init
  logger = new Logger(progname);
  logger->ParseConfigInfo(filepath);

  // data engine init
  db = MongodbEngine::getInstance();
  db->init();
  db->setLibname("Md");
  db->setTablename("TSMarketDataField");

  udppiper = new WZPiper<UdpSocket>();
  udppiper->init(filepath, WZ_PIPER_CLIENT, WZ_PIPER_BLOCK);
}

void testInit() {
#ifdef DEBUG
  mytime = new Time();
  mytime->Init();
#endif
}

void writeDataEngine(TSMarketDataField *pDepthMarketData) {
  // to document
  md.clear();
  parseFrom(md, *pDepthMarketData);
#ifdef DEBUG
  cerr << "===== Data Engine =====" << endl;
  cerr << num++ << endl;
#endif

  // documents insert the document
  mds.push_back(md);
  if (mds.size() >= 50) {
    if (db->insert_many(mds)) {
      LOG(INFO) << "insert TSMarketDataFields success!";
    } else {
      LOG(ERROR) << "Can't insert TSMarketDataFields!";
    }
    mds.clear();
  }
}

void writeThread() {
  TSMarketDataField *pDepthMarketData = new TSMarketDataField;
  que = new MessageQueue(sizeof(*pDepthMarketData), 600);
  while(1){
    if(que->receive(pDepthMarketData)){
      writeDataEngine(pDepthMarketData);
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
    logger->Fatal("Not have a such file or this file is not readable!");
    exit(1);
  }

  readInit(argv[0], argv[2]);
  thread wtr(writeThread);
  //thread alr(alertThread);

  MdEngine *engine = new CustomMdSpi(InvestorID, Password, MdAddr);
  engine->SetOutput(udppiper);

  logger->Info("初始化行情...");
  engine->Init();
  sleep(1);

  // test class init
  testInit();

  engine->ReqSubscribeMarketData(contracts, contractsnum);
  wtr.join();
  engine->Join();

  engine->Release();

  return 0;
}
