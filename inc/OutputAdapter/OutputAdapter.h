//
//
// Author : lijiaheng
// This is a base output class

#ifndef OUTPUTADAPTER_H
#define OUTPUTADAPTER_H

#include <iostream>
#include "OutputAdapter/Frame.h"

class OutputAdapter{

 public:
  OutputAdapter() {};
  ~OutputAdapter() {};
  virtual void init() = 0;
  virtual void send(Frame dataframe) = 0;
  virtual void Close() = 0;

};

#endif