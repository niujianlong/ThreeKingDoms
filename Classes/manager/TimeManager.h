//
//  TimeManager.h
//  threeKingdoms
//  Created by sma11case on 14-1-4.
//
//

#ifndef __threeKingdoms__TimeManager__
#define __threeKingdoms__TimeManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

enum TimeType
{
    TimeType_morning,
    TimeType_dusk,
    TimeType_night,
    TimeType_dayTime,
};

class TimeManager:public CCObject
{
public:
    CLASS_INSTANCE(TimeManager);
    bool init();
    
    int64_t getSystemTimeM();
    
    int getSystemTime();
    
    //t1为参考时间 t2为要比较的时间
    bool isLaterDay(int64_t t1,int64_t t2);
    bool isSameDay(int64_t t1,int64_t t2);
    
    bool includeSomeWeekDay(int64_t t1,int64_t t2,int weekDay);
    
    int getYear(int64_t t);
    int getMonth(int64_t t);
    int getDay(int64_t t);
    int getWeekDay(int64_t t);
    int getHour(int64_t t);
    
    TimeType getTimeType();
    
private:
    struct tm* getTimeStruct(int64_t t);
};

#endif /* defined(__threeKingdoms__TimeManager__) */
