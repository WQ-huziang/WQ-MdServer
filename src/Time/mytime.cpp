//
//
// Author : huziang
// This is a test file

#include "mytime.h"
#include <unistd.h>
#include <sys/stat.h>

string Time::path = "../test/sending-time-data/";

Time::Time() {
  gettimeofday( &this->begin, NULL );
  // create new floder
  if (access(path.c_str(), W_OK) == -1) {
    mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  }
}

Time::~Time() {
  fclose(fp);
}

void Time::Init() {
  string filepath = "timedata.csv";
  string dicpath = path;
  dicpath += filepath;
  fp = fopen(dicpath.c_str(), "w");
  fprintf(fp, "ID,start,end\n");
  fclose(fp);
  fp = fopen(dicpath.c_str(), "a+");
}

long Time::GetDiffTime() {
  struct timeval now;
  gettimeofday( &now, NULL );
  return 1000000 * ( now.tv_sec - begin.tv_sec ) + now.tv_usec - begin.tv_usec;
}

void Time::WriteName(char *name) {
  fprintf(fp, "%s,", name);
  fflush(fp);
}

void Time::WriteStart() {
  fprintf(fp, "%ld,", GetDiffTime());
  fflush(fp);
}

void Time::WriteEnd() {
  fprintf(fp, "%ld\n", GetDiffTime());
  fflush(fp);
}