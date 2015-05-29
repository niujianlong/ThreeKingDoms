//
//  NPCManager.cpp
//  threeKingdoms
//
//  Created by .m on 13-12-25.
//
//

#include "NPCManager.h"
#include "GameUtils.h"
#include "FightManager.h"
#include "StringUtils.h"
#include "NPCRule.h"
#include "FightSceneFacade.h"
#include "MoneyLayer.h"
#include "SoundManager.h"
#include "BossLottery.h"
#include "SystemConfigRule.h"
#include "UserData.h"
#include "GoldPot.h"
#include "Task.h"
#include "GuideManager.h"

bool NPCManager::init()
{
    isStop = false;
    npcArray = CCArray::create();
    tempNpcArray = CCArray::create();
    tempNpcArray->retain();
    npcArray->retain();
    
    return true;
}

void NPCManager::startUpdate()
{
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(NPCManager::updateNpcInfo), this, 0.3, false);
}

void NPCManager::stopUpdate()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(NPCManager::updateNpcInfo), this);
}

void NPCManager::createTroopsNPC(int npcId,int formationIndex,RoleDirection direction,int speed,TroopsType troopsType)
{
    if(isStop){
        return;
    }
    
    NPC *npc = NPC::create(npcId,direction,speed,false,troopsType);
    npc->setPosition(getNPCPosition(formationIndex,direction));
    npcArray->addObject(npc);
    INSTANCE(FightSceneFacade)->addNpcToScene(npc);

}

void NPCManager::createRandomNpc(int npcId,bool isBoss)
{
    if(isStop && !isBoss){
        return;
    }
    
    RoleDirection direction = INSTANCE(GameUtils)->getRandomFromFloat(0.5)?RoleDirection_left:RoleDirection_right;
    int speed = INSTANCE(NPCRule)->getNpcSpeed(npcId);
    int index = INSTANCE(GameUtils)->getRandom(5);
    
    NPC *npc = NPC::create(npcId,direction,speed,isBoss,TroopsType_none);
    npc->setPosition(getNPCPosition(index,direction));
    npcArray->addObject(npc);
    INSTANCE(FightSceneFacade)->addNpcToScene(npc);
}

void NPCManager::removeNPC(NPC *npc)
{
    int money = npc->getNpcMoney();
    INSTANCE(FightManager)->addAnger(npc->getNpcAnger());
    INSTANCE(MoneyLayerManager)->showMoney(npc->getPosition(), money * INSTANCE(FightManager)->getCurrentRate() * INSTANCE(FightManager)->getAttackMultiple());
//    INSTANCE(MoneyLayerManager)->createReduceMoney(money);
    tempNpcArray->addObject(npc);
    npcArray->removeObject(npc);
    if(npc->getNpcIsBoss()){
        INSTANCE(FightManager)->setBossDeadStatus(BossStatus_dead);
        
        if(INSTANCE(FightManager)->isFinalBoss(npc->getNpcId())){
            if(INSTANCE(SystemConfigRule)->potIsFull()){
                INSTANCE(GoldPotFacade)->showGoldPot();
            }
            INSTANCE(UserData)->addFinishChapterTimes(1);
            CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdatePot);
        }
        
    }
    
    INSTANCE(TaskFacade)->addFinishNum(npc->getNpcId());
    
    if(INSTANCE(GuideManager)->getIsGuiding() && npc->getSkillId() != 0){
        allNpcStopComplete();
        INSTANCE(GuideManager)->goToNext();
    }
    
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(NPCManager::removeNpcHandler), this);
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(NPCManager::removeNpcHandler), this, 0.1, false);
}

void NPCManager::removeNpcHandler()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(NPCManager::removeNpcHandler), this);
    int totleMoney = 0;
    int totleIntegral = 0;
    for(int i=tempNpcArray->count() - 1;i>=0;i--){
        NPC *npc = (NPC *)tempNpcArray->objectAtIndex(i);
        int money = npc->getNpcMoney();
        int integral = npc->getNpcIntegral();
        
        totleMoney += money;
        totleIntegral+=integral;
        tempNpcArray->removeObject(npc);
        if(npc->getNpcIsBoss()){
            INSTANCE(BossLotteryFacade)->setBossMultiple(1);
        }
    }
    
    INSTANCE(FightManager)->addMoney(totleMoney * INSTANCE(FightManager)->getAttackMultiple());
    INSTANCE(FightManager)->addIntegral(totleIntegral);
}

CCPoint NPCManager::getNPCPosition(int index,RoleDirection direction)
{
    if(direction == RoleDirection_right){
        return ccp(- 700 - (index / 5) * 100, (index % 5) * 60 - 250);
    }else{
        return ccp(700 + (index / 5) * 100, (index % 5) * 60 - 250);
    }
    
}

CCArray* NPCManager::getAllNpc()
{
    return npcArray;
}

void NPCManager::updateNpcInfo()
{
    for(int i=npcArray->count() - 1;i >= 0;i--){
        NPC *npc = (NPC*)npcArray->objectAtIndex(i);
        bool dead = false;
        if(npc->getCurrentDirection() == RoleDirection_left && npc->getPosition().x <= -720){
            dead = true;
        }
        if(npc->getCurrentDirection() == RoleDirection_right && npc->getPosition().x >= 720){
            dead = true;
        }
        if(dead){
            npc->removeFromParent();
            npcArray->removeObjectAtIndex(i);
            if(npc->getNpcIsBoss()){
                INSTANCE(BossLotteryFacade)->setBossMultiple(1);
                INSTANCE(FightManager)->setBossDeadStatus(BossStatus_disappear);
            }
        }else{
            if(npc->getNpcAttackType() == 2 || (npc->getNpcTroopsType() == TroopsType_attack && npc->getNpcAttackType() != 0)){
                if(INSTANCE(FightManager)->npcCanAttackRole(npc)){
                    npc->playAttack();
                }
            }
        }
    }
    
    if(INSTANCE(GuideManager)->getIsGuiding()){
        if(INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10000){
            if(npcArray->count() == 0){
                createGuideNpc_1();
            }
        }else if(INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10001){
            for(int i=npcArray->count() - 1;i >= 0;i--){
                NPC *npc = (NPC*)npcArray->objectAtIndex(i);
                if(npc->getPosition().x <= 0){
                    keepAllNpcStop(0);
                    INSTANCE(GuideManager)->goToNext();
                    break;
                }
            }
        }else if(INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10004){
            if(npcArray->count() == 0){
                createGuideNpc_2();
            }
        }else if(INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10005){
            for(int i=npcArray->count() - 1;i >= 0;i--){
                NPC *npc = (NPC*)npcArray->objectAtIndex(i);
                if(npc->getSkillId() != 0){
                    INSTANCE(GuideManager)->registerPosition(GuideStep_10006, npc->getParent()->convertToWorldSpace(npc->getPosition()));
                }
            }
            for(int i=npcArray->count() - 1;i >= 0;i--){
                NPC *npc = (NPC*)npcArray->objectAtIndex(i);
                if(npc->getPosition().x <= 0){
                    keepAllNpcStop(0);
                    INSTANCE(GuideManager)->goToNext();
                    break;
                }
            }
        }else if(INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10007){
            if(npcArray->count() == 0){
                INSTANCE(GuideManager)->goToNext();
            }
        }
        
    }else{
        BossStatus status = INSTANCE(FightManager)->getBossDeadStatus();
        if(npcArray->count() == 0){
            if(status != BossStatus_appear && !INSTANCE(FightManager)->getTroopsAppear()){
                //清屏完毕 出送分部队
                if(status == BossStatus_disappear){
                    INSTANCE(FightManager)->createTroops(0);
                }else{
                    INSTANCE(FightManager)->createTroops(1);
                }
                
            }else if(status != BossStatus_appear && INSTANCE(FightManager)->getTroopsAppear()){
                //送分部队清屏完毕
                INSTANCE(FightManager)->setBossDeadStatus(BossStatus_appear);
                INSTANCE(FightManager)->setTroopsAppear(false);
                INSTANCE(FightManager)->setCreateBossCallSelect();
            }
        }
    }
    
    
}

void NPCManager::keepAllNpcStop(int second)
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(NPCManager::stopHandler), this);
    isStop = true;
    for(int i=npcArray->count() - 1;i >= 0;i--){
        NPC *npc = (NPC*)npcArray->objectAtIndex(i);
        npc->playStop();
    }
    
    if(second > 0){
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(NPCManager::stopHandler), this, second, false);
    }
}

void NPCManager::allNpcStopComplete()
{
    stopHandler();
}

void NPCManager::stopHandler()
{
    for(int i=npcArray->count() - 1;i >= 0;i--){
        NPC *npc = (NPC*)npcArray->objectAtIndex(i);
        if(npc->getNpcStatus() != RoleStatusDie){
            npc->setIsStop(false);
            npc->playWalk();
        }
    }
    isStop = false;
    INSTANCE(FightManager)->setMustHitbale(false);
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(NPCManager::stopHandler), this);
    
    
}

void NPCManager::removeAllNpc()
{
    npcArray->removeAllObjects();
}


void NPCManager::createGuideNpc_1()
{
    if(INSTANCE(GuideManager)->getIsGuiding() && INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10000){
        RoleDirection direction = RoleDirection_left;
        int speed = 80;
        
        for(int i=0;i<3;i++){
            for(int j=1;j<=3;j++){
                NPC *npc = NPC::create(10001,direction,speed,false,TroopsType_none);
                npc->setPosition(getNPCPosition(j + i*5,direction));
                npcArray->addObject(npc);
                INSTANCE(FightSceneFacade)->addNpcToScene(npc);
            }
            
        }
        INSTANCE(GuideManager)->goToNext();
    }
}

void NPCManager::createGuideNpc_2()
{
    RoleDirection direction = RoleDirection_left;
    int speed = 80;
    int num = 0;
    for(int i=0;i<10;i++){
        NPC *npc = NPC::create(10001,direction,speed,false,TroopsType_none);
        npc->setPosition(getNPCPosition(i,direction));
        npcArray->addObject(npc);
        INSTANCE(FightSceneFacade)->addNpcToScene(npc);
    }
    num+=10;
    
    NPC *npc = NPC::create(10004,direction,speed,false,TroopsType_none);
    npc->setPosition(getNPCPosition(num + 2,direction));
    npcArray->addObject(npc);
    INSTANCE(FightSceneFacade)->addNpcToScene(npc);
    
    num+=5;
    
    for(int i=0;i<10;i++){
        NPC *npc = NPC::create(10016,direction,speed,false,TroopsType_none);
        npc->setPosition(getNPCPosition(num + i,direction));
        npcArray->addObject(npc);
        INSTANCE(FightSceneFacade)->addNpcToScene(npc);
    }
    
    num+=10;
    
    
    
    for(int i=0;i<10;i++){
        NPC *npc = NPC::create(10010,direction,speed,false,TroopsType_none);
        npc->setPosition(getNPCPosition(num + i,direction));
        npcArray->addObject(npc);
        INSTANCE(FightSceneFacade)->addNpcToScene(npc);
    }
    INSTANCE(GuideManager)->goToNext();
}

void NPCManager::setStop(bool param)
{
    isStop = param;
}


