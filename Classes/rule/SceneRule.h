//
//  SceneRule.h
//  threeKingdoms
//  Created by sma11case 13-12-27.
//
//

#ifndef __threeKingdoms__SceneRule__
#define __threeKingdoms__SceneRule__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class SceneRule:public CCObject
{
public:
    CLASS_INSTANCE(SceneRule);
    bool init();
    
    //获取所有场景id
    vector<int> getAllSceneId();
    
    //获取场景名
    string getSceneName(int sceneId);
    //获取场景描述
    string getSceneDesc(int sceneId);
    //获取场景图片id
    int getSceneImgId(int sceneId);
    //获取场景所需等级
    int getSceneNeedLevel(int sceneId);
    //获取场景所需vip
    int getSceneNeedVip(int sceneId);
    //获取场景阵型Id
    string getSceneFormation(int sceneId);
    
    //获取boss出现数量
    int getSceneBossCount(int sceneId);
    //获取boss id
    vector<int> getSceneBossId(int sceneId);
    //获取技能兵id
    vector<int> getSkillNpcId(int sceneId);
    //获取士兵id
    vector<int> getNpcId(int sceneId);
    //获取所有npc id
    vector<int> getAllNpcId(int sceneId);
    
    //获取士兵概率
    vector<float> getNpcProbabilitys(int sceneId);
    
    //获取技能兵概率
    float getSkillNpcProbability(int sceneId);
    
    //获取得分区间
    vector<int> getScoreVector(int sceneId,int type);
    //获取影响系数
    float getScoreCoefficient(int sceneId);
    //获取得分周期影响系数加成
    float getCycleScoreCoefficientAddition(int sceneId);
    //获取攻击累计加成影响系数
    float getAttackScoreCoefficientAddition(int sceneId);
    
    //获取场景阵型
    vector<vector<int> > getSceneFormationVector(int sceneId);
    
    //场景倍率
    int getSceneMagnification(int sceneId);
    //出分周期命中率
    float getSceneScoreHitRate(int sceneId);
    //吃分周期命中率
    float getSceneLoseHitRate(int sceneId);
    //得分部队命中率
    float getTroopsHitRate(int sceneId);
private:
    CCDictionary *getSceneDic(int sceneId);
    string getSceneAttribute(int sceneId,const char *attributeName);
    
    CCDictionary *mainDic;
    int lastId;
    CCDictionary *lastSubDic;
};

#endif /* defined(__threeKingdoms__SceneRule__) */
