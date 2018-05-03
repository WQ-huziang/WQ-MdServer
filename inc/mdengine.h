/***************************************************************************
Copyright(C) 2018, Wizard Quant
Author: lijiaheng
Description: this is a base mdserver virtual class used in main.cpp
Date: 2018年5月3日 星期四 下午2:20
****************************************************************************/

#ifndef MDSERVER_MDENGINE_H_
#define MDSERVER_MDENGINE_H_

#include "tsdatastruct.h"
#include "wzmem_inc/memengine.hpp"

/***************************************************************************
Description: MdEngine get data from other place (such as CTP), and transfrom
            data to Frame struct, then transport Frame to other process
****************************************************************************/
class MdEngine {
 public:

  /*************************************************
  Function: MdEngine
  Description: Constructor
  InputParameter:
    _output: outside output to transport Frame struct
  Return: none
  *************************************************/
  MdEngine(MemEngine<Frame, 1024, 10>* _output = NULL)
    : output(_output) {}

  /*************************************************
  Function: Init
  Description: Virtual function, initialization needed variable
  InputParameter: none
  Return: none
  *************************************************/
  virtual void Init() = 0;

  /*************************************************
  Function: Join
  Description: Virtual function, wait all thread end
  InputParameter: none
  Return: none
  *************************************************/
  virtual void Join() = 0;

  /*************************************************
  Function: Release 
  Description: Virtual function, release all holded data
  InputParameter: none
  Return: none
  *************************************************/
  virtual void Release() = 0;


  /*************************************************
  Function: ReqSubscribeMarketData 
  Description: Virtual function, to subscribe contract
  InputParameter:
    contracts: constracts' name
    contractsnum: constracts' size
  Return: none
  *************************************************/
  virtual void ReqSubscribeMarketData(char *contracts[], int contractsnum) = 0;

  /*************************************************
  Function: SetOutput
  Description: Set output, same with constructor
  InputParameter:
    _output: outside output to transport Frame struct
  Return: none
  *************************************************/
  void SetOutput(MemEngine<Frame, 1024, 10> *_output);

  /*************************************************
  Function: RtnDepthMarketData
  Description: transform TSMarketDataField to Frame at first,
    then transport Frame data by output
  InputParameter:
    pDepthMarketData: the given data
  Return: none
  *************************************************/
  void RtnDepthMarketData(TSMarketDataField* pDepthMarketData);

 private:
  // DISALLOW_COPY_AND_ASSIGN(MdEngine);
  MemEngine<Frame, 1024, 10> *output;  // use to transport Frame data
  Frame frame;                           // the Frame object, avoid to repeat construct
};

#endif  // MDSERVER_MDENGINE_H_
