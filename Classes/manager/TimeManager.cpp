//
//  TimeManager.cpp
//  threeKingdoms
//  Created by sma11case 14-1-4.
//
//

#include "TimeManager.h"

bool TimeManager::init()
{
    char *tz;
    tz = getenv("TZ");
    return true;
}

int64_t TimeManager::getSystemTimeM()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    int64_t r = int64_t(tv.tv_sec) * 1000 + int64_t(tv.tv_usec) / 1000;
    return r;
}

int TimeManager::getSystemTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec;
}

int TimeManager::getYear(int64_t t)
{
    time_t temp = t / 1000;
    tm *timeStruct = getTimeStruct(temp);
    return timeStruct->tm_year;
}

int TimeManager::getMonth(int64_t t)
{
    time_t temp = t / 1000;
    tm *timeStruct = getTimeStruct(temp);
    return timeStruct->tm_mon;
}

int TimeManager::getDay(int64_t t)
{
    time_t temp = t / 1000;
    tm *timeStruct = getTimeStruct(temp);
    return timeStruct->tm_mday;
}

int TimeManager::getWeekDay(int64_t t)
{
    time_t temp = t / 1000;
    tm *timeStruct = getTimeStruct(temp);
    return timeStruct->tm_wday;
}

int TimeManager::getHour(int64_t t)
{
    time_t temp = t / 1000;
    tm *timeStruct = getTimeStruct(temp);
    return timeStruct->tm_hour;
}

bool TimeManager::isLaterDay(int64_t t1, int64_t t2)
{
    if(t1 >= t2){
        return false;
    }else{
        int y1 = getYear(t1);
        int y2 = getYear(t2);
        int m1 = getMonth(t1);
        int m2 = getMonth(t2);
        int d1 = getDay(t1);
        int d2 = getDay(t2);
        
        if(y1 != y2 || m1 != m2 || d1 != d2){
            return true;
        }
        return false;
    }
}

bool TimeManager::isSameDay(int64_t t1, int64_t t2)
{

    int y1 = getYear(t1);
    int y2 = getYear(t2);
    int m1 = getMonth(t1);
    int m2 = getMonth(t2);
    int d1 = getDay(t1);
    int d2 = getDay(t2);
    
    if(y1 == y2 && m1 == m2 && d1 == d2){
        return true;
    }
    return false;
    
}

bool TimeManager::includeSomeWeekDay(int64_t t1, int64_t t2,int weekDay)
{
    if(t1 >= t2){
        return false;
    }else{
        int i=0;
        for(;;){
            i++;
            int64_t temp = t1 + 3600*24*1000 * i;
            if(isSameDay(t2,temp) || isLaterDay(t2,temp)){
                return false;
            }else{
                if(getWeekDay(temp) == weekDay){
                    return true;
                }
            }
        }
    }
}

TimeType TimeManager::getTimeType()
{
    int hour = getHour(getSystemTimeM());
    if(hour == 6 || hour == 7){
        return TimeType_morning;
    }else if(hour == 18){
        return TimeType_dusk;
    }else if(hour >=8 && hour <=17){
        return TimeType_dayTime;
    }else{
        return TimeType_night;
    }
}

struct tm* TimeManager::getTimeStruct(int64_t t)
{
    time_t timer;
    struct tm *tblock;
    
    if(t > 0){
        timer = t;
    }else{
        timer = time(NULL);
    }
    tblock = localtime(&timer);
    return tblock;
}
