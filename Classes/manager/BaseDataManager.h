//
//  BaseDataManager.h
//  threeKingdoms
//  Created by sma11case 13-12-26.
//
//

#ifndef __threeKingdoms__BaseDataManager__
#define __threeKingdoms__BaseDataManager__

#include <iostream>
#include "GameCommon.h"
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

#define SystemConfigXml "SystemConfig.xml"
#define SoldierXml "Soldier.xml"
#define SkillXml "Skill.xml"
#define ScenesXml "Scenes.xml"
#define RoleXml "Role.xml"
#define BaseFormationXml "BaseFormation.xml"
#define ModelConfigXml "ModelConfig.xml"
#define SystemConfigXml "SystemConfig.xml"
#define TitleXml "Title.xml"
#define LoginRewardXml "LoginReward.xml"
#define WheelOfFortune "WheelOfFortune.xml"
#define TreasureBowl "TreasureBowl.xml"
#define TaskXml "DailyTasks.xml"
#define RechargeXml "Recharge.xml"

class BaseDataManager:public CCObject
{
public:
    CLASS_INSTANCE(BaseDataManager);
    bool init();
    
    CCDictionary* getXml(const char* xmlPath);
    
    string getLan(string param);
    
    void removeAllXml();
private:
    CCDictionary *xmlDic;
    CCDictionary *lanDic;
    
    void loadLan();
};

#endif /* defined(__threeKingdoms__BaseDataManager__) */
