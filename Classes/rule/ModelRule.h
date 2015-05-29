//
//  ModelRule.h
//  threeKingdoms
//  Created by sma11case on 13-12-26.
//
//

#ifndef __threeKingdoms__ModelRule__
#define __threeKingdoms__ModelRule__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "RoleRule.h"

using namespace std;
USING_NS_CC;

class ModelRule:public CCObject
{
public:
    CLASS_INSTANCE(ModelRule);
    bool init();
    
    //获取模型图片名
    string getModelFrameNameByModelId(int modelId,RoleStatus status,bool containPng = false);
    //获取模型站立第一帧图片名
    string getModelFirstFrameNameByModelId(int modelId,RoleStatus status);
    
    //获取模型路径
    string getModelPath(int modelId);
    //获取模型锚点
    CCPoint getModelAnchorPoint(int modelId);
    //获取模型技能特效锚点
    CCPoint getModelSkillEffectAnchorPoint(int modelId);
    //获取模型普攻特效锚点
    CCPoint getModelAttackEffectAnchorPoint(int modelId);
    //获取模型受击范围
    CCSize getModelHurtSize(int modelId);
    //获取模型攻击范围
    CCSize getModelAttackSize(int modelId);

    //获取技能被击特效图片名
    string getSkillHitFrameName(int skillId,bool containPng = false);
    //获取技能被击特效锚点
    CCPoint getSkillHitAnchorPoint(int skillId);
    
private:
    CCDictionary *getModelDic(int modelId);
    string getModelAttribute(int modelId,const char *attributeName);
    CCDictionary *mainDic;
    
    int lastId;
    CCDictionary *lastSubDic;
};

#endif /* defined(__threeKingdoms__ModelRule__) */
