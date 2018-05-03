//
//
// Author : lijiaheng
//   This is a class inherit virtual class MdEngine and
// class CThostFtdcMdSpi, and have instance CThostFtdcMdApi

#ifndef MDSERVER_CUSTOMMDSPI_H_
#define MDSERVER_CUSTOMMDSPI_H_

#include <string>
#include "mdengine.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcUserApiStruct.h"

using std::string;

typedef char String[20];

class CustomMdSpi : public MdEngine, public CThostFtdcMdSpi
{
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

 //�Զ���
 public:
  CustomMdSpi(TThostFtdcInvestorIDType uid, 
              TThostFtdcPasswordType password, 
              char *mdaddr, 
              char *datadir = "./data");
  // virtual function
  void Init();
  void Join();
  void Release();
  void ReqSubscribeMarketData(char *contracts[], int contractsnum);

  void ReqUserLogin();

private:
  // DISALLOW_COPY_AND_ASSIGN(CustomMdSpi);
  TThostFtdcBrokerIDType BrokerID;
  TThostFtdcInvestorIDType InvestorID;
  TThostFtdcPasswordType Password;
  CThostFtdcMdApi *pUserApi;
  bool lock;
};

#endif  // MDSERVER_CUSTOMMDSPI_H_