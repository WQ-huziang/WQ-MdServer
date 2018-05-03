//
// Created by wesley on 18-4-20.
//

#ifndef STRATEGY_LOGMODE_H
#define STRATEGY_LOGMODE_H

//#define __DEBUG__

#ifdef __DEBUG__
#define DEBUG(format,...) printf("[" __TIME__ " " __FILE__ ":%d] " format "\n", __LINE__, ##__VA_ARGS__)
#else
#define DEBUG(format,...)
#endif

// 输出重定向

#endif //STRATEGY_LOGMODE_H
