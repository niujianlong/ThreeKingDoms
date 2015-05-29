//
//  NPCRule.h
//  threeKingdoms
//  Created by sma11case on 13-12-25.
//
//

#ifndef __threeKingdoms__NPCRule__
#define __threeKingdoms__NPCRule__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "RoleRule.h"

using namespace std;
USING_NS_CC;

class NPCRule:public CCObject
{
public:
    CLASS_INSTANCE(NPCRule);
    bool init();
    
    //获取npc图片名
    string getNpcFrameNameByNpcId(int npcId,RoleStatus status,bool containPng = false);
    //获取npc站立第一帧图片名
    string getNpcFirstFrameNameByNpcId(int npdId,RoleStatus status);
    
    //获取npc血量
    int getNpcHp(int npcId);
    //获取npc锚点
    CCPoint getNpcAnchorPoint(int npcId);
    //获取npc模型id
    int getNpcModelId(int npcId);
    //获取npc名字
    string getNpcName(int npcId);
    //获取npc类型
    int getNpcType(int npcId);
    //获取npc积分
    int getNpcIntegral(int npcId);
    //获取npc技能id
    int getNpcSkillId(int npcId);
    //获取npc速度
    int getNpcSpeed(int npcId);
    //获取npc元宝下限
    int getNpcMoneyMin(int npcId);
    //获取npc元宝上限
    int getNpcMoneyMax(int npcId);
    //获取npc元宝
    int getNpcMoney(int npcId);
    //获取npc携带怒气
    int getNpcAnger(int npcId);
    //获取npc闪避
    float getNpcDodge(int npcId);
    //获取npc图片资源路径
    string getNpcImgPath(int npcId);
    //npc描述
    string getNpcDesc(int npdId);
    
    //获取npc受击范围
    CCSize getNpcHurtSize(int npcId);
    //获取npc攻击范围
    CCSize getNpcAttackSize(int npcId);
    
    //攻击类型
    int getNpcAttackType(int npcId);
    //攻击概率
    float getNpcAttackProbability(int npcId);
    //站立概率
    float getNpcStandProbability(int npcId);
    //加速概率
    float getNpcSpeedUpProbability(int npdId);
    //加速概率
    float getNpcSpeedDownProbability(int npcId);
    
    //攻击惩罚
    int getNpcAttackPenalty(int npcId);
    
private:
    CCDictionary *getNpcDic(int npcId);
    string getNpcAttribute(int npcId,const char *attributeName);
    
    CCDictionary *mainDic;
    
    int lastId;
    CCDictionary *lastSubDic;
};

#endif /* defined(__threeKingdoms__NPCRule__) */
