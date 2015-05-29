//
//  SceneRule.cpp
//  threeKingdoms
//  Created by sma11case on 13-12-27.
//
//

#include "SceneRule.h"
#include "BaseDataManager.h"
#include "StringUtils.h"

bool SceneRule::init()
{
    mainDic = NULL;
    lastId = -1;
    return true;
}

vector<int> SceneRule::getAllSceneId()
{
    if(mainDic == NULL){
        mainDic = INSTANCE(BaseDataManager)->getXml(ScenesXml);
    }
    vector<int> idVector;
    CCArray *array = mainDic->allKeys();
    for(int i=0;i<array->count();i++){
        idVector.push_back(INSTANCE(StringUtils)->stringToInt(((CCString*) array->objectAtIndex(i))->getCString()));
    }
    return idVector;
}

string SceneRule::getSceneName(int sceneId)
{
    return INSTANCE(BaseDataManager)->getLan(getSceneAttribute(sceneId,"name"));
}

string SceneRule::getSceneDesc(int sceneId)
{
    return getSceneAttribute(sceneId,"description");
}

int SceneRule::getSceneImgId(int sceneId)
{
    return INSTANCE(StringUtils)->stringToInt(getSceneAttribute(sceneId,"image"));
}

int SceneRule::getSceneNeedLevel(int sceneId)
{
    return INSTANCE(StringUtils)->stringToInt(getSceneAttribute(sceneId,"level"));
}

int SceneRule::getSceneNeedVip(int sceneId)
{
    return INSTANCE(StringUtils)->stringToInt(getSceneAttribute(sceneId,"viplevel"));
}

string SceneRule::getSceneFormation(int sceneId)
{
    return getSceneAttribute(sceneId,"baseFormationIds");
}

vector<vector<int> > SceneRule::getSceneFormationVector(int sceneId)
{
    string temp = getSceneFormation(sceneId);
    vector<vector<int> > result = INSTANCE(StringUtils)->getIntVectorFromString(temp, "|","_");
    return result;
}

int SceneRule::getSceneBossCount(int sceneId)
{
    return INSTANCE(StringUtils)->stringToInt(getSceneAttribute(sceneId, "ariseBossCount"));
}

vector<int> SceneRule::getSceneBossId(int sceneId)
{
    return INSTANCE(StringUtils)->getIntVectorFromString(getSceneAttribute(sceneId,"bossIds"), "_");
}

vector<int> SceneRule::getSkillNpcId(int sceneId)
{
    return INSTANCE(StringUtils)->getIntVectorFromString(getSceneAttribute(sceneId,"skillSoldierIds"), "_");
}

vector<int> SceneRule::getNpcId(int sceneId)
{
    return INSTANCE(StringUtils)->getIntVectorFromString(getSceneAttribute(sceneId,"soldierIds"), "_");
}

vector<int> SceneRule::getAllNpcId(int sceneId)
{
    vector<int> result;
    vector<int> v1 = getSceneBossId(sceneId);
    vector<int> v2 = getSkillNpcId(sceneId);
    vector<int> v3 = getNpcId(sceneId);
    result.insert(result.end(), v1.begin(), v1.end());
    result.insert(result.end(), v2.begin(), v2.end());
    result.insert(result.end(), v3.begin(), v3.end());
    return result;
}

vector<float> SceneRule::getNpcProbabilitys(int sceneId)
{
    return INSTANCE(StringUtils)->getFloatVectorFromString(getSceneAttribute(sceneId, "soldierProbabilitys"), "_");
}

float SceneRule::getSkillNpcProbability(int sceneId)
{
    return INSTANCE(StringUtils)->stringToFloat(getSceneAttribute(sceneId, "skillSoldierProbability"));
}

vector<int> SceneRule::getScoreVector(int sceneId,int type)
{
    if(type == 1){
        return INSTANCE(StringUtils)->getIntVectorFromString(getSceneAttribute(sceneId ,"scoreInterregional"),"_");
    }else if(type == 2){
        return INSTANCE(StringUtils)->getIntVectorFromString(getSceneAttribute(sceneId ,"scoreInterregional2"),"_");
    }else {
        return INSTANCE(StringUtils)->getIntVectorFromString(getSceneAttribute(sceneId ,"scoreInterregional3"),"_");
    }
    
}

float SceneRule::getScoreCoefficient(int sceneId)
{
    return INSTANCE(StringUtils)->stringToFloat(getSceneAttribute(sceneId ,"defaultMaxWinScoreCoefficient"));
}

float SceneRule::getCycleScoreCoefficientAddition(int sceneId)
{
    return INSTANCE(StringUtils)->stringToFloat(getSceneAttribute(sceneId ,"scoreCycleCoefficientAddition"));
}

float SceneRule::getAttackScoreCoefficientAddition(int sceneId)
{
    return INSTANCE(StringUtils)->stringToFloat(getSceneAttribute(sceneId ,"attackCumulativeCoefficientAddition"));
}

int SceneRule::getSceneMagnification(int sceneId)
{
    return INSTANCE(StringUtils)->stringToInt(getSceneAttribute(sceneId ,"magnification"));
}

float SceneRule::getSceneScoreHitRate(int sceneId)
{
    return INSTANCE(StringUtils)->stringToFloat(getSceneAttribute(sceneId ,"scoreCycleHitRate"));
}

float SceneRule::getSceneLoseHitRate(int sceneId)
{
    return INSTANCE(StringUtils)->stringToFloat(getSceneAttribute(sceneId ,"loseScoreCycleHitRate"));
}

float SceneRule::getTroopsHitRate(int sceneId)
{
    return INSTANCE(StringUtils)->stringToFloat(getSceneAttribute(sceneId ,"scoreTroopsHitRate"));
}

CCDictionary* SceneRule::getSceneDic(int sceneId)
{
    if(mainDic == NULL){
        mainDic = INSTANCE(BaseDataManager)->getXml(ScenesXml);
    }
    
    if(lastId != sceneId){
        lastId = sceneId;
        lastSubDic = (CCDictionary *) mainDic->objectForKey(CCString::createWithFormat("%d",sceneId)->getCString());
    }
    return lastSubDic;
}

string SceneRule::getSceneAttribute(int sceneId, const char *attributeName)
{
    return ((CCString *) getSceneDic(sceneId)->objectForKey(attributeName))->getCString();
}