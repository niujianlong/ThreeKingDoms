//
//  SystemConfigRule.cpp
//  threeKingdoms
//
//  Created by .m on 13-12-30.
//
//

#include "SystemConfigRule.h"
#include "BaseDataManager.h"
#include "StringUtils.h"
#include "GameUtils.h"
#include "FightManager.h"
#include "UserData.h"

bool SystemConfigRule::init()
{
    return true;
}


int SystemConfigRule::getInitGold()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("initGold"));
}

int SystemConfigRule::getAttackCost()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("attackGoldCost"));
}

int SystemConfigRule::getMaxMagnification()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("maxMagnification"));
}

float SystemConfigRule::getDefaultEase()
{
    return INSTANCE(StringUtils)->stringToFloat(getSystemAttribute("defaultEase"));
}

float SystemConfigRule::getCRPWeights()
{
    return INSTANCE(StringUtils)->stringToFloat(getSystemAttribute("crpWeights"));
}

float SystemConfigRule::getDPWeights()
{
    return INSTANCE(StringUtils)->stringToFloat(getSystemAttribute("dpWeights"));
}

float SystemConfigRule::getCCPWeights()
{
    return INSTANCE(StringUtils)->stringToFloat(getSystemAttribute("ccpWeights"));
}

float SystemConfigRule::getACPWeights()
{
    return INSTANCE(StringUtils)->stringToFloat(getSystemAttribute("acpWeights"));
}

int SystemConfigRule::getDispatchTroopsInterval()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("dispatchTroopsInterval"));
}

int SystemConfigRule::getScoreConversionCycleMaxTime()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("scoreConversionCycleMaxTime"));
}

int SystemConfigRule::getScoreConversionCycleMinTime()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("scoreConversionCycleMinTime"));
}

int SystemConfigRule::getLoseScoreConversionCycleMaxTime()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("loseScoreConversionCycleMaxTime"));
}

int SystemConfigRule::getLoseScoreConversionCycleMinTime()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("loseScoreConversionCycleMinTime"));
}

int SystemConfigRule::getSendTroopsMaxTime()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("sendTroopsMaxTime"));
}

int SystemConfigRule::getSendTroopsMinTime()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("sendTroopsMinTime"));
}

int SystemConfigRule::getSentTroopsMaxNumber()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("sentTroopsManNumber"));
}

int SystemConfigRule::getSentTroopsMinNumber()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("sentTroopsMinNumber"));
}

int SystemConfigRule::getLoginReward(int dayNum)
{
    return INSTANCE(StringUtils)->getIntVectorFromString(getLoginAttribute(dayNum,"reward"),"_")[1];
}

int SystemConfigRule::getBossLotteryCost()
{
    return 20;
}

string SystemConfigRule::getFirstProbability()
{
    return getWheelAttribute("firstProbability");
}

string SystemConfigRule::getSecondProbability()
{
    return getWheelAttribute("secondProbability");
}

string SystemConfigRule::getThirdProbability()
{
    return getWheelAttribute("thirdProbability");
}

int SystemConfigRule::getWheelMultiple()
{
    string probability;
    if(INSTANCE(UserData)->getWheelTimes() == 0){
        probability = getSecondProbability();
    }
    if(!INSTANCE(FightManager)->getSomethingGood() && INSTANCE(FightManager)->getAnger() < 450){
        probability = getThirdProbability();
    }else{
        probability = getFirstProbability();
    }
    
    vector<float> probabilityV = INSTANCE(StringUtils)->getFloatVectorFromString(probability, "_");
    float multiple[] = {1.0f,2.0f,3.0f,4.0f,5.0f,6.0f};
    vector<vector<float> > p;
    for(int i=0;i<probabilityV.size();i++){
        vector<float> temp;
        temp.push_back(multiple[i]);
        temp.push_back(probabilityV[i]);
        p.push_back(temp);
    }
    int result = INSTANCE(GameUtils)->getRandomFromVector(p);
    return result;
}

int SystemConfigRule::getTreasureBowlGoldCost(int times)
{
    return INSTANCE(StringUtils)->stringToInt(getTreasureBowlAttibute(times,"goldCost"));
}

int SystemConfigRule::getTreasureBowlWinnings(int times)
{
    return INSTANCE(StringUtils)->stringToInt(getTreasureBowlAttibute(times,"winnings"));
}

int SystemConfigRule::getCurrentTreasureBowlGoldCost()
{
    return getTreasureBowlGoldCost(INSTANCE(UserData)->getFinishChapterTimes());
}

int SystemConfigRule::getCurrentTreasureBowlWinnings()
{
    return getTreasureBowlWinnings(INSTANCE(UserData)->getFinishChapterTimes());
}

bool SystemConfigRule::potIsFull()
{
    int currentPot = INSTANCE(UserData)->getPotGold();
    int max = getCurrentTreasureBowlGoldCost();
    
    if(currentPot >= max){
        return true;
    }
    return false;
}

int SystemConfigRule::getAngerMax()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("angerHighLimit"));
}

int SystemConfigRule::getOnlineReward()
{
    return INSTANCE(StringUtils)->getIntVectorFromString(getSystemAttribute("dailyOnlineReward"), "_")[1];
}

int SystemConfigRule::getOnlineRewardTime()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("dailyOnlineRewardTime"));
}

int SystemConfigRule::getOnlineRewardTimes()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("dailyOnlineRewardCount"));
}

int SystemConfigRule::getTaskCount()
{
    return INSTANCE(StringUtils)->stringToInt(getSystemAttribute("dailyTaskCount"));
}

int SystemConfigRule::getTaskTime(bool firstTime)
{
    vector<int> v = INSTANCE(StringUtils)->getIntVectorFromString(getSystemAttribute("dailyTaskTimeInterval"),"_");
    if(firstTime){
        return v[0];
    }
    return v[1];
}

CCDictionary* SystemConfigRule::getSystemDic()
{
    CCDictionary* dic = (CCDictionary *) INSTANCE(BaseDataManager)->getXml(SystemConfigXml)->objectForKey("1");
    return dic;
}

string SystemConfigRule::getSystemAttribute(const char *attributeName)
{
    return ((CCString *) getSystemDic()->objectForKey(attributeName))->getCString();
}

CCDictionary* SystemConfigRule::getLoginDic(int dayNum)
{
    CCDictionary* dic = (CCDictionary *) INSTANCE(BaseDataManager)->getXml(LoginRewardXml)->objectForKey(INSTANCE(StringUtils)->intToString(dayNum));
    return dic;
}

string SystemConfigRule::getLoginAttribute(int dayNum, const char *attributeName)
{
    return ((CCString *) getLoginDic(dayNum)->objectForKey(attributeName))->getCString();
}

CCDictionary* SystemConfigRule::getWheelDic()
{
    CCDictionary* dic = (CCDictionary *) INSTANCE(BaseDataManager)->getXml(WheelOfFortune)->objectForKey("1");
    return dic;
}

string SystemConfigRule::getWheelAttribute(const char *attributeName)
{
    return ((CCString *) getWheelDic()->objectForKey(attributeName))->getCString();
}

CCDictionary* SystemConfigRule::getTreasureBowlDic(int times)
{
    CCDictionary* dic = (CCDictionary *) INSTANCE(BaseDataManager)->getXml(TreasureBowl)->objectForKey(INSTANCE(StringUtils)->intToString(times));
    return dic;
}

string SystemConfigRule::getTreasureBowlAttibute(int times, const char *attributeName)
{
    return ((CCString *) getTreasureBowlDic(times)->objectForKey(attributeName))->getCString();
}
