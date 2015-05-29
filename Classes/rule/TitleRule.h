//
//  TitleRule.h
//  threeKingdoms
//  Created by sma11case 13-12-31.
//
//

#ifndef __threeKingdoms__TitleRule__
#define __threeKingdoms__TitleRule__

#include <iostream>
#include "cocos2d.h"
#include "GameUtils.h"

using namespace std;
USING_NS_CC;

class TitleRule:public CCObject
{
public:
    CLASS_INSTANCE(TitleRule);
    bool init();
    
    //获取头衔名称by积分
    string getTitleNameByIntegral(int integral);
    //获取头衔名称by等级
    string getTitleNameByLevel(int level);
    //获取等级idby积分
    int getTitleLevelByIntegral(int integral);
    //获取头衔名称by头衔等级
    string getTitleNameByTitleLevel(int titleLevel);
    //获取头衔积分by头衔等级
    int getTitleIntegralByTitleLevel(int titleLevel);
    //获取头衔升级积分
    int getTitleUpgradeIntegral(int titleLevel,int integral);
    
    //升级头衔获得奖励积分
    int getTitleUpgradeReward(int titleLevel);
    
    //获取最大连招次数
    int getEvenStrokes(int titleLevel);
    
    float getTitleAttackAddition(int titleLevel);
    float getTitleSpeedAddition(int titleLevel);
private:
    CCDictionary *getTitleDic(int titleLevel);
    string getTitleAttribute(int titleLevel, const char *attributeName);
    
    CCDictionary *mainDic;
    int lastId;
    CCDictionary *lastSubDic;
};

#endif /* defined(__threeKingdoms__TitleRule__) */
