//
//  FightSceneFacade.cpp
//  threeKingdoms
//  Created by sma11case on 13-12-24.
//
//

#include "FightSceneFacade.h"
#include "ParticleManager.h"

bool FightSceneFacade::init()
{
    fightScene = NULL;
    return true;
}

void FightSceneFacade::openFightScene()
{
    CCScene *scene = CCScene::create();
    fightScene = FightScene::create();
    scene->addChild(fightScene);
    CCDirector::sharedDirector()->replaceScene(scene);
}

void FightSceneFacade::addNpcToScene(NPC *npc)
{
    if(fightScene){
        fightScene->addNpcToScene(npc);
    }
}

void FightSceneFacade::setRole(BaseRole *role)
{
    this->role = role;
}

BaseRole *FightSceneFacade::getRole()
{
    return role;
}

void FightSceneFacade::showSkillHit(int skillId)
{
    fightScene->showSkillHit(skillId);
}

void FightSceneFacade::showAngerEffect(NPC *npc)
{
    if(fightScene){
        fightScene->showAngerEffect(npc);
    }
}

FightScene* FightSceneFacade::getFightScene()
{
    return fightScene;
}