//
//  SingleCharacter.cpp
//  threeKingdoms
//
//  Created by .m on 14-1-2.
//
//

#include "SingleCharacter.h"
#include "EventManager.h"
#include "GameUtils.h"
#include "FightManager.h"
#include "UserData.h"
#include "RoleRule.h"
#include "AnimationUtils.h"
#include "ButtonUtils.h"
#include "MessageBox.h"
#include "NoticeBox.h"
#include "StringUtils.h"

SingleCharacter * SingleCharacter::create(int roleId){
    SingleCharacter *singleCharacter = new SingleCharacter(roleId);
    if(singleCharacter && singleCharacter->init()){
        singleCharacter->autorelease();
        return singleCharacter;
    }else{
        delete singleCharacter;
        singleCharacter = NULL;
        return NULL;
    }
}

SingleCharacter::SingleCharacter(int roleId)
{
    this->roleId = roleId;
}

SingleCharacter::~SingleCharacter()
{
    
}

bool SingleCharacter::init()
{
    if(!CCSprite::initWithSpriteFrameName(getFrameName(roleId,FrameType_role).c_str()))
    {
        return false;
    }
    setAnchorPoint(INSTANCE(RoleRule)->getRoleAnchorPoint(roleId));
    initContent();
    setColor(ccBLACK);
    return true;
}

string SingleCharacter::getFrameName(int roleId,FrameType type)
{
    string result;
    switch (type) {
        case FrameType_role:
//            result = CCString::createWithFormat("createCharacter_role_%d.png",roleId)->getCString();
            result = INSTANCE(RoleRule)->getRoleFirstFrameNameByRoleId(roleId, RoleStatusStand);
            break;
        case FrameType_lightEffect:
            result = getLightEffect(roleId);
            break;
        case FrameType_name:
            result = "createCharacter_roleName.png";
            break;
        default:
            break;
    }
    return result;
}

string SingleCharacter::getLightEffect(int roleId)
{
    string result;
    switch (roleId) {
        case 20003:
            result = "createCharacter_lightEffect_purple.png";
            break;
        case 20002:
            result = "createCharacter_lightEffect_blue.png";
            break;
        case 20005:
            result = "createCharacter_lightEffect_yellow.png";
            break;
        case 20001:
            result = "createCharacter_lightEffect_red.png";
            break;
        default:
            break;
    }
    return result;
}

void SingleCharacter::initContent()
{
    lightEffect = CCSprite::createWithSpriteFrameName(getFrameName(roleId, FrameType_lightEffect).c_str());
    addChild(lightEffect,-1);
    lightEffect->setPosition(ccpAdd(getAnchorPointInPoints(),ccp(0, 0)));
    INSTANCE(EventManager)->addEventListener(this, this, callfuncO_selector(SingleCharacter::click),true,ccp(0.2, 0.4),ccp(0, 100));
    selectedFlag = CCSprite::createWithSpriteFrameName("createCharacter_selectedFlag.png");
    addChild(selectedFlag,-1);
    selectedFlag->setPosition(ccpAdd(getAnchorPointInPoints(),ccp(0, 150)));
    selectedFlag->setVisible(false);
    
    roleName = CCSprite::createWithSpriteFrameName(getFrameName(roleId, FrameType_name).c_str());
    addChild(roleName);
    roleName->setPosition(ccpAdd(getAnchorPointInPoints(),ccp(0, -40)));
    roleName->setVisible(false);
    
    CCLabelTTF *name = CCLabelTTF::create();
    name->setFontSize(22);
    name->setString(INSTANCE(RoleRule)->getRoleName(roleId).c_str());
    roleName->addChild(name);
    name->setPosition(getCenterPosition(roleName));
    
    setColor(ccBLACK);
    lightEffect->setColor(ccBLACK);
    
    if(!INSTANCE(RoleRule)->ownRole(roleId)){
        int needVip = INSTANCE(RoleRule)->getRoleVip(roleId);
        int goldCost = INSTANCE(RoleRule)->getRoleCost(roleId);
        
        if(goldCost == 0 && needVip != 0){
            //vip限制
            buyBtn = INSTANCE(ButtonUtils)->createButton("createCharacter_vipBtn_1.png", "createCharacter_vipBtn_2.png", "createCharacter_vipBtn_2.png", CCSizeMake(114, 40), "vip开放",22,ccYELLOW);
        }else if(needVip == 0 && goldCost != 0){
            //金币购买
            buyBtn = INSTANCE(ButtonUtils)->createButton("createCharacter_buyBtn_1.png", "createCharacter_buyBtn_2.png", "createCharacter_buyBtn_2.png", CCSizeMake(114, 40), CCString::createWithFormat("%s元宝",INSTANCE(StringUtils)->numToString(goldCost).c_str())->getCString(),22,ccYELLOW);
        }
        
        addChild(buyBtn,-1);
        buyBtn->setPosition(ccpAdd(getAnchorPointInPoints(),ccp(0, 225)));
        buyBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(SingleCharacter::buy), CCControlEventTouchUpInside);
    }
}

void SingleCharacter::click(cocos2d::CCObject *object)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/createCharacter/createCharacter.plist");
    CCNotificationCenter::sharedNotificationCenter()->postNotification(UnselectAllSingleCharacter);
    setSelect(true);
    INSTANCE(UserData)->setCurrentRoleId(roleId);
}

void SingleCharacter::buy()
{
    if(!INSTANCE(RoleRule)->ownRole(roleId)){
        int needVip = INSTANCE(RoleRule)->getRoleVip(roleId);
        int goldCost = INSTANCE(RoleRule)->getRoleCost(roleId);
        string roleName = INSTANCE(RoleRule)->getRoleName(roleId);
        if(needVip == 0 && goldCost != 0){
            INSTANCE(MessageBoxFacade)->showMessageBox(CCString::createWithFormat("是否花费%d元宝购买%s",goldCost,roleName.c_str())->getCString(), this, callfunc_selector(SingleCharacter::buyHandler));
        }else{
            INSTANCE(NoticeBoxFacade)->showNoticeBox(CCString::createWithFormat("vip开放%s",roleName.c_str())->getCString());
        }
    }
}

void SingleCharacter::buyHandler()
{
    
    int cost = INSTANCE(RoleRule)->getRoleCost(roleId);
    if(INSTANCE(UserData)->getCurrentMoney() >= cost){
        INSTANCE(UserData)->costCurrentMoney(cost);
        INSTANCE(UserData)->addRole(roleId);
        buyBtn->removeFromParent();
    }else{
        INSTANCE(NoticeBoxFacade)->showNoticeBox("元宝不足");
    }
    
}

void SingleCharacter::setSelect(bool select)
{
    if(select){
        selectedFlag->setVisible(true);
        roleName->setVisible(true);
        setColor(ccWHITE);
        lightEffect->setColor(ccWHITE);
        CCAnimate *animate = INSTANCE(AnimationUtils)->getModelAnimate(roleId, RoleStatusSkill, 0.1);
        runAction(CCSequence::create(animate,CCCallFunc::create(this, callfunc_selector(SingleCharacter::skillComplete)),NULL));
    }else{
        selectedFlag->setVisible(false);
        roleName->setVisible(false);
        setColor(ccBLACK);
        lightEffect->setColor(ccBLACK);
        stopAllActions();
        setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(INSTANCE(RoleRule)->getRoleFirstFrameNameByRoleId(roleId, RoleStatusStand).c_str()));
    }
}

void SingleCharacter::skillComplete()
{
    stopAllActions();
    CCAnimate *animate = INSTANCE(AnimationUtils)->getModelAnimate(roleId, RoleStatusStand, 0.1);
    runAction(CCRepeatForever::create(animate));
}

int SingleCharacter::getRoleId()
{
    return roleId;
}
