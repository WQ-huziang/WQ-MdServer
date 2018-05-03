/***************************************************************************
Copyright(C) 2018, Wizard Quant
Author: huziang
Description: Using benchmark to test mdserver
Date: 2018年5月3日 星期四 下午3:37
****************************************************************************/

#include <benchmark/benchmark.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <fstream>
#include <thread>
#include <unistd.h>
#include "custommdspi.h"
#include "TS2CTPparser.h"
#include "mongodbengine.h"
#include "wzsocket_inc/udp.h"
#include "logger.h"
#include "Thread/dataenginethread.h"
using namespace std;

#define MAX_NUM 1000

CThostFtdcDepthMarketDataField input_array[MAX_NUM];
CustomMdSpi *engine;
extern FQueue<TSMarketDataField*> que;
MemEngine<Frame, 1024, 10> *mempiper;
Logger *logger;
DataEngine *db;

/*************************************************
Function: scanTS
Description: read TS object by file
InputParameter: none
Return: none
*************************************************/
void scanTS(ifstream &fin, TSMarketDataField &pDepthMarketData) {
  fin >> pDepthMarketData.TradingDay
     >> pDepthMarketData.InstrumentID
     >> pDepthMarketData.LastPrice
     >> pDepthMarketData.PreSettlementPrice
     >> pDepthMarketData.PreClosePrice
     >> pDepthMarketData.PreOpenInterest
     >> pDepthMarketData.OpenPrice
     >> pDepthMarketData.HighestPrice
     >> pDepthMarketData.LowestPrice
     >> pDepthMarketData.Volume
     >> pDepthMarketData.Turnover
     >> pDepthMarketData.OpenInterest;
  double temp;
  fin >> temp >> temp
     >> pDepthMarketData.UpperLimitPrice
     >> pDepthMarketData.LowerLimitPrice
     >> pDepthMarketData.UpdateTime
     >> pDepthMarketData.UpdateMillisec
     >> pDepthMarketData.BidPrice1
     >> pDepthMarketData.BidVolume1
     >> pDepthMarketData.AskPrice1
     >> pDepthMarketData.AskVolume1;
}

/***************************************************************************
Description: Test function OnRtnDepthMarketData
****************************************************************************/
static void BM_OnRtnDepthMarketData(benchmark::State& state) {
  int num = 0;
  while (state.KeepRunning()) {
    state.PauseTiming();
    num = num == MAX_NUM - 1 ? 0 : num + 1;
    state.ResumeTiming();
    engine->OnRtnDepthMarketData(&input_array[num]);
  }
}

/***************************************************************************
Description: Test function writeDataEngine
****************************************************************************/
static void BM_writeDataEngine(benchmark::State& state) {
  int num = 0;
  while (state.KeepRunning()) {
    state.PauseTiming();
    num = num == MAX_NUM - 1 ? 0 : num + 1;
    TSMarketDataField ts;
    parseFrom(ts, input_array[num]);
    state.ResumeTiming();
    writeDataEngine(&ts);
  }
}

// set time
BENCHMARK(BM_OnRtnDepthMarketData);
BENCHMARK(BM_writeDataEngine);

/***************************************************************************
Description: init function like main.cpp
****************************************************************************/
void init() {
  // read data from file
  ifstream fin("../test/data.csv");
  TSMarketDataField ts;
  for (int i = 0; i < MAX_NUM; i++) {
    scanTS(fin, ts);
    parseTo(ts, input_array[i]);
  }
  fin.close();

  // init logger
  logger = new Logger("timetest");
  logger->ParseConfigInfo("../test/config.ini");

  // init udppiper
  mempiper = new MemEngine<Frame, 1024, 10>();
  mempiper->init("../test/config.ini", WZ_PIPER_CLIENT, WZ_PIPER_BLOCK);

  // init mdengine
  engine = new CustomMdSpi("112586", "821361187", "tcp://180.168.146.187:10010");
  engine->SetOutput(mempiper);

  // init data engine
  db = MongodbEngine::getInstance();
  db->init();
  db->setLibname("Test");
  db->setTablename("TSMarketDataField");
}

int main(int argc, char** argv) {
  init();

  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}