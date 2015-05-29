//
//  NPCRule.cpp
//  threeKingdoms
//  Created by sma11case on 13-12-25.
//
//

#include "NPCRule.h"
#include "GameUtils.h"
#include "ModelRule.h"
#include "BaseDataManager.h"
#include "StringUtils.h"

bool NPCRule::init()
{
    lastId = -1;
    mainDic = NULL;
    return true;
}

string NPCRule::getNpcFrameNameByNpcId(int npcId,RoleStatus status,bool containPng)
{
    return INSTANCE(ModelRule)->getModelFrameNameByModelId(getNpcModelId(npcId), status,containPng);
}

string NPCRule::getNpcFirstFrameNameByNpcId(int npcId,RoleStatus status)
{
    return INSTANCE(ModelRule)->getModelFirstFrameNameByModelId(getNpcModelId(npcId), status);
}

int NPCRule::getNpcHp(int npcId)
{
    return INSTANCE(StringUtils)->stringToInt(getNpcAttribute(npcId, "hp"));
    
}

CCPoint NPCRule::getNpcAnchorPoint(int npcId)
{
    return INSTANCE(ModelRule)->getModelAnchorPoint(getNpcModelId(npcId));
//    return ccp(0.5,0.41);
}

int NPCRule::getNpcModelId(int npcId)
{
    return INSTANCE(StringUtils)->stringToInt(getNpcAttribute(npcId, "model"));
}

string NPCRule::getNpcName(int npcId)
{
    return INSTANCE(BaseDataManager)->getLan(getNpcAttribute(npcId, "name"));
}

int NPCRule::getNpcType(int npcId)
{
    return INSTANCE(StringUtils)->stringToInt(getNpcAttribute(npcId, "type"));
}

int NPCRule::getNpcIntegral(int npcId)
{
    return INSTANCE(StringUtils)->stringToInt(getNpcAttribute(npcId, "integral"));
}

int NPCRule::getNpcSkillId(int npcId)
{
    return INSTANCE(StringUtils)->stringToInt(getNpcAttribute(npcId, "skillId"));
}

int NPCRule::getNpcSpeed(int npcId)
{
    return INSTANCE(StringUtils)->stringToInt(getNpcAttribute(npcId, "moveSpeed"));
}

int NPCRule::getNpcMoneyMin(int npcId)
{
    return INSTANCE(StringUtils)->stringToInt(getNpcAttribute(npcId, "moneylow"));
}

int NPCRule::getNpcMoneyMax(int npcId)
{
    return INSTANCE(StringUtils)->stringToInt(getNpcAttribute(npcId, "money"));
}

int NPCRule::getNpcMoney(int npcId)
{
    int max = getNpcMoneyMax(npcId);
    int min = getNpcMoneyMin(npcId);
    if(max == min){
        return max;
    }
    return min + INSTANCE(GameUtils)->getRandom(max - min + 1);
}

int NPCRule::getNpcAnger(int npcId)
{
    return INSTANCE(StringUtils)->stringToInt(getNpcAttribute(npcId, "anger"));
}

float NPCRule::getNpcDodge(int npcId)
{
    return INSTANCE(StringUtils)->stringToFloat(getNpcAttribute(npcId, "dodge"));
}

string NPCRule::getNpcImgPath(int npcId)
{
    return INSTANCE(ModelRule)->getModelPath(getNpcModelId(npcId));
}

CCSize NPCRule::getNpcHurtSize(int npcId)
{
    return INSTANCE(ModelRule)->getModelHurtSize(getNpcModelId(npcId));
}

CCSize NPCRule::getNpcAttackSize(int npcId)
{
    return INSTANCE(ModelRule)->getModelAttackSize(getNpcModelId(npcId));
}

int NPCRule::getNpcAttackType(int npcId)
{
    return INSTANCE(StringUtils)->stringToInt(getNpcAttribute(npcId, "attackType"));
}

float NPCRule::getNpcAttackProbability(int npcId)
{
    return INSTANCE(StringUtils)->stringToFloat(getNpcAttribute(npcId, "attackProbability"));
}

float NPCRule::getNpcStandProbability(int npcId)
{
    return INSTANCE(StringUtils)->stringToFloat(getNpcAttribute(npcId, "standbyProbability"));
}

float NPCRule::getNpcSpeedUpProbability(int npcId)
{
    return INSTANCE(StringUtils)->stringToFloat(getNpcAttribute(npcId, "speedUpProbability"));
}

float NPCRule::getNpcSpeedDownProbability(int npcId)
{
    return INSTANCE(StringUtils)->stringToFloat(getNpcAttribute(npcId, "reducerProbability"));
}

int NPCRule::getNpcAttackPenalty(int npcId)
{
    return INSTANCE(StringUtils)->stringToInt(getNpcAttribute(npcId, "attackPenalty"));
}

string NPCRule::getNpcDesc(int npdId)
{
    return INSTANCE(BaseDataManager)->getLan(getNpcAttribute(npdId, "feature"));
}

CCDictionary* NPCRule::getNpcDic(int npcId)
{
    if(mainDic == NULL){
        mainDic =  INSTANCE(BaseDataManager)->getXml(SoldierXml);
    }
    if(lastId != npcId){
        lastId = npcId;
        lastSubDic = (CCDictionary *)mainDic->objectForKey(INSTANCE(StringUtils)->intToString(npcId));
    }
    return lastSubDic;
}

string NPCRule::getNpcAttribute(int npcId, const char *attributeName)
{
    return ((CCString *) getNpcDic(npcId)->objectForKey(attributeName))->getCString();
}


