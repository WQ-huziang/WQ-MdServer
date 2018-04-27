//
//
// Author : huziang
// this is a mongodb database complete

#ifndef WZUTIL_MONGODBENGINE_H_
#define WZUTIL_MONGODBENGINE_H_

#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/options/find.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include "dataengine.h"

using bsoncxx::builder::stream::document;

class MongodbEngine : public DataEngine {
 public:
  static DataEngine* getInstance();
  int find(vector<map<string, string>> &mds, const document &doc);   // find by bson

  // virtual function complete
  void init();

  /******************************************
  Function: insert_one
  Description: insert one item into mongodb
  InputParameter: 
    map<string, string>: the map of data that is to be inserted
  Return: 0 if send succeed, -1 if failed
  ******************************************/
  int insert_one(const map<string, string> &);

  /******************************************
  Function: insert_many
  Description: insert many items into mongodb
  InputParameter: 
    vector<map<string, string>>: the vector of the maps of data that is to be inserted
  Return: 0 if send succeed, -1 if failed
  ******************************************/
  int insert_many(const vector<map<string, string>> &);

  /******************************************
  Function: update_one
  Description: update one item in mongodb
  InputParameter: 
    map<string, string>: the map of data that is to be updated
    vector<KeyValue>: the conditions that is used to find the item
  Return: 0 if send succeed, -1 if failed
  ******************************************/
  int update_one(const KeyValue &, const vector<KeyValue> &);

  /******************************************
  Function: update_many
  Description: update many items in mongodb
  InputParameter: 
    vector<map<string, string>>: the vector of the maps of data that is to be update
    vector<KeyValue>: the conditions that is used to find the items
  Return: 0 if send succeed, -1 if failed
  ******************************************/
  int update_many(const KeyValue &, const vector<KeyValue> &);

  /******************************************
  Function: find_one
  Description: find one item from mongodb
  InputParameter: 
    map<string, string>: the map of data that is found from mongodb
    vector<KeyValue>: the conditions that is used to find the item
    ID: the ID of the instrument, NULL means to find all the instrument
  Return: 0 if send succeed, -1 if failed
  ******************************************/
  int find_one(map<string, string> &, const vector<KeyValue> &, const char ID[20] = "\0");

  /******************************************
  Function: find_many
  Description: find some items from mongodb
  InputParameter: 
    vector<map<string, string>>: the vector of the maps of data that is found from mongodb
    vector<KeyValue>: the conditions that is used to find the items
    ID: the ID of the instrument, NULL means to find all the instrument
  Return: 0 if send succeed, -1 if failed
  ******************************************/
  int find_many(vector<map<string, string>> &, const vector<KeyValue> &, const char ID[20] = "\0");

  /******************************************
  Function: delete_one
  Description: delete one item in mongodb
  InputParameter: 
    vector<KeyValue>: the conditions that is used to find the item
    ID: the ID of the instrument, NULL means to find all the instrument
  Return: 0 if send succeed, -1 if failed
  ******************************************/
  int delete_one(const vector<KeyValue> &, const char ID[20] = "\0");

  /******************************************
  Function: delete_many
  Description: delete some items in mongodb
  InputParameter: 
    vector<KeyValue>: the conditions that is used to find the item
    ID: the ID of the instrument, NULL means to find all the instrument
  Return: 0 if send succeed, -1 if failed
  ******************************************/
  int delete_many(const vector<KeyValue> &, const char ID[20] = "\0");

  // set index
  int set_index(string, bool isascending = true);

  /******************************************
  Function: get_max_item
  Description: get the max item according to a key
  InputParameter: 
    map<string, string>: the item found from mongodb
    string: the column which is to be found from
  Return: 0 if send succeed, -1 if failed
  ******************************************/
  int get_max_item(map<string, string> &, const string &);

  /******************************************
  Function: get_latest_item
  Description: get some latest items according to a num
  InputParameter: 
    vector<map<string, string>>: the vector the items found from mongodb
    ID: the ID of the instrument
    int: the number of items
  Return: 0 if send succeed, -1 if failed
  ******************************************/
  int get_latest_item(vector<map<string, string>> &, const char ID[20], int );


 protected:
  MongodbEngine();

 private:
  mongocxx::client conn;

  // latest info
  const string TradingDay = "TradingDay";
  const string UpdateTime = "UpdateTime";

  // write_read_lock
  volatile bool isWriting;
  volatile int isReading;
};

#endif  // WZUTIL_MONGODBENGINE_H_
