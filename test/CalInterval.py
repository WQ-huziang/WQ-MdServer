import numpy as np
import sys
import re


class CalInterval:

    def __init__(self):
        pass

    def loadData(self,file):
        f = open(file,'r',encoding='utf-8')
        time =[]
        line = f.readline()
        while line:
            cutline = line.split('\t')
            time.extend(cutline)
            line = f.readline()
        time_int = []
        for i in range(len(time)):
            if time[i] != '':
                time_int.append(int(time[i])/3096.4785)
        time_int.sort()
        return time_int

    def calTimeInterval_(self, time1, time2):
        interval = (sum(time1) - sum(time2))/1024
        return interval

    def calTimeInterval(self, time1, time2):
        rates = [99, 255, 511, 767, 1023]
        rate_names = ["1% : ", "25% : ", "50% : ", "75% : ", "100% : "]
        time = []
        for i in range(len(time1)):
            time.append(time1[i] - time2[i])
        time.sort()
        for i in range(len(rates)):
            print(rate_names[i], time[rates[i]])

if __name__ == '__main__':
    CI = CalInterval()
    md_recv = CI.loadData("../test/time/md_recvtime.csv")
    md_save = CI.loadData("../test/time/md_savetime.csv")
    md_send = CI.loadData("../test/time/md_sendtime.csv")

    print("-------- Md --------")
    print("md: recv - send")
    CI.calTimeInterval(md_send, md_recv)
    md_recv_send = CI.calTimeInterval_(md_send, md_recv)
    print("avg : ", md_recv_send)
    print(" ")

    print("md: send - save")
    CI.calTimeInterval(md_save, md_send)
    md_send_save = CI.calTimeInterval_(md_save, md_send)
    print("avg : ", md_send_save)
    print(" ")

    print("md: recv - save")
    CI.calTimeInterval(md_save, md_recv)
    md_recv_save = CI.calTimeInterval_(md_save, md_recv)
    print("avg : ", md_recv_save)
    print(" ")
