//
//  ModelRule.cpp
//  threeKingdoms
//  Created by sma11case on 13-12-26.
//
//

#include "ModelRule.h"
#include "BaseDataManager.h"
#include "StringUtils.h"
#include "SkillRule.h"

bool ModelRule::init()
{
    lastId = -1;
    mainDic = NULL;
    return true;
}

string ModelRule::getModelFrameNameByModelId(int modelId,RoleStatus status,bool containPng)
{
    CCString *result;
    switch (status) {
        case RoleStatusStand:
            result = CCString::createWithFormat("%d_stand",modelId);
            break;
        case RoleStatusWalk:
            result = CCString::createWithFormat("%d_walk",modelId);
            break;
        case RoleStatusRun:
            result = CCString::createWithFormat("%d_run",modelId);
            break;
        case RoleStatusAttack:
            result = CCString::createWithFormat("%d_attack",modelId);
            break;
        case RoleStatusAttack_1:
            result = CCString::createWithFormat("%d_attack_1",modelId);
            break;
        case RoleStatusAttack_2:
            result = CCString::createWithFormat("%d_attack_2",modelId);
            break;
        case RoleStatusAttack_3:
            result = CCString::createWithFormat("%d_attack_3",modelId);
            break;
        case RoleStatusAttack_4:
            result = CCString::createWithFormat("%d_attack_4",modelId);
            break;
        case RoleStatusAttack_5:
            result = CCString::createWithFormat("%d_attack_5",modelId);
            break;
        case RoleStatusHurt:
            result = CCString::createWithFormat("%d_hurt",modelId);
            break;
        case RoleStatusDie:
            result = CCString::createWithFormat("%d_die",modelId);
            break;
        case RoleStatusSkill:
            result = CCString::createWithFormat("%d_skill",modelId);
            break;
        case RoleStatusAttackEffect:
            result = CCString::createWithFormat("%d_attack_effect",modelId);
            break;
        case RoleStatusSkillEffect:
            result = CCString::createWithFormat("%d_skill_effect",modelId);
            break;
        default:
            break;
    }
    if(containPng){
        return string(result->getCString()) + ".png";
    }else{
        return result->getCString();
    }
}

string ModelRule::getModelFirstFrameNameByModelId(int modelId,RoleStatus status)
{
    string result = getModelFrameNameByModelId(modelId,status);
    result.append("_0000.png");
    return result;
}

string ModelRule::getModelPath(int modelId)
{
    CCString* result = CCString::createWithFormat("model/%d/",modelId);
    return result->getCString();
}

CCPoint ModelRule::getModelAnchorPoint(int modelId)
{
    float _x = INSTANCE(StringUtils)->stringToFloat(getModelAttribute(modelId, "pointX"));
    float _y = INSTANCE(StringUtils)->stringToFloat(getModelAttribute(modelId, "pointY"));
    return ccp(_x, _y);
}

CCPoint ModelRule::getModelSkillEffectAnchorPoint(int modelId)
{
    float _x = INSTANCE(StringUtils)->stringToFloat(getModelAttribute(modelId, "skillpointX"));
    float _y = INSTANCE(StringUtils)->stringToFloat(getModelAttribute(modelId, "skillpointY"));
    return ccp(_x, _y);
}

CCPoint ModelRule::getModelAttackEffectAnchorPoint(int modelId)
{
    float _x = INSTANCE(StringUtils)->stringToFloat(getModelAttribute(modelId, "attackpointX"));
    float _y = INSTANCE(StringUtils)->stringToFloat(getModelAttribute(modelId, "attackpointY"));
    return ccp(_x, _y);
}

CCSize ModelRule::getModelHurtSize(int modelId)
{
    string temp = getModelAttribute(modelId, "size");
    if(temp == "0"){
        return CCSizeMake(0, 0);
    }
    vector<int> size = INSTANCE(StringUtils)->getIntVectorFromString(temp, "_");
    return CCSizeMake(size[0], size[1]);
}

CCSize ModelRule::getModelAttackSize(int modelId)
{
    string temp = getModelAttribute(modelId, "AttackSize");
    if(temp == "0"){
        return CCSizeMake(0, 0);
    }
    vector<int> size = INSTANCE(StringUtils)->getIntVectorFromString(temp, "_");
    return CCSizeMake(size[0], size[1]);
}

CCPoint ModelRule::getSkillHitAnchorPoint(int skillId)
{
    return INSTANCE(SkillRule)->getSkillHitAnchorPoint(skillId);
}

string ModelRule::getSkillHitFrameName(int skillId,bool containPng)
{
    string result = CCString::createWithFormat("%d_skill_hit",skillId)->getCString();
    if(containPng){
        result.append(".png");
    }
    return result;
}

CCDictionary* ModelRule::getModelDic(int modelId)
{
    if(mainDic == NULL){
        mainDic = INSTANCE(BaseDataManager)->getXml(ModelConfigXml);
    }
    if(lastId != modelId){
        lastId = modelId;
        lastSubDic = (CCDictionary *) mainDic->objectForKey(INSTANCE(StringUtils)->intToString(modelId));
    }
    
    return lastSubDic;
}

string ModelRule::getModelAttribute(int modelId, const char *attributeName)
{
    return ((CCString *) getModelDic(modelId)->objectForKey(attributeName))->getCString();
}