//
//
// Author : huziang
// This is a test file, test whether it has block

#ifndef MDSERVER_TIME_H_
#define MDSERVER_TIME_H_

#include <sys/time.h>
#include <stdio.h>
#include <iostream>
#include <string>
using std::string;

class Time {
 public:
  Time();
  ~Time();
  void Init();
  long GetDiffTime();
  void WriteName(char *name);
  void WriteStart();
  void WriteEnd();

 private:
  static string path;
  bool lock1, lock2;
  FILE *fp;
  struct timeval begin;
};

#endif  // MDSERVER_TIME_H_