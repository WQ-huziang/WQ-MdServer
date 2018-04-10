//
//
// Author : huziang
// this is a mongodb database complete

#ifndef WZUTIL_MONGODBENGINE_H_
#define WZUTIL_MONGODBENGINE_H_

#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include "DataEngine.h"

using bsoncxx::builder::stream::document;

class MongodbEngine : public DataEngine {
 public:
  static DataEngine* getInstance();
  int find(vector<map<string, string>> &mds, const document &doc);   // find by bson

  // virtual function complete
  void init();
  int insert_one(const map<string, string> &);
  int insert_many(const vector<map<string, string>> &);
  int update_one(const KeyValue &, const vector<KeyValue> &);
  int update_many(const KeyValue &, const vector<KeyValue> &);
  int find_one(map<string, string> &, const vector<KeyValue> &, const char ID[20] = "\0");
  int find_many(vector<map<string, string>> &, const vector<KeyValue> &, const char ID[20] = "\0");
  int delete_one(const vector<KeyValue> &, const char ID[20] = "\0");
  int delete_many(const vector<KeyValue> &, const char ID[20] = "\0");

  // set index
  int set_index(string, bool isascending = true);

 protected:
  MongodbEngine();

 private:
  mongocxx::client conn;
};

#endif  // WZUTIL_MONGODBENGINE_H_
