//
//  SetBar.cpp
//  threeKingdoms
//  Created by sma11case 14-1-2.
//
//

#include "SetBar.h"
#include "ButtonUtils.h"
#include "CreateCharacterFacade.h"
#include "ChapterFacade.h"
#include "GameSet.h"
#include "Recharge.h"
#include "GuideManager.h"

SetBar::SetBar()
{
    
}

SetBar::~SetBar()
{
    barBg->release();
}

bool SetBar::init()
{
    if(!CCNode::init()){
        return false;
    }
    initContent();
    return true;
}

void SetBar::initContent()
{
    isShow = false;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    
    barBg = CCSprite::createWithSpriteFrameName("fightUI_set_barBg.png");
    barBg->setAnchorPoint(ccp(0.5, 1));
    barBg->setPosition(ccp(0, -10));
    barBg->retain();
    
    setBtn = INSTANCE(ButtonUtils)->createButton("common_setBtn.png",CCSizeMake(75, 81), "");
    barBg->addChild(setBtn);
    setBtn->setPosition(ccp(30, 295));
    setBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(SetBar::openSet), CCControlEventTouchDown);
    
    CCControlButton *btn = INSTANCE(ButtonUtils)->createButton("common_rechargeBtn.png",CCSizeMake(75, 81), "");
    barBg->addChild(btn);
    btn->setPosition(ccp(30, 215));
    btn->addTargetWithActionForControlEvents(this, cccontrol_selector(SetBar::openRecharge), CCControlEventTouchDown);
    
//    btn = INSTANCE(ButtonUtils)->createButton("common_rankBtn.png",CCSizeMake(93, 81), "");
//    barBg->addChild(btn);
//    btn->setPosition(ccp(30, 55));
//    btn->addTargetWithActionForControlEvents(this, cccontrol_selector(SetBar::back), CCControlEventTouchDown);
    
    btn = INSTANCE(ButtonUtils)->createButton("common_chapterBtn.png",CCSizeMake(76, 81), "");
    barBg->addChild(btn);
    btn->setPosition(ccp(30, 135));
    btn->addTargetWithActionForControlEvents(this, cccontrol_selector(SetBar::back), CCControlEventTouchDown);
    
    showBtn = INSTANCE(ButtonUtils)->createButton("fightUI_set_showBtn.png","fightUI_set_hideBtn.png","fightUI_set_hideBtn.png", CCSizeMake(75, 79), "");
    addChild(showBtn);
    showBtn->setZoomOnTouchDown(false);
    showBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(SetBar::showBtnHandler), CCControlEventTouchUpInside);
    
    
}

void SetBar::showBtnHandler()
{
    if(isShow){
        hideBar();
        showBtn->setHighlighted(false);
    }else{
        showBar();
        showBtn->setHighlighted(true);
    }
    isShow = !isShow;
    
    if(INSTANCE(GuideManager)->getIsGuiding() && INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10009){
        INSTANCE(GuideManager)->goToNext();
    }
}

void SetBar::showBar()
{
    if(!barBg->getParent()){
        addChild(barBg,-1);
        INSTANCE(GuideManager)->registerPosition(GuideStep_10010, setBtn->getParent()->convertToWorldSpace(setBtn->getPosition()));
    }
}

void SetBar::hideBar()
{
    barBg->removeFromParent();
}

void SetBar::openSet()
{
    showBtnHandler();
    INSTANCE(GameSetFacade)->openGameSet(true);
    if(INSTANCE(GuideManager)->getIsGuiding() && INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10010){
        INSTANCE(GuideManager)->goToNext();
    }
}

void SetBar::openRecharge()
{
    showBtnHandler();
    INSTANCE(RechargeFacade)->open();
}

void SetBar::back()
{
    showBtnHandler();
//    INSTANCE(CreateCharacterFacade)->openCreateCharacterScene();
    INSTANCE(ChapterFacade)->openChapterScene();
}

void SetBar::onExit()
{
    CCNode::onExit();
}

void SetBar::onEnter()
{
    CCNode::onEnter();
    INSTANCE(GuideManager)->registerPosition(GuideStep_10009, showBtn->getParent()->convertToWorldSpace(showBtn->getPosition()));
    
}