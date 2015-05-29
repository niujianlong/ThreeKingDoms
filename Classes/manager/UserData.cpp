//
//  UserData.cpp
//  threeKingdoms
//  Created by sma11case on 14-1-4.
//
//

#include "UserData.h"
#include "SQLManager.h"
#include "TitleRule.h"
#include "StringUtils.h"
#include "SystemConfigRule.h"
#include "FightManager.h"
#include "GuideManager.h"

bool UserData::init()
{
    reloadData();
    
    isPPLogin = false;
    
    return true;
}

void UserData::setCurrentIntegral(int integral)
{
    currentIntegral = integral;
    
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_Integral, integral);
    }
    
    
    int currentTitleLevel = INSTANCE(TitleRule)->getTitleLevelByIntegral(currentIntegral);
    setTitleLevel(currentTitleLevel);
    
    int currentUpgradeIntegral = INSTANCE(TitleRule)->getTitleUpgradeIntegral(currentTitleLevel, currentIntegral);
    setCurrentUpgradeIntegral(currentUpgradeIntegral);
}

void UserData::setCurrentMoney(int money)
{
    currentMoney = money;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_Gold, money);
    }
}

void UserData::addCurrentMoney(int money)
{
    currentMoney += money;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_Gold, currentMoney);
    }
    
}

void UserData::costCurrentMoney(int money)
{
    currentMoney-=money;
    if(currentMoney < 0){
        currentMoney = 0;
    }
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_Gold, currentMoney);
        addPotGold(money);
    }
}

void UserData::setCurrentRoleId(int roleId)
{
    currentRoleId = roleId;
}

void UserData::setCurrentSceneId(int sceneId)
{
    currentSceneId = sceneId;
}

void UserData::setKillBossNum(int num)
{
    killBossNum = num;
}

void UserData::setTotleCost(int cost)
{
    totleCost = cost;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_TotleCost, totleCost);
    }
}

void UserData::setTotleGain(int gain)
{
    totleGain = gain;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_TotleGain, totleGain);
    }
}

void UserData::setTitleLevel(int titleLevel)
{
    currentTitleLevel = titleLevel;
    
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_TitleLevel, currentTitleLevel);
    }
}

void UserData::setCurrentUpgradeIntegral(int upgradeIntegral)
{
    currentUpgradeIntegral = upgradeIntegral;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_UpgradeIntegral, currentUpgradeIntegral);
    }
}

void UserData::setLastReceiveLoginRewardTime(int64_t time)
{
    lastReceiveLoginRewardTime = time;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_LastReceiveLoginRewardTime, lastReceiveLoginRewardTime);
    }
}

void UserData::setLastReceiveOnlineRewardTime(int64_t time)
{
    lastReceiveOnlineRewardTime = time;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_LastReceiveOnlineRewardTime, time);
    }
}

void UserData::setContinuousDay(int dayNum)
{
    currentContinuousDay = dayNum;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_ContinuousLoginDay, currentContinuousDay);
    }
}

void UserData::setSkillNum(int skillNum)
{
    this->skillNum = skillNum;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_SkillNum, skillNum);
    }
}

void UserData::setVipLevel(int vipLevel)
{
    this->vipLevel = vipLevel;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_vip, vipLevel);
    }
}

void UserData::setRoles(string roles)
{
    this->roles = roles;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_Roles, roles.c_str());
    }
}

void UserData::addRole(int roleId)
{
    if(roles.find(INSTANCE(StringUtils)->intToString(roleId)) == string::npos){
        roles.append("_"+INSTANCE(StringUtils)->intToString(roleId));
        setRoles(roles);
    }
    
}

int UserData::getCurrentIntegral()
{
    return currentIntegral;
}

int UserData::getCurrentMoney()
{
    return currentMoney;
}

int UserData::getCurrentRoleId()
{
    return currentRoleId;
}

int UserData::getCurrentSceneId()
{
    return currentSceneId;
}

int UserData::getKillBossNum()
{
    return killBossNum;
}

int UserData::getTotleCost()
{
    return totleCost;
}

int UserData::getTotleGain()
{
    return totleGain;
}

int UserData::getTitleLevel()
{
    return currentTitleLevel;
}

int UserData::getCurrentUpgradeIntegral()
{
    return currentUpgradeIntegral;
}

int64_t UserData::getLastReceiveLoginRewardTime()
{
    return lastReceiveLoginRewardTime;
}

int64_t UserData::getLastReceiveOnlineRewardTime()
{
    return lastReceiveOnlineRewardTime;
}

int UserData::getContinuousDay()
{
    return currentContinuousDay;
}

int UserData::getSkillNum()
{
    return skillNum;
}

int UserData::getVipLevel()
{
    return vipLevel;
}

string UserData::getRoles()
{
    return roles;
}

void UserData::setChapterStatus(int chapterId, int bossId)
{
    map<int, vector<int> > tempM = INSTANCE(StringUtils)->getIntMapFromString(chapterStatus, "|", "_");
    map<int, vector<int> >::iterator it = tempM.find(chapterId);
    if(it != tempM.end()){
        it->second[0] = bossId;
    }else{
        vector<int> t;
        t.push_back(bossId);
        tempM[chapterId] = t;
    }
    
    chapterStatus = INSTANCE(StringUtils)->intMapToString(tempM);
    
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_ChapterStatus, chapterStatus.c_str());
    }
}

int UserData::getChapterStatus(int chapterId)
{
    map<int, vector<int> > tempM = INSTANCE(StringUtils)->getIntMapFromString(chapterStatus, "|", "_");
    map<int, vector<int> >::iterator it = tempM.find(chapterId);
    if(it != tempM.end()){
        return it->second[0];
    }
    return 0;
}

void UserData::setWheelTimes(int times)
{
    wheelTimes = times;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_WheelTimes, times);
    }
}

void UserData::addWheelTimes(int times)
{
    wheelTimes+=times;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_WheelTimes, wheelTimes);
    }
}

int UserData::getWheelTimes()
{
    return wheelTimes;
}


void UserData::setFinishChapterTimes(int times)
{
    finishChapterTimes = times;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_FinishChapterTimes, times);
    }
}

void UserData::addFinishChapterTimes(int times)
{
    finishChapterTimes+=times;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_FinishChapterTimes, finishChapterTimes);
    }
}

int UserData::getFinishChapterTimes()
{
    return finishChapterTimes;
}


void UserData::setPotGold(int gold)
{
    if(gold > INSTANCE(SystemConfigRule)->getCurrentTreasureBowlGoldCost()){
        gold = INSTANCE(SystemConfigRule)->getCurrentTreasureBowlGoldCost();
    }
    currentPotGold = gold;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_PotGold, gold);
    }
}

void UserData::addPotGold(int gold)
{
    currentPotGold+=gold;
    if(currentPotGold > INSTANCE(SystemConfigRule)->getCurrentTreasureBowlGoldCost()){
        currentPotGold = INSTANCE(SystemConfigRule)->getCurrentTreasureBowlGoldCost();
    }
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_PotGold, currentPotGold);
    }
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdatePot);
}

int UserData::getPotGold()
{
    return currentPotGold;
}

int UserData::getPotWinning()
{
    return currentPotGold * (float(INSTANCE(SystemConfigRule)->getCurrentTreasureBowlWinnings()) / float(INSTANCE(SystemConfigRule)->getCurrentTreasureBowlGoldCost()));
}


void UserData::setReceiveOnlineRewardTimes(int times)
{
    receiveOnlineRewardTimes = times;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_ReceiveOnlineRewardTimes, times);
    }
}

void UserData::addReceiveOnlineRewardTimes(int times)
{
    receiveOnlineRewardTimes += times;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_ReceiveOnlineRewardTimes, receiveOnlineRewardTimes);
    }
}

int UserData::getReceiveOnlineRewardTimes()
{
    return receiveOnlineRewardTimes;
}

void UserData::setTaskCount(int count)
{
    taskCount = count;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_taskCount, count);
    }
}

void UserData::addTaskCount(int count)
{
    taskCount += count;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_taskCount, taskCount);
    }
}

int UserData::getTaskCount()
{
    return taskCount;
}

void UserData::setReceiveTaskTime(int64_t time)
{
    receiveTaskTime = time;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_receiveTaskTime, time);
    }
}

int64_t UserData::getReceiveTaskTime()
{
    return receiveTaskTime;
}

void UserData::setAnger(int anger)
{
    if(anger < 0){
        anger = 0;
    }else if(anger > 100){
        anger = 100;
    }
    this->anger = anger;
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(SQLManager)->save(FieldName_anger, anger);
    }
    
}

int UserData::getAnger()
{
    return anger;
}

void UserData::addLoginCount(int count)
{
    loginCount += count;
    INSTANCE(SQLManager)->save(FieldName_loginCount, loginCount);
}

int UserData::getLoginCount()
{
    return loginCount;
}

void UserData::reloadData()
{
    currentMoney = INSTANCE(SQLManager)->getValueInt(FieldName_Gold);
    currentIntegral = INSTANCE(SQLManager)->getValueInt(FieldName_Integral);
    killBossNum = INSTANCE(SQLManager)->getValueInt(FieldName_KillBossNum);
    totleCost = INSTANCE(SQLManager)->getValueInt(FieldName_TotleCost);
    totleGain = INSTANCE(SQLManager)->getValueInt(FieldName_TotleGain);
    currentTitleLevel = INSTANCE(SQLManager)->getValueInt(FieldName_TitleLevel);
    currentUpgradeIntegral = INSTANCE(SQLManager)->getValueInt(FieldName_UpgradeIntegral);
    lastReceiveLoginRewardTime = INSTANCE(StringUtils)->stringToInt64(INSTANCE(SQLManager)->getValue(FieldName_LastReceiveLoginRewardTime));
    lastReceiveOnlineRewardTime = INSTANCE(StringUtils)->stringToInt64(INSTANCE(SQLManager)->getValue(FieldName_LastReceiveOnlineRewardTime));
    currentContinuousDay = INSTANCE(SQLManager)->getValueInt(FieldName_ContinuousLoginDay);
    skillNum = INSTANCE(SQLManager)->getValueInt(FieldName_SkillNum);
    vipLevel = INSTANCE(SQLManager)->getValueInt(FieldName_vip);
    roles = INSTANCE(SQLManager)->getValue(FieldName_Roles);
    chapterStatus = INSTANCE(SQLManager)->getValue(FieldName_ChapterStatus);
    if(chapterStatus == "0"){
        chapterStatus = "";
    }
    wheelTimes = INSTANCE(SQLManager)->getValueInt(FieldName_WheelTimes);
    finishChapterTimes = INSTANCE(SQLManager)->getValueInt(FieldName_FinishChapterTimes);
    currentPotGold = INSTANCE(SQLManager)->getValueInt(FieldName_PotGold);
    receiveOnlineRewardTimes = INSTANCE(SQLManager)->getValueInt(FieldName_ReceiveOnlineRewardTimes);
    taskCount = INSTANCE(SQLManager)->getValueInt(FieldName_taskCount);
    receiveTaskTime = INSTANCE(StringUtils)->stringToInt64(INSTANCE(SQLManager)->getValue(FieldName_receiveTaskTime));
    anger = INSTANCE(SQLManager)->getValueInt(FieldName_anger);
    loginCount = INSTANCE(SQLManager)->getValueInt(FieldName_loginCount);
}

void UserData::setChargeAmount(int amount)
{
    chargeAmount = amount;
}

int UserData::getChargeAmount()
{
    return chargeAmount;
}

void UserData::setProductIds(vector<string> ids)
{
    productIds = ids;
}

vector<string> UserData::getProductIds()
{
    return productIds;
}