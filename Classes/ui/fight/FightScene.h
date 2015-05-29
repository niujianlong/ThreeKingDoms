//
//  FightScene.h
//  threeKingdoms
//  Created by sma11case 13-12-24.
//
//

#ifndef __Three__FightScene__
#define __Three__FightScene__

#include <iostream>
#include "cocos2d.h"
#include "BaseRole.h"
#include "NPC.h"

using namespace std;
USING_NS_CC;

class FightScene:public CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(FightScene);
    FightScene();
    ~FightScene();
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    
    void addNpcToScene(NPC *npc);
    
    void showSkillHit(int skillId);
    void showAngerEffect(NPC *npc);
private:
    CCSprite *bg;
    void initMap();
    void initUI();
    void initRole();
    BaseRole *role;
    
    CCNode *mapNode;
    
    void update(float t);
    
    CCSprite *getSkillHit(int skillId);
    void showSkillName(int skillId,float duration);
    
    void shake();
    
    bool handseling;
    void startHandsel();
    void stopHandsel();
    void handselGold();
};

#endif /* defined(__Three__FightScene__) */
