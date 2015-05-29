//
//  SkillRule.cpp
//  threeKingdoms
//  Created by sma11case 13-12-30.
//
//

#include "SkillRule.h"
#include "BaseDataManager.h"
#include "StringUtils.h"

bool SkillRule::init()
{
    lastId = -1;
    mainDic = NULL;
    return true;
}

int SkillRule::getSkillCost(int skillId)
{
    return INSTANCE(StringUtils)->stringToInt(getSkillAttribute(skillId, "anger"));
}

string SkillRule::getSkillName(int skillId)
{
    return INSTANCE(BaseDataManager)->getLan(getSkillAttribute(skillId, "name"));
}

CCPoint SkillRule::getSkillHitAnchorPoint(int skillId)
{
    float _x = INSTANCE(StringUtils)->stringToFloat(getSkillAttribute(skillId, "skillpointX"));
    float _y = INSTANCE(StringUtils)->stringToFloat(getSkillAttribute(skillId, "skillpointY"));
    return ccp(_x, _y);
}

CCDictionary* SkillRule::getSkillDic(int skillId)
{
    if(mainDic == NULL){
        mainDic = INSTANCE(BaseDataManager)->getXml(SkillXml);
    }
    
    if(lastId != skillId ){
        lastId = skillId;
        lastSubDic = (CCDictionary *) mainDic->objectForKey(CCString::createWithFormat("%d",skillId)->getCString());
    }
    return lastSubDic;
}

string SkillRule::getSkillAttribute(int skillId, const char *attributeName)
{
    return ((CCString *) getSkillDic(skillId)->objectForKey(attributeName))->getCString();
}