//
//
// Author : huziang
// This is a test file, test whether it has block

#ifndef TEST_H_
#define TEST_H_

#include <sys/time.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
using std::map;
using std::string;

class Time {
public:
  Time();
  ~Time();
  long SetMap(char *list[], int num);
  long GetDiffTime();
  void WriteStart(char *name);
  void WriteEnd(char *name);

private:
  bool lock1, lock2;
  map<string, FILE*> fpmap;
  struct timeval begin;
};

#endif  // TEST_H_