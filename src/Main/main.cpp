/***************************************************************************
Copyright(C) 2018, Wizard Quant
Author: huziang
Description: This is main.cpp file by md server
Date: 2018年5月3日 星期四 下午3:29
****************************************************************************/

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

char **contracts;                        // constracts' name list
int contractsnum;                        // constracts' size
TThostFtdcInvestorIDType InvestorID;     // user ID
TThostFtdcPasswordType Password;         // user password
char contractsfile[50];                  // the file stored constracts' name list
char MdAddr[50];                         // mds' address

Logger *logger;
MemEngine<Frame, 1024, 1024> *mempiper;
DataEngine *db;

/*************************************************
Function: processInstrumentIDList
Description: Read given file, and split it into
constracts' name list
InputParameter:
  list: constracts' name list
  filename: the given files' path
Return: the size of constracts' name list
*************************************************/
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

/*************************************************
Function: init
Description: init function, read information by given
.ini file
InputParameter:
  proname: projects' name
  filepath: the .ini files' path
Return: none
*************************************************/
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

  // init memory piper
  mempiper = new MemEngine<Frame, 1024, 1024>();
  mempiper->init(filepath, WZ_PIPER_CLIENT, WZ_PIPER_BLOCK);

  // init data engine
  db = MongodbEngine::getInstance();
  db->init();
  db->setLibname("Md");
  db->setTablename("TSMarketDataField");

  // start thread
  thread wtr(writeThread);
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

  // init mdengine and set output
  MdEngine *engine = new CustomMdSpi(InvestorID, Password, MdAddr);
  engine->SetOutput(mempiper);

  logger->Info("初始化行情...");
  engine->Init();
  sleep(1);  // in order to given enough time to login user

  engine->ReqSubscribeMarketData(contracts, contractsnum);

  wtr.join();
  engine->Join();
  engine->Release();

  return 0;
}
