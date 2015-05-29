//
//  BaseRole.cpp
//  threeKingdoms
//
//  Created by .m on 13-12-24.
//
//

#include "BaseRole.h"
#include "AnimationUtils.h"
#include "JoyStickLayer.h"
#include "FightManager.h"
#include "SoundManager.h"
#include "SkillRule.h"
#include "FightSceneFacade.h"
#include "TitleRule.h"
#include "UserData.h"
#include "GuideManager.h"
#include "MessageBox.h"
#include "Recharge.h"
#include "MoneyLayer.h"

BaseRole* BaseRole::create(int roleId)
{
    BaseRole* role = new BaseRole(roleId);
    if(role && role->init()){
        role->autorelease();
        return role;
    }else{
        delete role;
        role = NULL;
        return NULL;
    }
}


BaseRole::BaseRole(int roleId){
    this->roleId = roleId;
    currentRoleDirection = RoleDirection_right;
    currentRoleStatus = RoleStatusNone;
    speedX = float(INSTANCE(RoleRule)->getRoleSpeed(roleId))*(1.0f+INSTANCE(TitleRule)->getTitleSpeedAddition(INSTANCE(UserData)->getTitleLevel()));
    speedY = speedX * 2 / 3;
    attackSpeed = INSTANCE(RoleRule)->getRoleAttackSpeed(roleId)*(1.0f-INSTANCE(TitleRule)->getTitleAttackAddition(INSTANCE(UserData)->getTitleLevel()));
    speedCoefficient = 0.6;
}

BaseRole::~BaseRole()
{
    
}

bool BaseRole::init()
{
    if(!CCNode::init()){
        return false;
    }
    
    evenStrokes = INSTANCE(TitleRule)->getEvenStrokes(INSTANCE(UserData)->getTitleLevel());
    initRole();
    
    return true;
}

void BaseRole::onEnter()
{
    CCNode::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BaseRole::joyStickHandler), JoyStick_status, NULL);
}

void BaseRole::onExit()
{
    CCNode::onExit();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, JoyStick_status);
}


void BaseRole::initRole()
{
    string img = INSTANCE(RoleRule)->getRoleImgPath(roleId);
    img.append(INSTANCE(RoleRule)->getRoleFrameNameByRoleId(roleId, RoleStatusStand));
    img.append(".plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(img.c_str());
    img = INSTANCE(RoleRule)->getRoleFirstFrameNameByRoleId(roleId, RoleStatusStand);
    role = CCSprite::createWithSpriteFrameName(img.c_str());
    addChild(role);
    role->setAnchorPoint(INSTANCE(RoleRule)->getRoleAnchorPoint(roleId));
    CCSprite *shadow = CCSprite::create("fightImg/role_shadow.png");
    role->addChild(shadow,-1);
    shadow->setPosition(role->getAnchorPointInPoints());
    playStand();
    
    CCSprite *arrow = CCSprite::create();
    CCAnimation *animation = INSTANCE(AnimationUtils)->getCommonAnimation("fightImg/roleArrow.plist", "roleArrow");
    CCAction *action = CCRepeatForever::create(CCAnimate::create(animation));
    arrow->runAction(action);
    addChild(arrow);
    arrow->setPosition(ccp(0, 250));
}


void BaseRole::setRolePosition(cocos2d::CCPoint p)
{
    if(isAttacking() || currentRoleStatus == RoleStatusSkill){
        return;
    }
    if(p.x <0){
        currentRoleDirection = RoleDirection_left;
        role->setFlipX(true);
    }else{
        currentRoleDirection = RoleDirection_right;
        role->setFlipX(false);
    }
    
    CCPoint nP = ccpAdd(getPosition(), p);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    float _x;
    float _y;
    
    if(nP.y >20 || nP.y <-280){
        _y = getPositionY();
    }else{
        _y = nP.y;
    }
    
    if(nP.x >= winSize.width/2 || nP.x <= -winSize.width/2){
        _x = getPositionX();
    }else{
        _x = nP.x;
    }
    setPosition(ccp(_x, _y));
    playRun();
    
    if(INSTANCE(GuideManager)->getIsGuiding() && INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10002){
        CCPoint tp = getParent()->convertToWorldSpace(nP);
        CCRect r = CCRectMake(winSize.width/2 - 140, 180, 80, 40);
        if(r.containsPoint(tp)){
            INSTANCE(GuideManager)->goToNext();
        }
    }
}

void BaseRole::joyStickHandler(cocos2d::CCString *direction)
{
    if(currentRoleStatus == RoleStatusHurt){
        return;
    }
    if(strcmp(direction->getCString(),JoyStick_up) == 0){
        setRolePosition(ccp(0, speedY));
    }else if(strcmp(direction->getCString() , JoyStick_down) == 0){
        setRolePosition(ccp(0, -speedY));
    }else if(strcmp(direction->getCString() , JoyStick_right) == 0){
        setRolePosition(ccp(speedX, 0));
    }else if(strcmp(direction->getCString() , JoyStick_left) == 0){
        setRolePosition(ccp(-speedX, 0));
    }else if(strcmp(direction->getCString() , JoyStick_right_down) == 0){
        setRolePosition(ccp(speedX * speedCoefficient, -speedY * speedCoefficient));
    }else if(strcmp(direction->getCString() , JoyStick_right_up) == 0){
        setRolePosition(ccp(speedX * speedCoefficient, speedY * speedCoefficient));
    }else if(strcmp(direction->getCString() , JoyStick_left_down) == 0){
        setRolePosition(ccp(-speedX * speedCoefficient, -speedY * speedCoefficient));
    }else if(strcmp(direction->getCString() , JoyStick_left_up) == 0){
        setRolePosition(ccp(-speedX * speedCoefficient, speedY * speedCoefficient));
    }else if(strcmp(direction->getCString() , JoyStick_skill) == 0){
            playSkill();
    }else if(strcmp(direction->getCString() , JoyStick_attack) == 0){
//        if(INSTANCE(FightManager)->enoughMoney()){
            playAttack();
//        }else{
//            //变色
//        }
    }else if(strcmp(direction->getCString() , JoyStick_none) == 0){
        if(!isAttacking() && currentRoleStatus != RoleStatusSkill){
            playStand();
        }
    }
}

void BaseRole::playRun()
{
    if(currentRoleStatus == RoleStatusRun){
        return;
    }
    currentRoleStatus = RoleStatusRun;
    
    role->stopAllActions();
    CCAction *action = CCRepeatForever::create(getAnimate(RoleStatusRun,0.07));
    role->runAction(action);
}

void BaseRole::playStand()
{
    if(currentRoleStatus == RoleStatusStand){
        return;
    }
    
    role->stopAllActions();
    CCAction *action = CCRepeatForever::create(getAnimate(RoleStatusStand));
    currentRoleStatus = RoleStatusStand;
    role->runAction(action);
}

void BaseRole::playAttack()
{
    RoleStatus status = currentRoleStatus;
    evenStrokes = INSTANCE(FightManager)->getEvenStrokes();
    if(currentRoleStatus == RoleStatusSkill){
        return;
    }
    if(isAttacking()){
        if(attackCompleted){
            if(currentRoleStatus == RoleStatusAttack_1){
                currentRoleStatus = RoleStatusAttack_2;
            }else if(currentRoleStatus == RoleStatusAttack_2){
                currentRoleStatus = RoleStatusAttack_3;
            }else if(currentRoleStatus == RoleStatusAttack_3){
                currentRoleStatus = RoleStatusAttack_4;
            }else if(currentRoleStatus == RoleStatusAttack_4){
                currentRoleStatus = RoleStatusAttack_5;
            }else if(currentRoleStatus == RoleStatusAttack_5){
                return;
            }
        }else{
            return;
        }
    }else{
        currentRoleStatus = RoleStatusAttack_1;
    }
    INSTANCE(FightManager)->setAttackMultiple(getAttackMultiple());
    if(!INSTANCE(FightManager)->enoughMoney()){
        currentRoleStatus = status;
        INSTANCE(FightManager)->setAttackMultiple(1);
        INSTANCE(MessageBoxFacade)->showMessageBox("元宝很少了？去看看我们准备的更多元宝吧", INSTANCE(RechargeFacade), callfunc_selector(RechargeFacade::open));
        return;
    }
    
    attackCompleted = false;
    
    role->stopAllActions();

    CCAnimate *animate = getAnimate(currentRoleStatus,attackSpeed);
    CCAction *action = CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(BaseRole::attackComplete)),NULL);
    role->runAction(action);
    
    this->getScheduler()->scheduleSelector(schedule_selector(BaseRole::startAttack), this, animate->getDuration()/2.0f, false);
    this->getScheduler()->scheduleSelector(schedule_selector(BaseRole::allowNextAttack), this, animate->getDuration()-0.1, false);
//    playEffect(RoleStatusAttackEffect);
    
    if(INSTANCE(GuideManager)->getIsGuiding() && INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10003){
        INSTANCE(GuideManager)->goToNext();
    }
}

void BaseRole::startAttack()
{
    INSTANCE(SoundManager)->playFightAttack();
    this->getScheduler()->unscheduleSelector(schedule_selector(BaseRole::startAttack), this);
    INSTANCE(FightManager)->roleAttack_new(getAttackMultiple());
    
}

void BaseRole::attackComplete()
{
    playStand();
    
}

void BaseRole::allowNextAttack()
{
    this->getScheduler()->unscheduleSelector(schedule_selector(BaseRole::allowNextAttack), this);
    if(evenStrokes == 1 && currentRoleStatus == RoleStatusAttack_1){
        attackCompleted = false;
    }else if(evenStrokes == 2 && currentRoleStatus == RoleStatusAttack_2){
        attackCompleted = false;
    }else if(evenStrokes == 3 && currentRoleStatus == RoleStatusAttack_3){
        attackCompleted = false;
    }else if(evenStrokes == 4 && currentRoleStatus == RoleStatusAttack_4){
        attackCompleted = false;
    }else if(evenStrokes == 5 && currentRoleStatus == RoleStatusAttack_5){
        attackCompleted = false;
    }else{
        attackCompleted = true;
    }
    
}

void BaseRole::playEffect(RoleStatus status)
{
    string img = INSTANCE(RoleRule)->getRoleImgPath(roleId);
    img.append(INSTANCE(RoleRule)->getRoleFrameNameByRoleId(roleId, status));
    img.append(".plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(img.c_str());
    CCSprite *attackEffect = CCSprite::createWithSpriteFrameName(INSTANCE(RoleRule)->getRoleFirstFrameNameByRoleId(roleId, status).c_str());
    CCAction *action = CCSequence::create(getAnimate(status),CCCallFuncN::create(attackEffect, callfuncN_selector(CCSprite::removeFromParent)),NULL);
    
    role->addChild(attackEffect);
    if(currentRoleDirection == RoleDirection_left){
        attackEffect->setFlipX(true);
    }else{
        attackEffect->setFlipX(false);
    }
    if(status == RoleStatusSkillEffect){
        attackEffect->setAnchorPoint(INSTANCE(RoleRule)->getRoleSkillEffectAnchorPoint(roleId));
    }else{
        attackEffect->setAnchorPoint(INSTANCE(RoleRule)->getRoleAttackEffectAnchorPoint(roleId));
    }
    
    attackEffect->setPosition(role->getAnchorPointInPoints());
    attackEffect->runAction(action);
}

void BaseRole::playSkill()
{
    if(currentRoleStatus == RoleStatusSkill || isAttacking()){
        return;
    }
    currentRoleStatus = RoleStatusSkill;
    
    role->stopAllActions();
    
    CCAction *action = CCSequence::create(getAnimate(RoleStatusSkill),CCCallFuncN::create(this, callfuncN_selector(BaseRole::skillComplete)),NULL);
    role->runAction(action);
    
    if(roleId != 20005){
        this->getScheduler()->scheduleSelector(schedule_selector(BaseRole::startSkill), this, 0.1 * INSTANCE(RoleRule)->getRoleSkillFrameNum(roleId), false);
    }else{
        this->getScheduler()->scheduleSelector(schedule_selector(BaseRole::startSkill), this, 1.0f, false);

    }
    playEffect(RoleStatusSkillEffect);
    INSTANCE(FightSceneFacade)->showSkillHit(getSkillId());
    INSTANCE(SoundManager)->playFightSkill(getSkillId());
    INSTANCE(FightManager)->setAttackMultiple(1);
}

void BaseRole::skillComplete()
{
    playStand();
}

void BaseRole::startSkill()
{
    INSTANCE(SoundManager)->playFightAttack();
    INSTANCE(FightManager)->roleSkill();
    this->getScheduler()->unscheduleSelector(schedule_selector(BaseRole::startSkill), this);
}

CCAnimate* BaseRole::getAnimate(RoleStatus status, float duration)
{
    string img = INSTANCE(RoleRule)->getRoleFrameNameByRoleId(roleId, status);
    
    CCAnimation *animation = INSTANCE(AnimationUtils)->getModelAnimation(INSTANCE(RoleRule)->getRoleModelId(roleId),img.c_str(), img.c_str(),duration);
    CCAnimate *animate = CCAnimate::create(animation);
    return animate;
}

RoleDirection BaseRole::getRoleDirection()
{
    return currentRoleDirection;
}

CCRect BaseRole::getAttackRect()
{
    CCSize size = INSTANCE(RoleRule)->getRoleAttackSize(roleId);
    
    if(currentRoleDirection == RoleDirection_left){
        return CCRectMake(getPositionX() - size.width, getPositionY() - size.height/2, size.width, size.height);
    }else{
        return CCRectMake(getPositionX(), getPositionY() - size.height/2, size.width, size.height);
    }
}

CCRect BaseRole::getHurtRect()
{
    CCSize size = INSTANCE(RoleRule)->getRoleHurtSize(roleId);
    return CCRectMake(getPositionX() - size.width/2, getPositionY() - size.height/2, size.width, size.height);
}

int BaseRole::getRoleId()
{
    return roleId;
}

int BaseRole::getSkillCost()
{
    return INSTANCE(SkillRule)->getSkillCost(INSTANCE(RoleRule)->getRoleSkillId(roleId));
}

int BaseRole::getSkillId()
{
    return INSTANCE(RoleRule)->getRoleSkillId(roleId);
}

int BaseRole::getRow()
{
    return INSTANCE(FightManager)->getRow(getPositionY());
}


bool BaseRole::isAttacking()
{
    if(currentRoleStatus == RoleStatusAttack_1 || currentRoleStatus == RoleStatusAttack_2 || currentRoleStatus == RoleStatusAttack_3 || currentRoleStatus == RoleStatusAttack_4 || currentRoleStatus == RoleStatusAttack_5){
        return true;
    }
    return false;
}

int BaseRole::getAttackMultiple()
{
    if(currentRoleStatus == RoleStatusAttack_1){
        return 1;
    }else if(currentRoleStatus == RoleStatusAttack_2){
        return 2;
    }else if(currentRoleStatus == RoleStatusAttack_3){
        return 3;
    }else if(currentRoleStatus == RoleStatusAttack_4){
        return 4;
    }else if(currentRoleStatus == RoleStatusAttack_5){
        return 5;
    }
    return 0;
}

void BaseRole::playHurt(int attackPenalty)
{
    if(currentRoleStatus == RoleStatusHurt || currentRoleStatus == RoleStatusSkill){
        return;
    }
    this->getScheduler()->unscheduleSelector(schedule_selector(BaseRole::startAttack), this);
    currentRoleStatus = RoleStatusHurt;
    role->stopAllActions();
    CCAnimate *animate = getAnimate(RoleStatusHurt);
    CCAction *action = CCSequence::create(animate,CCDelayTime::create(0.1),CCCallFuncN::create(this, callfuncN_selector(BaseRole::hurtComplete)),NULL);
    role->runAction(action);
    INSTANCE(SoundManager)->playFightHurt();
    
    INSTANCE(FightManager)->addMoney(-attackPenalty);
    INSTANCE(MoneyLayerManager)->createReduceMoney(attackPenalty * INSTANCE(FightManager)->getCurrentRate());
}

void BaseRole::hurtComplete()
{
    playStand();
}
