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

#endif  // TEST_H_