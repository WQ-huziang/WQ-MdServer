//
//
// Author : huziang
// include class DataEngine and struct

#ifndef WZUTILS_DATAENGINE_H_
#define WZUTILS_DATAENGINE_H_

#include <cstring>
#include <iostream>
#include <map>
#include "tsdatastruct.h"
using std::vector;
using std::string;
using std::map;

struct KeyValue {
  string key;
  bool sides;
  string minvalue;
  string maxvalue;

  KeyValue() {
    sides = false;
  }
  KeyValue(const string _key, const string value)
    : key(_key),
      minvalue(value) {
      sides = false;
  }

  KeyValue(const string _key, const string _minvalue, const string _maxvalue)
    : key(_key),
      minvalue(_minvalue),
      maxvalue(_maxvalue) {
      sides = false;
  }
};

class DataEngine {
 public:
  inline void setLibname(const char lib[20]) { strcpy(libname, lib); }
  inline void setTablename(const char table[20]) { strcpy(tablename, table); }

  // using map and vector<map> to translate all kinds of struct
  virtual void init() = 0;
  virtual int insert_one(const map<string, string> &) = 0;
  virtual int insert_many(const vector<std::map<string, string>> &) = 0;
  virtual int update_one(const KeyValue &, const vector<KeyValue> &) = 0;
  virtual int update_many(const KeyValue &, const vector<KeyValue> &) = 0;
  virtual int find_one(map<string, string> &, const vector<KeyValue> &, const char ID[20] = "\0") = 0;
  virtual int find_many(vector<map<string, string>> &, const vector<KeyValue> &, const char ID[20] = "\0") = 0;
  virtual int delete_one(const vector<KeyValue> &, const char ID[20] = "\0") = 0;
  virtual int delete_many(const vector<KeyValue> &, const char ID[20] = "\0") = 0;

  // set index
  virtual int set_index(string, bool isascending = true) = 0;

  // get max value
  virtual int get_max_item(map<string, string> &, const string &) = 0;

  // get latest item
  virtual int get_latest_item(vector<map<string, string>> &, const char ID[20], int ) = 0;

 protected:
  DataEngine() {}
  static DataEngine *instance;
  char libname[20];
  char tablename[20];
};

DataEngine *DataEngine::instance = NULL;

#endif  // WZUTILS_DATAENGINE_H_