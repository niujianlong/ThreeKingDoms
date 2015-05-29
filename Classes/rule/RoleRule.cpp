//
//  RoleRule.cpp
//  threeKingdoms
//  Created by sma11case on 13-12-24.
//
//

#include "RoleRule.h"
#include "ModelRule.h"
#include "BaseDataManager.h"
#include "StringUtils.h"
#include "UserData.h"
#include "GameUtils.h"
#include <algorithm>

bool RoleRule::init()
{
    mainDic = NULL;
    return true;
}

string RoleRule::getRoleFrameNameByRoleId(int roleId,RoleStatus status,bool containPng)
{
    return INSTANCE(ModelRule)->getModelFrameNameByModelId(getRoleModelId(roleId), status,containPng);
}

string RoleRule::getRoleFirstFrameNameByRoleId(int roleId,RoleStatus status)
{
    return INSTANCE(ModelRule)->getModelFirstFrameNameByModelId(getRoleModelId(roleId), status);
}

string RoleRule::getRoleName(int roleId)
{
    return INSTANCE(BaseDataManager)->getLan(getRoleAttribute(roleId, "name"));
}

int RoleRule::getRoleSkillId(int roleId)
{
    return INSTANCE(StringUtils)->stringToInt(getRoleAttribute(roleId, "skillId"));
}

CCPoint RoleRule::getRoleAnchorPoint(int roleId)
{
    return INSTANCE(ModelRule)->getModelAnchorPoint(getRoleModelId(roleId));
}

CCPoint RoleRule::getRoleSkillEffectAnchorPoint(int roleId)
{
    return INSTANCE(ModelRule)->getModelSkillEffectAnchorPoint(getRoleModelId(roleId));
}

CCPoint RoleRule::getRoleAttackEffectAnchorPoint(int roleId)
{
    return INSTANCE(ModelRule)->getModelAttackEffectAnchorPoint(getRoleModelId(roleId));
}

int RoleRule::getRoleAttackFrameNum(int roleId)
{
    return 3;
}

int RoleRule::getRoleSkillFrameNum(int roleId)
{
    return 7;
}

int RoleRule::getRoleModelId(int roleId)
{
    return INSTANCE(StringUtils)->stringToInt(getRoleAttribute(roleId, "model"));
}

int RoleRule::getRoleMaxAttack(int roleId)
{
    return INSTANCE(StringUtils)->stringToInt(getRoleAttribute(roleId, "maxATK"));
}

int RoleRule::getRoleMinAttack(int roleId)
{
    return INSTANCE(StringUtils)->stringToInt(getRoleAttribute(roleId, "minATK"));
}

int RoleRule::getRoleSpeed(int roleId)
{
    return INSTANCE(StringUtils)->stringToInt(getRoleAttribute(roleId, "moveSpeed"));
}

float RoleRule::getRoleAttackSpeed(int roleId)
{
    return INSTANCE(StringUtils)->stringToFloat(getRoleAttribute(roleId, "attackSpeed"));
}

string RoleRule::getRoleImgPath(int roleId)
{
    return INSTANCE(ModelRule)->getModelPath(getRoleModelId(roleId));
}

CCSize RoleRule::getRoleAttackSize(int roleId)
{
    return INSTANCE(ModelRule)->getModelAttackSize(getRoleModelId(roleId));
}

CCSize RoleRule::getRoleHurtSize(int roleId)
{
    return INSTANCE(ModelRule)->getModelHurtSize(getRoleModelId(roleId));
}

CCDictionary* RoleRule::getRoleDic(int roleId)
{
    if(mainDic == NULL){
        mainDic = INSTANCE(BaseDataManager)->getXml(RoleXml);
    }
    
    if(lastId != roleId){
        lastId = roleId;
        lastSubDic = (CCDictionary *)mainDic->objectForKey(CCString::createWithFormat("%d",roleId)->getCString());
    }

    return lastSubDic;
}

string RoleRule::getRoleAttribute(int roleId, const char *attributeName)
{
    return ((CCString *) getRoleDic(roleId)->objectForKey(attributeName))->getCString();
}

int RoleRule::getRoleVip(int roleId)
{
    return INSTANCE(StringUtils)->stringToInt(getRoleAttribute(roleId, "vip"));
}

int RoleRule::getRoleCost(int roleId)
{
    return INSTANCE(StringUtils)->stringToInt(getRoleAttribute(roleId, "goldCost"));
}

int RoleRule::getRoleSequence(int roleId)
{
    return INSTANCE(StringUtils)->stringToInt(getRoleAttribute(roleId, "sequence"));
}

bool RoleRule::ownRole(int roleId)
{
    vector<int> roles = INSTANCE(StringUtils)->getIntVectorFromString(INSTANCE(UserData)->getRoles(), "_");
    return INSTANCE(GameUtils)->vectorContainInt(roles, roleId);
}

string RoleRule::getRoleDesc(int roleId)
{
    return INSTANCE(BaseDataManager)->getLan(getRoleAttribute(roleId, "feature"));
}

vector<int> RoleRule::getFreeRolesVector()
{
    vector<int> result;
    CCArray *key = INSTANCE(BaseDataManager)->getXml(RoleXml)->allKeys();
    for(int i=0;i<key->count();i++){
        int roleId =INSTANCE(StringUtils)->stringToInt((CCString *)key->objectAtIndex(i));
        int vip = getRoleVip(roleId);
        int goldCost = getRoleCost(roleId);
        if(vip == 0 && goldCost == 0){
            result.push_back(roleId);
        }
    }
    return result;
}

string RoleRule::getFreeRoles()
{
    string result = "";
    vector<int> free = getFreeRolesVector();
    
    return INSTANCE(StringUtils)->intVectorToString(free);
}

vector<int> RoleRule::getAllRoleId()
{
    vector<int> result;
    CCArray *key = INSTANCE(BaseDataManager)->getXml(RoleXml)->allKeys();
    for(int i=0;i<key->count();i++){
        result.push_back(INSTANCE(StringUtils)->stringToInt((CCString *)key->objectAtIndex(i)));
    }
    
    sort(result.begin(), result.end(),compareRole);
    return result;
}

bool compareRole(int roleId_1,int roleId_2)
{
    return INSTANCE(RoleRule)->getRoleSequence(roleId_1) < INSTANCE(RoleRule)->getRoleSequence(roleId_2);
}

