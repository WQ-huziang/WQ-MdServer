//
//
// Author : huziang
// complete alert class' function

#include "alert.h"
#include <algorithm>

void Alert::exec(TSMarketDataField &tsmd) {
  for (auto &func : funcs) {
    func(tsmd, *mydb, *output);
  }
}

void Alert::addTrigger(const Func func) {
  funcs.push_back(func);
}

void Alert::delTrigger(const Func func) {
  auto pos = std::find(funcs.begin(), funcs.end(), func);
  if (pos != funcs.end()) {
    funcs.erase(pos);
  }
}