//
//
// Author : huziang
// This is a test file

#include "test.h"

Time::Time() {
  gettimeofday( &this->begin, NULL );
}

Time::~Time() {
  for (auto it : fpmap) {
    fclose(it.second);
  }
}

long Time::SetMap(char *list[], int num) {
  for (int i = 0; i < num; i++) {
    string filepath = list[i];
    string dicpath = "/home/huziang/Desktop/MdServer/test/sending-time-data/";
    dicpath += filepath;
    FILE *fp = fopen(dicpath.c_str(), "w");
    fclose(fp);
    fp = fopen(dicpath.c_str(), "a+");
    fpmap[filepath] = fp;
  }
}

long Time::GetDiffTime() {
  struct timeval now;
  gettimeofday( &now, NULL );
  return 1000000 * ( now.tv_sec - begin.tv_sec ) + now.tv_usec - begin.tv_usec;
}

void Time::WriteStart(char *name) {
  FILE *fp = fpmap[string(name)];
  fprintf(fp, "START:%ld\n", GetDiffTime());
  fflush(fp);
}

void Time::WriteEnd(char *name) {
  FILE *fp = fpmap[string(name)];
  fprintf(fp, "END:%ld\n", GetDiffTime());
  fflush(fp);
}