/***************************************************************************
Copyright(C) 2018, Wizard Quant
Author: lijiaheng
Description: This is a class inherit virtual class MdEngine and
class CThostFtdcMdSpi, and have instance CThostFtdcMdApi
Date: 2018年5月3日 星期四 下午2:19
****************************************************************************/

#ifndef MDSERVER_CUSTOMMDSPI_H_
#define MDSERVER_CUSTOMMDSPI_H_

#include <string>
#include "mdengine.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcUserApiStruct.h"

using std::string;

/***************************************************************************
Description: CustomMdSpi realize the function defined in MdEngine
            by CTP's api
****************************************************************************/
class CustomMdSpi : public MdEngine, public CThostFtdcMdSpi
{

 /***************************************************************************
 Description: This public function is the realization of Spi
 ****************************************************************************/
 public:
  ///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
  void OnFrontConnected();

  ///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
  ///@param nReason ����ԭ��
  ///        0x1001 �����ʧ��
  ///        0x1002 ����дʧ��
  ///        0x2001 ����������ʱ
  ///        0x2002 ��������ʧ��
  ///        0x2003 �յ�������
  void OnFrontDisconnected(int nReason);

  ///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
  ///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
  void OnHeartBeatWarning(int nTimeLapse);


  ///��¼������Ӧ
  void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///�ǳ�������Ӧ
  void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///����Ӧ��
  void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///��������Ӧ��
  void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///ȡ����������Ӧ��
  void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///����ѯ��Ӧ��
  void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///ȡ������ѯ��Ӧ��
  void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  ///�������֪ͨ
  void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

  ///ѯ��֪ͨ
  void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

 public:

  /*************************************************
  Function: CustomMdSpi
  Description: Constructor
  InputParameter:
    uid: CTP's user ID
    password: CTP's user password, corresponding with uid
    mdaddr: CTP's market datas' tcp addr
    datadir: the floder store ".con" file (created by CTP)
  Return: none
  *************************************************/
  CustomMdSpi(TThostFtdcInvestorIDType uid, 
              TThostFtdcPasswordType password, 
              char *mdaddr, 
              char *datadir = "./data");
  
  /*************************************************
  Function: Init
  Description: Realized function, init pointer pUserApi
  InputParameter: none
  Return: none
  *************************************************/
  void Init();

  /*************************************************
  Function: Join
  Description: Realized function, join pointer pUserApi
  InputParameter: none
  Return: none
  *************************************************/
  void Join();

  /*************************************************
  Function: Release
  Description: Realized function, release pointer pUserApi
  InputParameter: none
  Return: none
  *************************************************/
  void Release();

  /*************************************************
  Function: ReqSubscribeMarketData
  Description: Realized function, send request to CTP
    in order to subscribe CTP's market data
  InputParameter:
    contracts: constracts' name
    contractsnum: constracts' size
  Return: none
  *************************************************/
  void ReqSubscribeMarketData(char *contracts[], int contractsnum);

  /*************************************************
  Function: ReqUserLogin
  Description: Before send request, you need to login at first 
  InputParameter: none
  Return: none
  *************************************************/
  void ReqUserLogin();

private:
  // DISALLOW_COPY_AND_ASSIGN(CustomMdSpi);
  TThostFtdcBrokerIDType BrokerID;         // 9999
  TThostFtdcInvestorIDType InvestorID;     // user's ID
  TThostFtdcPasswordType Password;         // user's passwird
  CThostFtdcMdApi *pUserApi;               // CTP's api pointer
};

#endif  // MDSERVER_CUSTOMMDSPI_H_