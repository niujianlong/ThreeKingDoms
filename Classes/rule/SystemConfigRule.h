//
//  SystemConfigRule.h
//  threeKingdoms
//  Created by sma11case 13-12-30.
//
//

#ifndef __threeKingdoms__SystemConfigRule__
#define __threeKingdoms__SystemConfigRule__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class SystemConfigRule:public CCObject
{
public:
    CLASS_INSTANCE(SystemConfigRule);
    bool init();
    
    //初始化元宝
    int getInitGold();
    //普攻消耗
    int getAttackCost();
    //最大倍率
    int getMaxMagnification();
    //抽水率
    float getDefaultEase();
    //crp权重
    float getCRPWeights();
    //抽水率权重
    float getDPWeights();
    //ccp权重
    float getCCPWeights();
    //acp权重
    float getACPWeights();
    //出兵间隔时间
    int getDispatchTroopsInterval();
    
    
    //出分周期变换最小时间
    int getScoreConversionCycleMinTime();
    //出分周期变换最大时间
    int getScoreConversionCycleMaxTime();
    //吃分周期变换最小时间
    int getLoseScoreConversionCycleMinTime();
    //吃分周期变换最小时间
    int getLoseScoreConversionCycleMaxTime();
    
    //出兵间隔最小值
    int getSendTroopsMinTime();
    //出兵间隔最大值
    int getSendTroopsMaxTime();
    //出兵数量最小值
    int getSentTroopsMinNumber();
    //出兵数量最大值
    int getSentTroopsMaxNumber();
    
    int getLoginReward(int dayNum);
    
    //boss抽奖消耗
    int getBossLotteryCost();
    
    //正常转盘概率
    string getFirstProbability();
    //首次打boss转盘概率
    string getSecondProbability();
    //吃分周期怒气少于50%转盘概率
    string getThirdProbability();
    //获取转盘倍数
    int getWheelMultiple();
    
    //获取彩金
    int getTreasureBowlWinnings(int times);
    //获取元宝消耗
    int getTreasureBowlGoldCost(int times);
    
    //获取当前元宝消耗
    int getCurrentTreasureBowlGoldCost();
    //获取当前彩金
    int getCurrentTreasureBowlWinnings();
    //彩池是否已满
    bool potIsFull();
    
    //怒气上限
    int getAngerMax();
    
    //在线奖励
    int getOnlineReward();
    //在线奖励时间间隔
    int getOnlineRewardTime();
    //在线奖励每次次数
    int getOnlineRewardTimes();
    
    //每日任务次数
    int getTaskCount();
    //每日任务间隔
    int getTaskTime(bool firstTime);
private:
    CCDictionary *getSystemDic();
    string getSystemAttribute(const char *attributeName);
    
    CCDictionary *getLoginDic(int dayNum);
    string getLoginAttribute(int dayNum, const char* attributeName);
    
    CCDictionary *getWheelDic();
    string getWheelAttribute(const char *attributeName);
    
    CCDictionary *getTreasureBowlDic(int times);
    string getTreasureBowlAttibute(int times,const char* attributeName);
    
};

#endif /* defined(__threeKingdoms__SystemConfigRule__) */
