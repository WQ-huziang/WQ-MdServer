//
// Author: luojunbin
//

#ifndef SOCKETSERVER_H_
#define SOCKETSERVER_H_

#include "frame.h"

template <class T>
class WZServer
{
public:
  WZServer();
  int init(char file_path[256]);
  int epollInit();
  int wzRecv(Frame &frame);
  int wzSend(Frame &frame);
  int wzBind();

private:
  T* t;
};

template <class T>
WZServer<T>::WZServer()
{
  t = new T();
}

template <class T>
int WZServer<T>::init(char file_path[256])
{
  return t->init(file_path);
}

template <class T>
int WZServer<T>::epollInit()
{
  if (t->epollInit() == -1)
    return -1;
  return 0;
}

template <class T>
int WZServer<T>::wzRecv(Frame &frame)
{
  return t->wzRecv(frame);
}

template <class T>
int WZServer<T>::wzSend(Frame &frame)
{
  if (t->wzSend(frame) == -1)
    return -1;
  return 0;
}

template <class T>
int WZServer<T>::wzBind()
{
  if (t->wzBind() == -1)
    return -1;
  return 0;
}

#endif