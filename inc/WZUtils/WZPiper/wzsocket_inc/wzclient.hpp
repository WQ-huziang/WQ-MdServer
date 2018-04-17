//
// Author: luojunbin
//

#ifndef SOCKETCLIENT_H_
#define SOCKETCLIENT_H_

#include "frame.h"
#include "wzsokect_inc/wzsocket.h"

template <class T>
class WZClient
{
public:
  WZClient();
  int init(char file_path[256]);
  int epollInit();
  int wzRecv(Frame &frame);
  int wzSend(Frame &frame);
  int wzConnect();

private:
  T* t;
};

template <class T>
WZClient<T>::WZClient()
{
  t = new T();
}

template <class T>
int WZClient<T>::init(char file_path[256])
{
  return t->init(file_path);
}

template <class T>
int WZClient<T>::epollInit()
{
  if (t->epollInit() == -1)
    return -1;
  return 0;
}

template <class T>
int WZClient<T>::wzRecv(Frame &frame)
{
  if (t->wzRecv(frame) == -1)
    return -1;
  return 0;
}

template <class T>
int WZClient<T>::wzSend(Frame &frame)
{
  if (t->wzSend(frame) == -1)
    return -1;
  return 0;
}

template <class T>
int WZClient<T>::wzConnect()
{
  return t->wzConnect();
}

#endif