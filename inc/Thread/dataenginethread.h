//
//
// Author : huziang
// This is a thread function to store data into data engine

#ifndef MDSERVER_DATAENGINETHREAD_H_
#define MDSERVER_DATAENGINETHREAD_H_

#include <csignal>
#include <fstream>
#include "tsdatastruct.h"
#include "dataparse.h"
#include "mongodbengine.h"
#include "logger.h"
#include "messagequeue.h"
using std::map;
using std::vector;


#ifdef DEBUG
#include <chrono>
using std::time_t;
#define TIMES 1024
extern long recvtime[TIMES];
extern long sendtime[TIMES];
extern long timenum;
long savetime[TIMES];

/*
 * 调用之间返回当前时间点到2018年04月19日 10:29:13的us级别
 * 返回 time_t 实际上是个 long
 */
time_t mygetTimeStamp()
{
    std::chrono::time_point<std::chrono::system_clock,std::chrono::microseconds> tp = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
    auto tmp = std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch());
    time_t timestamp = tmp.count();
    // 以 2018年04月19日 10:29:13 时间点往后计时
    timestamp -= 1524104953746000;
    return timestamp;
}

/*
 * 输入t1 为开始时间，t2为结束时间， 返回long为us数
 * 返回 time_t 实际上是个 long
 */
long getDuration(time_t t1, time_t t2) {
    auto mt1 = std::chrono::microseconds(t1);
    auto mt2 = std::chrono::microseconds(t2);
    std::chrono::duration<int64_t, std::micro> time_span = std::chrono::duration_cast<std::chrono::duration<int64_t, std::micro>>(mt2 - mt1);
    long time = time_span.count();
    return time;
}
#endif

MessageQueue *que;
extern DataEngine *db;
extern Logger *logger;
vector<map<string, string>> mds;
map<string, string> md;

void writeDataEngine(TSMarketDataField *pDepthMarketData) {
  // to document
  md.clear();
  parseFrom(md, *pDepthMarketData);

  // documents insert the document
  mds.push_back(md);
#ifdef DEBUG
  if (mds.size() >= TIMES) {
#else
  if (mds.size() >= 50) {
#endif
    if (db->insert_many(mds)) {
      LOG(INFO) << "insert TSMarketDataFields success!";
    } else {
      LOG(ERROR) << "Can't insert TSMarketDataFields!";
    }
    mds.clear();
  }

#ifdef DEBUG
  if (timenum == TIMES) {
    ofstream fout("../test/time/recvtime.txt");
    for (int i = 0; i < TIMES; ++i) {
      fout << recvtime[i] << endl;
    }
    fout.close();

    fout.open("../test/time/sendtime.txt");
    for (int i = 0; i < TIMES; ++i) {
      fout << sendtime[i] << endl;
    }
    fout.close();

    fout.open("../test/time/savetime.txt");
    for (int i = 0; i < TIMES; ++i) {
      fout << savetime[i] << endl;
    }
    fout.close();

    fout.open("../test/time/processinterval.txt");
    long long avg = 0;
    for (int i = 0; i < TIMES; ++i) {
      avg += getDuration(recvtime[i], savetime[i]);
    }
    fout << "AVERAGE: " << avg / TIMES << endl;
    for (int i = 0; i < TIMES; ++i) {
      fout << savetime[i] << endl;
    }
    fout.close();
    exit(0);
  }

  savetime[timenum] = mygetTimeStamp();
#endif
}

void writeThread() {
  // if recieve signal kill or ctrl+c, save remain data
  auto sig_handle = [](int sig) {
    if (sig == SIGTERM || sig == SIGINT) {
      LOG(ERROR) << "Kill Signal recieved!";
    }

    db->insert_many(mds);
    exit(0);
  };
  signal(SIGINT, sig_handle);
  signal(SIGTERM, sig_handle);

  TSMarketDataField *pDepthMarketData = new TSMarketDataField;
  que = new MessageQueue(sizeof(*pDepthMarketData), 600);
  // wait to receive data
  while(1){
    if(que->receive(pDepthMarketData)){
      writeDataEngine(pDepthMarketData);
    }
  }
}

#endif // MDSERVER_DATAENGINETHREAD_H_