//
//  SkillRule.h
//  threeKingdoms
//
//  Created by .m on 13-12-30.
//
//

#ifndef __threeKingdoms__SkillRule__
#define __threeKingdoms__SkillRule__

#include <iostream>
#include "cocos2d.h"
#include "GameUtils.h"

using namespace std;
USING_NS_CC;

class SkillRule:public CCObject
{
public:
    CLASS_INSTANCE(SkillRule);
    bool init();
    
    //技能消耗
    int getSkillCost(int skillId);
    //技能名
    string getSkillName(int skillId);
    //技能被击效果锚点
    CCPoint getSkillHitAnchorPoint(int skillId);
    
private:
    CCDictionary *getSkillDic(int skillId);
    string getSkillAttribute(int skillId, const char *attributeName);
    
    CCDictionary *mainDic;
    int lastId;
    CCDictionary *lastSubDic;
};

#endif /* defined(__threeKingdoms__SkillRule__) */
