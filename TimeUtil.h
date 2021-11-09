//
// Created by masker on 2021/11/9.
//

#ifndef IM_FOR_LINUX_TIMEUTIL_H
#define IM_FOR_LINUX_TIMEUTIL_H



#include <ctime>
#include <iostream>
#include <cstdlib>
#include <string>

#pragma once
using namespace std;
class TimeUtil
{
public:
    TimeUtil();
    ~TimeUtil();
    void TimeToString(time_t time1, char *szTime);
    static time_t StringToTime(char * szTime);
    string AddMonth(time_t &tTime);
};


#endif //IM_FOR_LINUX_TIMEUTIL_H
