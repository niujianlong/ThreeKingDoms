//
//  Recharge.cpp
//  threeKingdoms
//  Created by sma11case on 14-2-7.
//
//

#include "Recharge.h"
#include "CommonBg.h"
#include "ButtonUtils.h"
#include "ChapterFacade.h"
#include "SingleRecharge.h"
#include "FightManager.h"
#include "NPCManager.h"
#include "BossLottery.h"
#include "SceneManager.h"
#include "RechargeRule.h"

Recharge::Recharge()
{
    
}

Recharge::~Recharge()
{
    
}

bool Recharge::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    initContent();
    return true;
}

void Recharge::initContent()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    addChild(CommonBg::create("元宝商城"));
    CCControlButton *backBtn = INSTANCE(ButtonUtils)->createButton("common_backBtn.png", CCSizeMake(75, 81), "");
    backBtn->setPosition(ccp(winSize.width/2 - 60, 260));
    
    backBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(Recharge::closeHandler), CCControlEventTouchUpInside);
    addChild(backBtn);
    
    moneyBar = CommonMoneyBar::create();
    addChild(moneyBar);
    moneyBar->setPosition(ccp( 60 - winSize.width/2, 60 - winSize.height/2));
    
    CCLayer *layer = CCLayer::create();
    
    CCScrollView *scrollView = CCScrollView::create();
    scrollView->setContainer(layer);
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);
    addChild(scrollView);
    scrollView->setPosition(ccp(-winSize.width/2 + 5, -100));
    
    int rechargeType;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    rechargeType = 1;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    rechargeType = 2;
#endif
    
    vector<int> rechargeIdVector = INSTANCE(RechargeRule)->getRechargeIdByType(rechargeType);

    int w = winSize.width == 1136? 233:189;
    for(int i=0;i<rechargeIdVector.size();i++){
        SingleRecharge *singleRecharge = SingleRecharge::create(rechargeIdVector[i]);
        layer->addChild(singleRecharge);
        
        singleRecharge->setPosition(ccp(98 + w * i, 100));
    }
    
    scrollView->setViewSize(CCSizeMake(winSize.width - 10, 400));
    scrollView->setContentSize(CCSizeMake(w*rechargeIdVector.size(), scrollView->getViewSize().height));
    
    CCLabelTTF *noticeLabel = CCLabelTTF::create();
    noticeLabel->setFontSize(28);
    noticeLabel->setColor(ccYELLOW);
    noticeLabel->setString("充值即可成为VIP会员，选择诸葛先生征战VIP专属战场。");
    
    noticeLabel->setAnchorPoint(ccp(0, 0.5));
    noticeLabel->setPosition(ccp(60 - winSize.width/2, -140));
    addChild(noticeLabel);
}

void Recharge::onEnter()
{
    ADD_TOUCH;
    CCLayer::onEnter();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    setPosition(ccp(winSize.width/2, winSize.height/2));
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(moneyBar, callfuncO_selector(CommonMoneyBar::updateBar), Recharge_Notice, NULL);
}

void Recharge::onExit()
{
    REMOVE_TOUCH;
    CCLayer::onExit();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(moneyBar, Recharge_Notice);
}

bool Recharge::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void Recharge::closeHandler()
{
    this->removeFromParent();
    if(!INSTANCE(BossLotteryFacade)->getLotteryStatus()){
        INSTANCE(FightManager)->resumeFight();
    }
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
}


bool RechargeFacade::init()
{
    return true;
}

void RechargeFacade::open()
{
    if(!INSTANCE(BossLotteryFacade)->getLotteryStatus()){
        INSTANCE(FightManager)->pauseFight();
    }
    INSTANCE(SceneManager)->addToCurrentScene(Recharge::create(), zOrder_notice);
}

