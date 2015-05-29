//
//  NPC.cpp
//  threeKingdoms
//  Created by sma11case 13-12-24.
//
//

#include "NPC.h"
#include "AnimationUtils.h"
#include "FightManager.h"
#include "NPCRule.h"
#include "SoundManager.h"
#include "FightSceneFacade.h"
#include "NPCManager.h"
#include "GameUtils.h"
#include "BossLottery.h"
#include "GuideManager.h"

NPC* NPC::create(int npcId,RoleDirection direction,int speed,bool isBoss,TroopsType troopsType)
{
    NPC *npc = new NPC(npcId,direction,speed,isBoss,troopsType);
    if(npc && npc->init()){
        npc->autorelease();
        return npc;
    }else{
        delete npc;
        npc = NULL;
        return NULL;
    }
}

NPC::NPC(int npcId,RoleDirection direction,int speed,bool isBoss,TroopsType troopsType){
    this->npcId = npcId;
    this->isBoss = isBoss;
    this->currentDirection = direction;
    this->troopsType = troopsType;
    if(speed == 0){
        this->npcSpeed= INSTANCE(NPCRule)->getNpcSpeed(npcId);
    }else{
        this->npcSpeed= speed;
    }
    
    currentStatus = RoleStatusNone;
    npcRole = NULL;
    isStop = false;
    accelerated = false;
    isDead = false;
    attackable = true;
}

NPC::~NPC()
{
    
}

bool NPC::init()
{
    if(!CCNode::init()){
        return false;
    }
    
    string img = INSTANCE(NPCRule)->getNpcImgPath(npcId);
    img.append(INSTANCE(NPCRule)->getNpcFrameNameByNpcId(npcId, RoleStatusWalk));
    img.append(".plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(img.c_str());
    img = INSTANCE(NPCRule)->getNpcFirstFrameNameByNpcId(npcId, RoleStatusWalk);
    npcRole = CCSprite::createWithSpriteFrameName(img.c_str());
    addChild(npcRole);
    npcRole->setAnchorPoint(INSTANCE(NPCRule)->getNpcAnchorPoint(npcId));
    if(currentDirection == RoleDirection_right){
        npcRole->setFlipX(false);
    }else{
        npcRole->setFlipX(true);
    }
    CCSprite *shadow = CCSprite::create("fightImg/role_shadow.png");
    npcRole->addChild(shadow,-1);
    shadow->setPosition(npcRole->getAnchorPointInPoints());
    
    if(INSTANCE(NPCRule)->getNpcSkillId(npcId) != 0){
        CCSprite *effect = CCSprite::create();
        CCAnimation *animation = INSTANCE(AnimationUtils)->getCommonAnimation("fightImg/skillNpcEffect.plist", "skillNpcEffect");
        CCAction *action = CCRepeatForever::create(CCAnimate::create(animation));
        effect->runAction(action);
        npcRole->addChild(effect);
        effect->setAnchorPoint(ccp(0.5, 0.2));
        effect->setPosition(npcRole->getAnchorPointInPoints());
    }
    
    hurtSize = INSTANCE(NPCRule)->getNpcHurtSize(npcId);
    skillId = INSTANCE(NPCRule)->getNpcSkillId(npcId);
    missRate = INSTANCE(NPCRule)->getNpcDodge(npcId);
    npcMoney = INSTANCE(NPCRule)->getNpcMoney(npcId);
    npcIntegral = INSTANCE(NPCRule)->getNpcIntegral(npcId);
    npcAnger = INSTANCE(NPCRule)->getNpcAnger(npcId);
    standProbability = INSTANCE(NPCRule)->getNpcStandProbability(npcId);
    npcAttackType = INSTANCE(NPCRule)->getNpcAttackType(npcId);
    runAwayStatus = RunAwayStatus_none;
    attackPenalty = INSTANCE(NPCRule)->getNpcAttackPenalty(npcId);
    return true;
}

void NPC::onEnter()
{
    CCNode::onEnter();
    playWalk();
    if(troopsType == TroopsType_none && standProbability > 0){
        getScheduler()->scheduleSelector(schedule_selector(NPC::playStand), this, 3 + INSTANCE(GameUtils)->getRandom(3), false);
    }
}

void NPC::onExit()
{
    CCNode::onExit();
}

int NPC::getNpcId()
{
    return npcId;
}


void NPC::playWalk()
{
    if(currentStatus == RoleStatusWalk){
        return;
    }
    currentStatus = RoleStatusWalk;
    playWalkAnimate();
}

void NPC::playHurt(bool hit)
{
    if(isDead){
        return;
    }
    //停止反击
    getScheduler()->unscheduleSelector(schedule_selector(NPC::startAttackBack), this);
    currentStatus = RoleStatusHurt;
    stopMove();
    
    npcRole->stopAllActions();
    
    if(hit){
        isDead = true;
        getScheduler()->unscheduleAllForTarget(this);//重要
    }
    
    float duration;
    if(accelerated){
        duration = 0.05;
    }else{
        duration = 0.1;
    }
    CCAnimate *animate = getAnimate(RoleStatusHurt);
    CCAction *action = CCSequence::create(animate,CCDelayTime::create(0.1),CCCallFuncN::create(this, callfuncN_selector(NPC::hurtComplete)),NULL);
    npcRole->runAction(action);
    
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        if(skillId != 0){
            float duration = animate->getDuration();
            CCMoveBy *move;
            if(INSTANCE(FightSceneFacade)->getRole()->getRoleDirection() == RoleDirection_left){
                move = CCMoveBy::create(duration,ccp(-100, 0));
            }else{
                move = CCMoveBy::create(duration,ccp(100, 0));
            }
            
            this->runAction(move);
        }
    }
    
    
    INSTANCE(SoundManager)->playFightHurt();
    playBlood();
}

void NPC::hurtComplete()
{
    if(isDead){
        playDie();
    }else{
        if(isStop){
            npcRole->stopAllActions();
            npcRole->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(INSTANCE(NPCRule)->getNpcFirstFrameNameByNpcId(npcId, RoleStatusWalk).c_str()));
        }else{
            bool isAttackBack;
            int attackType = INSTANCE(NPCRule)->getNpcAttackType(npcId);
            if(troopsType == TroopsType_none){
                //无阵型
                if(attackType == 0 || attackType == 2){
                    isAttackBack = false;
                }else{
                    if(INSTANCE(GameUtils)->getRandomFromFloat(INSTANCE(NPCRule)->getNpcAttackProbability(npcId))){
                        isAttackBack = true;
                    }else{
                        isAttackBack = false;
                    }
                }
            }else if(troopsType == TroopsType_attack){
                isAttackBack = false;
            }else{
                isAttackBack = false;
            }
            
            
            if(isAttackBack){
                //在攻击范围内反击
                if(INSTANCE(FightManager)->npcCanAttackRole(this)){
                    playAttackBack();
                }else{
                    playWalk();
                }
                
            }else{
                float speedUpP = INSTANCE(NPCRule)->getNpcSpeedUpProbability(npcId);
                float speedDonwP = INSTANCE(NPCRule)->getNpcSpeedDownProbability(npcId);
                if(speedUpP == 0 && speedDonwP == 0){
                    //不反击 不逃跑
                    playWalk();
                }else if(speedUpP != 0){
                    //加速逃跑
                    if(INSTANCE(GameUtils)->getRandomFromFloat(speedUpP)){
                        runAway(true);
                    }else {
                        playWalk();
                    }
                    
                }else{
                    //减速
                    if(INSTANCE(GameUtils)->getRandomFromFloat(speedDonwP)){
                        runAway(false);
                    }else {
                        playWalk();
                    }
                }
            }
            
        }
        
    }
}

void NPC::playDie()
{
    if(currentStatus == RoleStatusDie){
        return;
    }
    stopMove();
    getScheduler()->unscheduleAllForTarget(this);
    npcRole->stopAllActions();
    CCAnimate *animate = getAnimate(RoleStatusDie);
    float duration = animate->getDuration()/2;
    CCAction *action = CCSequence::create(animate,CCDelayTime::create(5) ,CCCallFuncN::create(this, callfuncN_selector(NPC::dieComplete)),NULL);
    npcRole->runAction(action);
    
    CCMoveBy *move;
    
    if(INSTANCE(FightSceneFacade)->getRole()->getPosition().x > getPosition().x){
        //向左偏移
        if(true){
            int offset = - CCDirector::sharedDirector()->getWinSize().width/2 - getPosition().x + 300;
            move = CCMoveBy::create(duration,ccp(offset>-350?-350:offset , 0));
        }else{
            move = CCMoveBy::create(duration,ccp(-350, 0));
        }
        
        npcRole->setFlipX(true);
    }else{
        //向右偏移
        if(true){
            int offset = CCDirector::sharedDirector()->getWinSize().width/2 - getPosition().x - 300;
            move = CCMoveBy::create(duration,ccp(offset< 350?350:offset , 0));
        }else{
            move = CCMoveBy::create(duration,ccp(350, 0));
        }
        npcRole->setFlipX(false);
    }
    
    this->runAction(move);
    
    INSTANCE(SoundManager)->playFightDead();
    INSTANCE(NPCManager)->removeNPC(this);
    
    if(skillId != 0){
        INSTANCE(FightManager)->npcSkill(skillId);
    }
    if(npcAnger > 0){
        INSTANCE(FightSceneFacade)->showAngerEffect(this);
    }
}

void NPC::dieComplete()
{
    removeFromParent();
}

void NPC::startMove(bool changeY)
{
    float duration;
    int _x;
    int tempSpeed = npcSpeed;
    if(accelerated){
        tempSpeed = npcSpeed * ClearNpcSpeedCoefficient;
    }
    if(runAwayStatus == RunAwayStatus_speedUp){
        tempSpeed = tempSpeed * NpcRunAwaySpeedCoefficient;
    }else if(runAwayStatus == RunAwayStatus_speedDown){
        tempSpeed = tempSpeed / NpcRunAwaySpeedCoefficient;
    }
    if(currentDirection == RoleDirection_right){
        duration = (740 - getPosition().x)/tempSpeed;
        _x = 740;
    }else{
        duration = (740 + getPosition().x)/tempSpeed;
        _x = -740;
    }
    
    int positionY = getNpcPositionY() - getPosition().y;
    CCMoveTo *move = CCMoveTo::create(duration, ccp(_x, getPosition().y));
    if(changeY){
        int offsetY = INSTANCE(GameUtils)->getRandomFromFloat(0.5)? 60:-60;
        if(getPosition().y + offsetY > -10 || getPosition().y + offsetY < -250){
            offsetY = -offsetY;
        }
        positionY += offsetY;
        
    }
    
    if(positionY != 0){
        CCMoveBy *moveY = CCMoveBy::create(0.4, ccp(0, positionY));
        this->runAction(moveY);
    }
    
    this->runAction(move);
}

void NPC::stopMove()
{
    this->stopAllActions();
}

void NPC::playStand()
{
    getScheduler()->unscheduleSelector(schedule_selector(NPC::playStand), this);
    if(currentStatus == RoleStatusStand){
        return;
    }
    stopMove();
    
    currentStatus = RoleStatusStand;
    
    npcRole->stopAllActions();
    CCAnimate *animate = getAnimate(RoleStatusStand);
    CCRepeatForever *action = CCRepeatForever::create(animate);
    npcRole->runAction(action);
    getScheduler()->scheduleSelector(schedule_selector(NPC::standComplete), this, 3 + INSTANCE(GameUtils)->getRandom(3), false);
}

void NPC::standComplete()
{
    getScheduler()->unscheduleSelector(schedule_selector(NPC::standComplete), this);
    if(INSTANCE(GameUtils)->getRandomFromFloat(standProbability)){
        getScheduler()->scheduleSelector(schedule_selector(NPC::playStand), this, 3 + INSTANCE(GameUtils)->getRandom(3), false);
    }
    playWalk();
}

void NPC::setNpcStatus(RoleStatus status)
{
    currentStatus = status;
}

RoleStatus NPC::getNpcStatus()
{
    return currentStatus;
}

CCAnimate* NPC::getAnimate(RoleStatus status)
{
    string img = INSTANCE(NPCRule)->getNpcFrameNameByNpcId(npcId, status);
    float duration;
    if(status == RoleStatusWalk){
        duration = 6.0/(float)npcSpeed;
        if(accelerated){
            duration = duration / (ClearNpcSpeedCoefficient/2);
        }
        if(runAwayStatus == RunAwayStatus_speedUp){
            duration = duration / (NpcRunAwaySpeedCoefficient/2);
        }else if(runAwayStatus == RunAwayStatus_speedDown){
            duration = duration * NpcRunAwaySpeedCoefficient;
        }
    }else{
        duration = 0.1;
    }
    
    CCAnimation *animation = INSTANCE(AnimationUtils)->getModelAnimation(INSTANCE(NPCRule)->getNpcModelId(npcId),img.c_str(), img.c_str(),duration);
    CCAnimate *animate = CCAnimate::create(animation);
    return animate;
}

RoleDirection NPC::getCurrentDirection()
{
    return currentDirection;
}

CCRect NPC::getAttackRect()
{
    CCSize size = INSTANCE(NPCRule)->getNpcAttackSize(npcId);
    if(currentDirection == RoleDirection_left){
        return CCRectMake(getPositionX() - size.width, getPositionY() - size.height/2, size.width, size.height);
    }else{
        return CCRectMake(getPositionX(), getPositionY() - size.height/2, size.width, size.height);
    }
    
}

CCRect NPC::getHurtRect()
{
    return CCRectMake(getPositionX() - hurtSize.width/2, getPositionY() - hurtSize.height/2, hurtSize.width, hurtSize.height);

}

float NPC::getMiss()
{
    return missRate;
}

int NPC::getRow()
{
    return INSTANCE(FightManager)->getRow(getPositionY());
}

void NPC::playStop()
{
    if(!isDead){
        currentStatus = RoleStatusNone;
        isStop = true;
        stopAllActions();
        npcRole->stopAllActions();
        getScheduler()->pauseTarget(this);
    }
}

void NPC::setIsStop(bool stop)
{
    isStop = stop;
    if(!stop){
//        npcRole->resumeSchedulerAndActions();
//        resumeSchedulerAndActions();
        getScheduler()->resumeTarget(this);
    }
}

void NPC::playBlood()
{
    string imgPath = "fightImg/blood.plist";
    CCAnimation *animation = INSTANCE(AnimationUtils)->getCommonAnimation(imgPath.c_str(), "blood",0.07);
    CCSprite *blood = CCSprite::create();
    CCSequence *action = CCSequence::create(CCAnimate::create(animation),CCCallFuncN::create(blood, callfuncN_selector(CCSprite::removeFromParent)),NULL);
    blood->runAction(action);
    addChild(blood);
    blood->setPosition(ccp(0, 100));
}

//int NPC::getNpcHp()
//{
//    return npcHp;
//}
bool NPC::getNpcIsDead()
{
    return isDead;
}

int NPC::getNpcAnger()
{
    return npcAnger;
}

int NPC::getNpcIntegral()
{
    return npcIntegral;
}

int NPC::getNpcMoney()
{
    if(isBoss){
        return npcMoney * INSTANCE(BossLotteryFacade)->getBossMultiple();
    }
    return npcMoney;
}

bool NPC::getNpcIsBoss()
{
    return isBoss;
}

void NPC::acceleratedMove()
{
    getScheduler()->unscheduleSelector(schedule_selector(NPC::playStand), this);
    accelerated = true;
    if(currentStatus != RoleStatusHurt){
        playWalkAnimate();
    }
}

void NPC::playAttack()
{
    if(currentStatus == RoleStatusAttack || !attackable){
        return;
    }
    currentStatus = RoleStatusAttack;
    stopMove();
    npcRole->stopAllActions();
    CCAnimate *animate = getAnimate(RoleStatusAttack);
    CCSequence *action = CCSequence::create(animate,CCCallFunc::create(this, callfunc_selector(NPC::attackComplete)),NULL);
    npcRole->runAction(action);
    getScheduler()->scheduleSelector(schedule_selector(NPC::startAttack), this, animate->getDuration()/2.0f, false);
    attackable = false;
    getScheduler()->scheduleSelector(schedule_selector(NPC::setAttackableHandler), this, 2, false);
}

void NPC::startAttack()
{
    getScheduler()->unscheduleSelector(schedule_selector(NPC::startAttack), this);
    INSTANCE(FightManager)->npcAttack(this);
    INSTANCE(SoundManager)->playFightAttack();
}

void NPC::attackComplete()
{
    playWalk();
}

void NPC::setAttackableHandler()
{
    getScheduler()->unscheduleSelector(schedule_selector(NPC::setAttackableHandler), this);
    attackable = true;
}

void NPC::playAttackBack()
{
    npcRole->stopAllActions();
    CCAnimate *animate = getAnimate(RoleStatusAttack);
    CCSequence *action = CCSequence::create(animate,CCCallFunc::create(this, callfunc_selector(NPC::attackBackComplete)),NULL);
    npcRole->runAction(action);
    getScheduler()->scheduleSelector(schedule_selector(NPC::startAttackBack), this, 0.3, false);
}

void NPC::startAttackBack()
{
    getScheduler()->unscheduleSelector(schedule_selector(NPC::startAttackBack), this);
    INSTANCE(FightManager)->npcAttack(this);
    INSTANCE(SoundManager)->playFightAttack();
}

void NPC::attackBackComplete()
{
    playWalk();
}

void NPC::runAway(bool speedUp)
{
    getScheduler()->unscheduleSelector(schedule_selector(NPC::runAwayComplete), this);
    if(speedUp){
        //加速换线逃跑
        runAwayStatus = RunAwayStatus_speedUp;
        playWalkAnimate(true);
    }else{
        //减速不换线
        runAwayStatus = RunAwayStatus_speedDown;
        playWalkAnimate();
    }
    
    getScheduler()->scheduleSelector(schedule_selector(NPC::runAwayComplete), this, 2 + INSTANCE(GameUtils)->getRandom(2), false);
}

void NPC::runAwayComplete()
{
    getScheduler()->unscheduleSelector(schedule_selector(NPC::runAwayComplete), this);
    if(!isDead){
        runAwayStatus = RunAwayStatus_none;
        playWalkAnimate();
    }
    
}

void NPC::playWalkAnimate(bool changeY)
{
    this->stopAllActions();
    npcRole->stopAllActions();
    CCAction *action = CCRepeatForever::create(getAnimate(RoleStatusWalk));
    npcRole->runAction(action);
    startMove(changeY);
}

int NPC::getNpcPositionY()
{
    //-250 -190 -130 -70 -10
    float positionY = getPosition().y;
    if(positionY == -250 || positionY == -190 || positionY == -130 || positionY == -70 || positionY == -10){
        return positionY;
    }else{
        positionY = -(int((-10 - positionY)/60)) * 60 - 10;
        return positionY;
    }
}

int NPC::getNpcAttackType()
{
    return npcAttackType;
}

TroopsType NPC::getNpcTroopsType()
{
    return troopsType;
}

int NPC::getNpcAttackPenalty()
{
    return attackPenalty;
}

void NPC::stopAll()
{
    stopAllActions();
    getScheduler()->unscheduleAllForTarget(this);
    npcRole->stopAllActions();
}

CCSprite* NPC::getSprite()
{
    return npcRole;
}

int NPC::getSkillId()
{
    return skillId;
}