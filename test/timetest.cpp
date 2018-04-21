//
//
// Author : huziang
// Using benchmark to test mdserver

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
#include "messagequeue.h"
#include "wzsocket_inc/udp.h"
#include "logger.h"
#include "Thread/dataenginethread.h"
using namespace std;

#define MAX_NUM 1000

CThostFtdcDepthMarketDataField input_array[MAX_NUM];
CustomMdSpi *engine;
extern MessageQueue *que;
WZPiper<UdpSocket> *udppiper;
Logger *logger;
DataEngine *db;

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

static void BM_OnRtnDepthMarketData(benchmark::State& state) {
  int num = 0;
  while (state.KeepRunning()) {
    state.PauseTiming();
    num = num == MAX_NUM - 1 ? 0 : num + 1;
    state.ResumeTiming();
    engine->OnRtnDepthMarketData(&input_array[num]);
    usleep(10000);
  }
}

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

BENCHMARK(BM_OnRtnDepthMarketData);
BENCHMARK(BM_writeDataEngine);

void init() {
  // init logger
  logger = new Logger("timetest");
  logger->ParseConfigInfo("../test/config.ini");

  // init udppiper
  udppiper = new WZPiper<UdpSocket>();
  udppiper->init("../test/config.ini", WZ_PIPER_CLIENT, WZ_PIPER_BLOCK);

  // init mdengine
  engine = new CustomMdSpi("112586", "821361187", "tcp://180.168.146.187:10010");
  engine->SetOutput(udppiper);

  // init messagequeue
  TSMarketDataField *p;
  que = new MessageQueue(sizeof(p), 600);

  // init data engine
  db = MongodbEngine::getInstance();
  db->init();
  db->setLibname("Test");
  db->setTablename("TSMarketDataField");
}

int main(int argc, char** argv) {
  ifstream fin("../test/data.csv");
  TSMarketDataField ts;
  for (int i = 0; i < MAX_NUM; i++) {
    scanTS(fin, ts);
    parseTo(ts, input_array[i]);
  }
  fin.close();

  init();

  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}