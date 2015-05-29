//
//  FightSceneFacade.h
//  threeKingdoms
//
//  Created by .m on 13-12-24.
//
//

#ifndef __threeKingdoms__FightSceneFacade__
#define __threeKingdoms__FightSceneFacade__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "BaseRole.h"
#include "FightScene.h"
#include "NPC.h"

using namespace std;
USING_NS_CC;

class FightSceneFacade:public CCObject
{
public:
    CLASS_INSTANCE(FightSceneFacade);
    bool init();
    
    void openFightScene();
    
    void addNpcToScene(NPC *npc);
    BaseRole *getRole();
    void setRole(BaseRole *role);
    
    void showSkillHit(int skillId);
    
    void showAngerEffect(NPC *npc);
    
    FightScene *getFightScene();
private:
    FightScene *fightScene;
    BaseRole *role;
};

#endif /* defined(__threeKingdoms__FightSceneFacade__) */
