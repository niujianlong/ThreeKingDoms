//
//  GoldPot.cpp
//  threeKingdoms
//
//  Created by .m on 14-2-12.
//
//

#include "GoldPot.h"
#include "SceneManager.h"
#include "SystemConfigRule.h"
#include "MoneyLayer.h"
#include "GameUtils.h"
#include "AnimateManager.h"
#include "UserData.h"
#include "FightManager.h"

bool GoldPot::init()
{
    if(!CCNode::init()){
        return false;
    }
    initContent();
    return true;
}

void GoldPot::initContent()
{
    gainGold = INSTANCE(SystemConfigRule)->getCurrentTreasureBowlWinnings();
    CCSprite *pot  = CCSprite::create("common/goldPot.png");
    addChild(pot);
    
    INSTANCE(UserData)->setPotGold(0);
    INSTANCE(UserData)->addCurrentMoney(gainGold);
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdatePot);
}

void GoldPot::onEnter()
{
    CCNode::onEnter();
    setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    
    INSTANCE(AnimateManager)->showScaleAnimate(this);
    
    INSTANCE(MoneyLayerManager)->createMoney(gainGold,ccp(0, 0));
}

void GoldPot::onExit()
{
    CCNode::onExit();
}


bool GoldPotFacade::init()
{
    return true;
}

void GoldPotFacade::showGoldPot()
{
    INSTANCE(SceneManager)->addToCurrentScene(GoldPot::create(), zOrder_notice);
}
