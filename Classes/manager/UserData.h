//
//  UserData.h
//  threeKingdoms
//  Created by sma11case on 14-1-4.
//
//

#ifndef __threeKingdoms__UserData__
#define __threeKingdoms__UserData__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class UserData:public CCObject
{
public:
    CLASS_INSTANCE(UserData);
    bool init();
    
    void setCurrentRoleId(int roleId);
    int getCurrentRoleId();
    
    void setCurrentSceneId(int sceneId);
    int getCurrentSceneId();
    
    void setCurrentMoney(int money);
    void addCurrentMoney(int money);
    void costCurrentMoney(int money);
    int getCurrentMoney();
    
    void setCurrentIntegral(int integral);
    int getCurrentIntegral();
    
    void setKillBossNum(int num);
    int getKillBossNum();
    
    void setTotleCost(int cost);
    int getTotleCost();
    
    void setTotleGain(int gain);
    int getTotleGain();
    
    void setTitleLevel(int titleLevel);
    int getTitleLevel();
    
    void setCurrentUpgradeIntegral(int upgradeIntegral);
    int getCurrentUpgradeIntegral();
    
    void setLastReceiveLoginRewardTime(int64_t time);
    int64_t getLastReceiveLoginRewardTime();
    
    void setLastReceiveOnlineRewardTime(int64_t time);
    int64_t getLastReceiveOnlineRewardTime();
    
    void setContinuousDay(int dayNum);
    int getContinuousDay();
    
    void setSkillNum(int skillNum);
    int getSkillNum();
    
    void setVipLevel(int vipLevel);
    int getVipLevel();
    
    void setRoles(string roles);
    string getRoles();
    void addRole(int roleId);
    
    void setChapterStatus(int chapterId,int bossId);
    int getChapterStatus(int chapterId);
    
    void setWheelTimes(int times);
    void addWheelTimes(int times);
    int getWheelTimes();
    
    void setFinishChapterTimes(int times);
    void addFinishChapterTimes(int times);
    int getFinishChapterTimes();
    
    void setPotGold(int gold);
    void addPotGold(int gold);
    int getPotGold();
    int getPotWinning();
    
    void setReceiveOnlineRewardTimes(int times);
    void addReceiveOnlineRewardTimes(int times);
    int getReceiveOnlineRewardTimes();
    
    void setTaskCount(int count);
    void addTaskCount(int count);
    int getTaskCount();
    
    void setReceiveTaskTime(int64_t time);
    int64_t getReceiveTaskTime();
    
    void setAnger(int anger);
    int getAnger();
    
    void addLoginCount(int count);
    int getLoginCount();
    
    void reloadData();
    
    void setChargeAmount(int amount);
    int getChargeAmount();
    
    void setProductIds(vector<string> ids);
    vector<string> getProductIds();
    
    bool isPPLogin;
private:
    //当前role id
    int currentRoleId;
    //当前场景id
    int currentSceneId;
    //当前元宝
    int currentMoney;
    //当前积分
    int currentIntegral;
    //当前头衔等级
    int currentTitleLevel;
    //当前升级积分
    int currentUpgradeIntegral;
    //当前连续登陆天数
    int currentContinuousDay;
    //击杀boss数量
    int killBossNum;
    //元宝总消耗(首次游戏时累计)
    int totleCost;
    //元宝总获取(首次游戏时累计)
    int totleGain;
    //技能释放次数
    int skillNum;
    
    //上次领取登录奖励时间
    int64_t lastReceiveLoginRewardTime;
    //上次领取在线奖励
    int64_t lastReceiveOnlineRewardTime;
    //vip等级
    int vipLevel;
    //拥有的角色id
    string roles;
    //关卡状态
    string chapterStatus;
    //转盘次数
    int wheelTimes;
    //通关次数
    int finishChapterTimes;
    //当前彩池奖金
    int currentPotGold;
    
    //当前领取在线奖励次数
    int receiveOnlineRewardTimes;
    
    //每日任务次数
    int taskCount;
    
    int anger;
    
    int64_t receiveTaskTime;
    
    int loginCount;
    
    int chargeAmount;
    
    vector<string> productIds;
};

#endif /* defined(__threeKingdoms__UserData__) */
