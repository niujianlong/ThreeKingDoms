//
//  RechargeRule.cpp
//  threeKingdoms
//  Created by sma11case 14-3-6.
//
//

#include "RechargeRule.h"
#include "BaseDataManager.h"
#include "StringUtils.h"

bool RechargeRule::init()
{
    return true;
}

int RechargeRule::getRechargeGoldCount(int rechargeId)
{
    return INSTANCE(StringUtils)->stringToInt(getRechargeAttribute(rechargeId, "gold"));
}

int RechargeRule::getRechargePrice(int rechargeId)
{
    return INSTANCE(StringUtils)->stringToInt(getRechargeAttribute(rechargeId, "price"));
}

string RechargeRule::getRechargeMark(int rechargeId)
{
    return getRechargeAttribute(rechargeId, "markId");
}

vector<int> RechargeRule::getRechargeIdByType(int type)
{
    vector<int> result;
    CCDictionary* mainDic = INSTANCE(BaseDataManager)->getXml(RechargeXml);
    CCArray *keyArray = mainDic->allKeys();
    for(int i=0;i<keyArray->count();i++){
        string key = ((CCString *)keyArray->objectAtIndex(i))->getCString();
        CCDictionary *subDic = (CCDictionary *)mainDic->objectForKey(key.c_str());
        int _type = INSTANCE(StringUtils)->stringToInt(((CCString *)subDic->objectForKey("type"))->getCString());
        if(_type == type){
            result.push_back(INSTANCE(StringUtils)->stringToInt(key));
        }
    }
    return result;
}

CCDictionary* RechargeRule::getRechargeDic(int rechargeId)
{
    CCDictionary* mainDic = INSTANCE(BaseDataManager)->getXml(RechargeXml);
    
    CCDictionary *subDic = (CCDictionary *) mainDic->objectForKey(CCString::createWithFormat("%d",rechargeId)->getCString());
    
    return subDic;
}

string RechargeRule::getRechargeAttribute(int rechargeId, const char *attributeName)
{
    return ((CCString *) getRechargeDic(rechargeId)->objectForKey(attributeName))->getCString();
}