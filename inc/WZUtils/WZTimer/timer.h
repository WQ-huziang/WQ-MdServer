/***************************************************************************
Copyright(C) 2018, Wizard Quant
Author: luoqingming
Description: get timestamp by TSC
Date: 2018-04-20
***************************************************************************/


#ifndef TSCTIMER_HPP_
#define TSCTIMER_HPP_


#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <chrono>

#ifndef FREQUENCY_US
#define FREQUENCY_US 3096.4785
#endif

#define TIMES 1024

using dur = std::chrono::duration<int64_t, std::micro>;
static double FREQUENCY;


/*
 * 高精度，低时延获得TSC时间
 */
inline unsigned long long getTimeByTSC(){
#if defined(__GNUC__)
#   if defined(__i386__)
    uint64_t x;
        __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
        return x;
#   elif defined(__x86_64__)
    uint32_t hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)lo) | ((uint64_t)hi << 32);
#   else
#       error Unsupported architecture.
#   endif
#elif defined(_MSC_VER)
    __asm {
            return __rdtsc();
        }
    #else
    #   error Other compilers not supported...
#endif
}
/*
 * 调用之间返回当前时间点到2018年04月19日 10:29:13的us级别
 * 返回 time_t 实际上是个 long
 */
inline std::time_t getTimeStamp()
{
    std::chrono::time_point<std::chrono::system_clock,std::chrono::microseconds> tp = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
    auto tmp=std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count();
    // 以 2018年04月19日 10:29:13 时间点往后计时
    timestamp -= 1524104953746000;
    return timestamp;
}

/*
 * 输入t1 为开始时间，t2为结束时间， 返回long为us数
 * 返回 time_t 实际上是个 long
 */
inline long getDuration(time_t t1, time_t t2){
    auto mt1 = std::chrono::microseconds(t1);
    auto mt2 = std::chrono::microseconds(t2);
    dur time_span = std::chrono::duration_cast<dur>(mt2-mt1);
    long time = time_span.count();
    return time;
}


inline double getDurationByTSC(unsigned long long &start, unsigned long long &end){
    return (end - start) /  FREQUENCY;
}

inline double getInterval(){
    long start = getTimeStamp();
    unsigned long long tsc_start = getTimeByTSC();
    sleep(5);
    unsigned long long tsc_end = getTimeByTSC();
    long end = getTimeStamp();
    long interval = getDuration(start, end);
    // cout << "(unsigned long long) interval:" << (unsigned long long) interval << "(long) interval:" << interval << " tsc_start:" << tsc_start << " tsc_end:" << tsc_end << " tsc duration:" << tsc_end - tsc_start <<endl;

    double tsc_interval = (tsc_end - tsc_start) / ((double) interval);
    // TODO: tsc_interval =

    return tsc_interval;
}

inline double getFrequency(int me_cycle){

    double mean = 0;
    for (int i =0; i < me_cycle; i++)
        mean += getInterval();
    mean /= me_cycle;
    FREQUENCY = mean;
    printf("final mean = %10lf circle/us \n", mean) ;
    return mean;
}


#endif // TSCTIMER_HPP_
