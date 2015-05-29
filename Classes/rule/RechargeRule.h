//
//  RechargeRule.h
//  threeKingdoms
//  Created by sma11case 14-3-6.
//
//

#ifndef __threeKingdoms__RechargeRule__
#define __threeKingdoms__RechargeRule__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class RechargeRule:public CCObject
{
public:
    CLASS_INSTANCE(RechargeRule);
    bool init();
    
    vector<int> getRechargeIdByType(int type);
    
    int getRechargePrice(int rechargeId);
    int getRechargeGoldCount(int rechargeId);
    string getRechargeMark(int rechargeId);
private:
    CCDictionary *getRechargeDic(int recharId);
    string getRechargeAttribute(int recharId, const char *attributeName);
};
#endif /* defined(__threeKingdoms__RechargeRule__) */
