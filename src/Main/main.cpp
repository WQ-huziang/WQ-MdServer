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
#include "custommdspi.h"
#include "logger.h"
#include "mongodbengine.h"
#include "Thread/dataenginethread.h"
using std::thread;

int contractsnum;
char **contracts;
TThostFtdcInvestorIDType InvestorID;
TThostFtdcPasswordType Password;
char contractsfile[50];
char MdAddr[50];

Logger *logger;
MemEngine<Frame, 1024, 1024> *mempiper;
DataEngine *db;

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

void init(char *progname, char *filepath){
  // get parameter
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

  // init logger
  logger = new Logger(progname);
  logger->ParseConfigInfo(filepath);

  // init data engine
  db = MongodbEngine::getInstance();
  db->init();
  db->setLibname("Md");
  db->setTablename("TSMarketDataField");

  // init memory piper
  mempiper = new MemEngine<Frame, 1024, 1024>();
  mempiper->init(filepath, WZ_PIPER_CLIENT, WZ_PIPER_BLOCK);
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

  init(argv[0], argv[2]);
  thread wtr(writeThread);

  MdEngine *engine = new CustomMdSpi(InvestorID, Password, MdAddr);
  engine->SetOutput(mempiper);

  logger->Info("初始化行情...");
  engine->Init();
  sleep(1);

  engine->ReqSubscribeMarketData(contracts, contractsnum);

  wtr.join();
  engine->Join();

  engine->Release();

  return 0;
}
