/***************************************************************************
Copyright(C) 2018, Wizard Quant
Author: huangxiaolin, luoqingming
Description:class template SignalHandler: Monitor the signal from OS when , 
Date: 2018-04-16
***************************************************************************/
#ifndef SIGNALHANDLER_HPP_
#define SIGNALHANDLER_HPP_
#include <csignal>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <map>
#include <queue>
#include "queuemanager.hpp"

#ifndef DataType
#define DataType Frame
#endif

#ifndef QueueSize
#define QueueSize 1024
#endif

#ifndef ReaderSize
#define ReaderSize 4
#endif

#ifndef SHM_FAILED
#define SHM_FAILED -1
#endif

using std::map;
using std::queue;

/***************************************************************************
Description: save pipeMode and readerId will be used when remove the reader
****************************************************************************/
struct SignalMapData
{
  int pipeMode;
  int readerId;
};

static map<int, queue<SignalMapData> > signalMap;

static QueueManager<DataType, QueueSize, ReaderSize> *signal_queue_manager;

/***************************************************************************
Description: catch the signal and handle it
****************************************************************************/
class SignalHandler
{
public:

	SignalHandler();
	~SignalHandler();

    /*************************************************
    Function: listenSignal
    Description: call the signal fuction to listen the SIG of current proccess
    InputParameter:
       signalType: signal type (SIGABRT or SIGSEGV or SIGTERM or..).
    Return: 0 if listen succeed, -1 if failed
    *************************************************/
	int listenSignal(int signalType);

	static int initSignalQueueManager(const int &m_key, const int &m_size, const int &m_flag, int &m_shmid, char* & m_memory_addr);


    /*************************************************
    Function: handleSignal
    Description: handle the signal according to signal type
    InputParameter:
       signalType: signal type (SIGABRT or SIGSEGV or SIGTERM or..).
    Return: none
    *************************************************/
	static void handleSignal(int signalType);

	/*************************************************
    Function: addToMap
    Description: add a proccess's pid and pipeMode, readerId
    InputParameter:
       pid: proccess's pid
       pipeMode: proccess's pipeMode
       readerId: proccess's readerId
    Return: 0 if addToMap succeed, -1 if failed
    *************************************************/
	int addToMap(int pid,int pipeMode,int readerId);

	/*************************************************
    Function: handleSignal
    Description: handle the signal according to signal type
    InputParameter:
       signalType: signal type (SIGABRT or SIGSEGV or SIGTERM or..).
    Return: 0 if release succeed, -1 if failed
    *************************************************/
	static int releaseReader(QueueManager<DataType, QueueSize, ReaderSize> *queue_manager, int reader_id, int piperMode);
	
private:

};


SignalHandler::SignalHandler(){
	signalMap.clear();
}

SignalHandler::~SignalHandler(){

}

int SignalHandler::initSignalQueueManager(const int &m_key, const int &m_size, const int &m_flag, int &m_shmid, char* & m_memory_addr){
	// call shmget and use return value to initialize shared memory address pointer
	m_shmid = shmget(m_key, m_size, m_flag);

	if ( m_shmid == -1 ) {
		LOG(ERROR) << "shared memory create failed";
		return -1;
	}

	// call shmat to attach shared memory
	m_memory_addr = reinterpret_cast<char*>(shmat(m_shmid, NULL, 0));

	if ( m_memory_addr == (char*)SHM_FAILED ) {
		LOG(ERROR) << "shared memory m_memory_addr attach failed";
		return -1;
	}

	// init the signal_queue_manager
	signal_queue_manager = reinterpret_cast<QueueManager<DataType, QueueSize, ReaderSize> * > (m_memory_addr);

	LOG(ERROR) << "shared memory create succeed, key = " << m_key << ", size = " << m_size << ", shmid = " << m_shmid;

	return 0;
}

int SignalHandler::listenSignal(int signalType){
	if(signal(signalType,handleSignal) == SIG_ERR){
		return -1;
	}
	return 0;
}



void SignalHandler::handleSignal(int signalType){
	int pid = getpid();
	map<int, queue<SignalMapData> >::iterator itr;
	itr = signalMap.find(pid);
	if(itr != signalMap.end()) {
	}
	else {
		LOG(ERROR) << "No pid:" << pid;
	}
	LOG(INFO) << "pid = " << pid;
	SignalMapData sd;
	switch (signalType) {
		case SIGINT:
			printf("Interrupt signal %d(SIGINT) received\n", signalType);
			while (!itr->second.empty()) {
				sd = itr->second.front();
				itr->second.pop();
				SignalHandler::releaseReader(signal_queue_manager,sd.pipeMode,sd.readerId);
			}
			break;
		case SIGFPE:
			printf("Interrupt signal %d(SIGFPE) received\n", signalType);
			break;
		case SIGILL:
			printf("Interrupt signal %d(SIGILL) received\n", signalType);
			break;
		case SIGABRT:
			printf("Interrupt signal %d(SIGABRT) received\n", signalType);
			break;
		case SIGKILL:
			printf("Interrupt signal %d(SIGKILL) received\n", signalType);
			break;
		case SIGTERM:
			printf("Interrupt signal %d(SIGTERM) received\n", signalType);
			while (!itr->second.empty()) {
				sd = itr->second.front();
				itr->second.pop();
				SignalHandler::releaseReader(signal_queue_manager,sd.pipeMode,sd.readerId);
			}
			exit(0);
			break;
		case SIGSEGV:
			printf("Interrupt signal %d(SIGSEGV) received\n", signalType);
			break;
		default:
			printf("Unkown signal\n");
			break;
	}
}

int SignalHandler::addToMap(int pid,int pipeMode,int readerId){
	SignalMapData sd;
	sd.pipeMode = pipeMode;
	sd.readerId = readerId;

	map<int, queue<SignalMapData> >::iterator itr;
	itr = signalMap.find(pid);
	if(itr != signalMap.end()) {
		itr->second.push(sd);
	}
	else {
		queue<SignalMapData> que;
		que.push(sd);
		signalMap[pid] = que;
	}

	return 0;
}

int SignalHandler::releaseReader(QueueManager<DataType, QueueSize, ReaderSize> *queue_manager, int piperMode, int reader_id){
  if(piperMode == 0) { // server
    // hang reader of the frame_req_queue and release the reader_id
    int result = queue_manager -> frame_req_queue.removeReader(reader_id);
    printf("call releaseReader() as mode 0, result is:%d\n", result);
    return result;
  }
  else if(piperMode == 1){ // client
    // hang reader of the frame_rec_queue and release the reader_id
    int result = queue_manager -> frame_rec_queue.removeReader(reader_id);
    printf("call releaseReader() as mode 1, result is:%d\n", result);
    return result;
  }
  return -1;
}
#endif //SIGNALHANDLER_HPP_