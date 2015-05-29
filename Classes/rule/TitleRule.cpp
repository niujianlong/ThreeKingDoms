//
//  TitleRule.cpp
//  threeKingdoms
//  Created by sma11case on 13-12-31.
//
//

#include "TitleRule.h"
#include "BaseDataManager.h"
#include "StringUtils.h"

bool TitleRule::init()
{
    mainDic = NULL;
    lastId = -1;
    return true;
}

string TitleRule::getTitleNameByIntegral(int integral)
{
    return getTitleNameByTitleLevel(getTitleLevelByIntegral(integral));
}

string TitleRule::getTitleNameByLevel(int level)
{
    return getTitleNameByTitleLevel(level);
}

int TitleRule::getTitleLevelByIntegral(int integral)
{
    if(mainDic == NULL){
        mainDic = INSTANCE(BaseDataManager)->getXml(TitleXml);
    }
    CCArray *keyArray = mainDic->allKeys();
    int integralTemp = 0;
    int titleLevelTemp = 0;
    for(int i=0;i<mainDic->count();i++){
        string key = ((CCString *)keyArray->objectAtIndex(i))->getCString();
        CCDictionary *subDic = (CCDictionary *) mainDic->objectForKey(key);
        integralTemp += INSTANCE(StringUtils)->stringToInt(((CCString *) subDic->objectForKey("integral"))->getCString());
        
        if(integral >= integralTemp){
            titleLevelTemp = INSTANCE(StringUtils)->stringToInt(key);
        }else{
            break;
        }
    }
    return titleLevelTemp;
}

string TitleRule::getTitleNameByTitleLevel(int titleLevel)
{
    return INSTANCE(BaseDataManager)->getLan(getTitleAttribute(titleLevel,"titleName"));
}

int TitleRule::getTitleIntegralByTitleLevel(int titleLevel)
{
    if(titleLevel > 16){
        return 1;
    }
    return INSTANCE(StringUtils)->stringToInt(getTitleAttribute(titleLevel,"integral"));
}

int TitleRule::getTitleUpgradeIntegral(int titleLevel, int integral)
{
    int totleIntegral = 0;
    for(int i=titleLevel;i>0;i--){
        totleIntegral += getTitleIntegralByTitleLevel(i);
    }
    integral -= totleIntegral;
    return integral;
}

int TitleRule::getTitleUpgradeReward(int titleLevel)
{
    return INSTANCE(StringUtils)->getIntVectorFromString(getTitleAttribute(titleLevel,"titleReward"),"_")[1];
}

int TitleRule::getEvenStrokes(int titleLevel)
{
    return INSTANCE(StringUtils)->stringToInt(getTitleAttribute(titleLevel,"evenStrokes"));
}

float TitleRule::getTitleAttackAddition(int titleLevel)
{
    return INSTANCE(StringUtils)->stringToFloat(getTitleAttribute(titleLevel,"addAttackSpeedPercentage"));
}

float TitleRule::getTitleSpeedAddition(int titleLevel)
{
    return INSTANCE(StringUtils)->stringToFloat(getTitleAttribute(titleLevel,"addMoveSpeedPercentage"));
}

CCDictionary* TitleRule::getTitleDic(int titleId)
{
    if(mainDic == NULL){
        mainDic = INSTANCE(BaseDataManager)->getXml(TitleXml);
    }
    if(lastId != titleId){
        lastId = titleId;
        lastSubDic = (CCDictionary *) mainDic->objectForKey(CCString::createWithFormat("%d",titleId)->getCString());
    }
    return lastSubDic;
}

string TitleRule::getTitleAttribute(int titleId, const char *attributeName)
{
    return ((CCString *) getTitleDic(titleId)->objectForKey(attributeName))->getCString();
}