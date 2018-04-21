/***************************************************************************
Copyright(C) 2018, Wizard Quant
Author: huangxiaolin, luoqingming
Description: WZPiper class template is the interface of the piper
Date: 2018-04-09
***************************************************************************/
#ifndef WZPIPER_H_
#define WZPIPER_H_

#include "frame.h"

/***************************************************************************
Description: single writer and multiple reader lockless queue with atomic,
    typename T:the type of IPC  (tcp,udp,memengine)
****************************************************************************/
template <typename T>
class WZPiper{
	public:
		/************************************************* 
		Function: WZPiper
		Description: Constructor, calls the constructor of T
		InputParameter: none
		Return: none
		*************************************************/
		WZPiper();

		/************************************************* 
		Function: ~WZPiper
		Description: Destructor, delete T
		InputParameter: none
		Return: none
		*************************************************/		
		~WZPiper();

		/************************************************* 
		Function: init
		Description: read configure file and init the IPC according to server_client_flag
		InputParameter: 
			file_path: the path of the configure file
			piperMode: the flag to mark server or client,
						0 or WZ_PIPER_SERVER as server,
						1 or WZ_PIPER_CLIENT as client
			blockMode: WZ_PIPER_BLOCK for Recv and Send block the proccess
					   WZ_PIPER_NBLOCK for Recv and Send return without block
		Return: positive if create succeed, -1 if failed
		*************************************************/
		int init(char file_path[256], int piperMode, int blockMode);
		
		/************************************************* 
		Function: Recv
		Description: read configure file and init the IPC according to server_client_flag
		InputParameter: 
			frame: read receive datum from piper to frame
		Return: size of receive data(positive) if receive succeed, -1 if failed
		*************************************************/
		int Recv(Frame &frame);

		/************************************************* 
		Function: Send
		Description: read configure file and init the IPC according to server_client_flag
		InputParameter:
			frame: the datum to send to piper
		Return: 0 if send succeed, -1 if failed
		*************************************************/
		int Send(Frame &frame);

	private:

		T* t; // pointer point to the IPC
};


template<typename T>
WZPiper<T>::WZPiper(){
	t = new T();
}

template<typename T>
WZPiper<T>::~WZPiper(){
	delete t;
}

template<typename T>
int WZPiper<T>::init(char file_path[256], int piperMode, int blockMode){
	return t->init(file_path, piperMode, blockMode);
}

template<typename T>
int WZPiper<T>::Recv(Frame &frame){
	return t->Recv(frame);
}

template<typename T>
int WZPiper<T>::Send(Frame &frame){
	return t->Send(frame);
}

///////////////////////////////////
// The mode of the piper 
// (server or client)
///////////////////////////////////
//server
#define WZ_PIPER_SERVER          0
//client 
#define WZ_PIPER_CLIENT          1
typedef short WZPiperMode;

///////////////////////////////////
// The mode of blocking 
// (blocking or nonblocking)
///////////////////////////////////
//blocking
#define WZ_PIPER_BLOCK           0
//nonblocking
#define WZ_PIPER_NBLOCK			 1
typedef short WZBlockMode;

#endif
