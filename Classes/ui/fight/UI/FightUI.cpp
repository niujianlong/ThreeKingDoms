//
//  FightUI.cpp
//  threeKingdoms
//  Created by sma11case 13-12-27.
//
//

#include "FightUI.h"
#include "JoyStickLayer.h"
#include "ButtonUtils.h"
#include "GameUtils.h"
#include "StringUtils.h"
#include "FightManager.h"
#include "SystemConfigRule.h"
#include "TitleRule.h"
#include "SetBar.h"
#include "UserData.h"
#include "LevelUp.h"
#include "GuideManager.h"
#include "EventManager.h"
#include "Recharge.h"

FightUI::FightUI()
{
//    currentRate = INSTANCE(FightManager)->getCurrentRate();
    currentMoney = INSTANCE(UserData)->getCurrentMoney();
    currentIntegral = INSTANCE(UserData)->getCurrentIntegral();
    maxRate = INSTANCE(SystemConfigRule)->getMaxMagnification();
    differenceMoney = 0;
}

FightUI::~FightUI()
{
    
}

bool FightUI::init()
{
    if(!CCLayer::init()){
        return false;
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/fightUI/fightUI.plist");
    initContent();
    return true;
}

void FightUI::onEnter()
{
    CCLayer::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(FightUI::updateMoney), NoticeUpdateMoney, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(FightUI::updateIntegral), NoticeUpdateIntegral, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(FightUI::updatePot), NoticeUpdatePot, NULL);
    
    updateIntegral();
    
    scheduleUpdate();
    
    INSTANCE(GuideManager)->registerPosition(GuideStep_10004, ccpAdd(moneyLabel->getParent()->convertToWorldSpace(moneyLabel->getPosition()), ccp(50, 0)));

}

void FightUI::onExit()
{
    CCLayer::onExit();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NoticeUpdateMoney);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NoticeUpdateIntegral);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NoticeUpdatePot);
}

void FightUI::initContent()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *bottomBar = CCSprite::createWithSpriteFrameName("fightUI_bottomBar.png");
    addChild(bottomBar);
    bottomBar->setPosition(ccp(0, (bottomBar->getContentSize().height - winSize.height) / 2));
    
    titleBar = CommonTitleBar::create();
    titleBar->setPosition(ccp(60 - winSize.width/2, winSize.height/2 - 60));
    addChild(titleBar);
    INSTANCE(EventManager)->addEventListener(titleBar->getEventNode(), this, callfuncO_selector(FightUI::showExpTips));
    
    potSprite = CCSprite::createWithSpriteFrameName("fightUI_pot_gray.png");
    addChild(potSprite);
    potSprite->setPosition(ccp(340 - winSize.width/2, winSize.height/2 - 60));
    
    INSTANCE(EventManager)->addEventListener(potSprite, this, callfuncO_selector(FightUI::showPotTips));
    
    int currentPot = INSTANCE(UserData)->getPotWinning();
    int max = INSTANCE(SystemConfigRule)->getCurrentTreasureBowlWinnings();
    
    potBar = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("fightUI_pot.png"));
    potSprite->addChild(potBar);
    potBar->setPosition(getCenterPosition(potSprite));
    potBar->setType(kCCProgressTimerTypeBar);
    potBar->setBarChangeRate(ccp(0, 1));
    potBar->setMidpoint(ccp(0, 0));
    potBar->setPercentage(((float)currentPot)/max * 100);
    
    potLabel = CCLabelTTF::create();
    potLabel->setFontSize(24);
    potLabel->setColor(ccGREEN);
    potSprite->addChild(potLabel);
    potLabel->setPosition(ccp(potSprite->getContentSize().width/2,potSprite->getContentSize().height/2));
    potLabel->setString(CCString::createWithFormat("%d/%d",currentPot,max)->getCString());
    
    updatePot();
    
    CCSprite *barFrame2 = CCSprite::createWithSpriteFrameName("fightUI_barFrame_2.png");
    addChild(barFrame2);
    barFrame2->setPosition(ccp( 20, 80 - winSize.height/2));
    
    moneyBar = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("fightUI_redBar.png"));
    barFrame2->addChild(moneyBar);
    moneyBar->setPosition(ccp(barFrame2->getContentSize().width/2,barFrame2->getContentSize().height/2));
    moneyBar->setType(kCCProgressTimerTypeBar);
    moneyBar->setBarChangeRate(ccp(1, 0));
    moneyBar->setMidpoint(ccp(0, 0));
    moneyBar->setPercentage(((float)currentMoney)/9999 * 100);
    
    moneyLabel = CCLabelBMFont::create(INSTANCE(StringUtils)->intToString(currentMoney).c_str(), "font/font_yellowNum.fnt");
    barFrame2->addChild(moneyLabel);
    moneyLabel->setPosition(ccpAdd(getCenterPosition(barFrame2),ccp(0,-5)));
    
    CCSprite *icon2 = CCSprite::createWithSpriteFrameName("fightUI_moneyIcon.png");
    barFrame2->addChild(icon2);
    icon2->setPosition(ccp(20, barFrame2->getContentSize().height/2));
    
    INSTANCE(EventManager)->addEventListener(icon2, INSTANCE(RechargeFacade), callfuncO_selector(RechargeFacade::open));
    
    JoyStickLayer *joyStickLayer = JoyStickLayer::create();
    addChild(joyStickLayer);
    
    setBar = SetBar::create();
    setBar->setPosition(ccp(winSize.width/2 - 40, 280));
    addChild(setBar);
    
    onlineReward = OnlineReward::create();
    addChild(onlineReward);
    onlineReward->setPosition(ccp(140 - winSize.width/2, winSize.height/2 - 110));
}

void FightUI::updateMoney()
{
    differenceMoney += INSTANCE(UserData)->getCurrentMoney() - currentMoney;
    currentMoney = INSTANCE(UserData)->getCurrentMoney();
    moneyBar->setPercentage(((float)currentMoney)/9999 * 100);
}

void FightUI::showMoneyAnimation()
{
    if(differenceMoney == 0){
        return;
    }
    if(differenceMoney < 0){
        if(differenceMoney <= -50000){
            differenceMoney+=22222;
        }else if(differenceMoney <= -5000){
            differenceMoney+=2222;
        }else if(differenceMoney <= -500){
            differenceMoney+=111;
        }else if(differenceMoney <= -50){
            differenceMoney+=11;
        }else{
            differenceMoney++;
        }
        
    }else{
        if(differenceMoney >= 50000){
            differenceMoney-=22222;
        }else if(differenceMoney >= 5000){
            differenceMoney-=2222;
        }else if(differenceMoney >= 500){
            differenceMoney-=111;
        }else if(differenceMoney >= 50){
            differenceMoney-=11;
        }else{
            differenceMoney--;
        }
    }
    moneyLabel->setString(INSTANCE(StringUtils)->intToString(currentMoney - differenceMoney).c_str());
    
}

void FightUI::updateIntegral()
{
    int lastTitleLevel = INSTANCE(TitleRule)->getTitleLevelByIntegral(currentIntegral);
    currentIntegral = INSTANCE(UserData)->getCurrentIntegral();
    int currentTitleLevel = INSTANCE(UserData)->getTitleLevel();
    titleBar->updateBar();
    if(currentTitleLevel > lastTitleLevel){
        INSTANCE(LevelUpFacade)->showLevelUp(currentTitleLevel);
    }
}

void FightUI::update(float t)
{
    showMoneyAnimation();
    
    if(INSTANCE(GuideManager)->getIsGuiding()){
        potSprite->setVisible(false);
        if(INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10008){
            onlineReward->setVisible(true);
        }else{
            onlineReward->setVisible(false);
        }
        
        if(INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10009 || INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10010|| INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10011|| INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10012){
            setBar->setVisible(true);
            onlineReward->setVisible(true);
        }else{
            setBar->setVisible(false);
        }
        
        INSTANCE(BossAvatarFacade)->setAvatarVisible(false);
    }else{
        potSprite->setVisible(true);
        onlineReward->setVisible(true);
        setBar->setVisible(true);
        INSTANCE(BossAvatarFacade)->setAvatarVisible(true);
    }
}

void FightUI::updatePot()
{
    int currentPot = INSTANCE(UserData)->getPotWinning();
    int max = INSTANCE(SystemConfigRule)->getCurrentTreasureBowlWinnings();
    
    if(max - currentPot <=100){
        potLabel->setColor(ccGREEN);
    }else{
        potLabel->setColor(ccRED);
    }
    potBar->setPercentage(((float)currentPot)/max * 100);
    potLabel->setString(CCString::createWithFormat("%d/%d",currentPot,max)->getCString());
}

void FightUI::showExpTips()
{
    INSTANCE(TipsManager)->showTips("升级能开启高倍场景和连招(连招越多，消耗越大，得到的奖励也越高)", titleBar->getParent()->convertToWorldSpace(titleBar->getPosition()));
}

void FightUI::showPotTips()
{
    INSTANCE(TipsManager)->showTips("聚宝盆存满时，击杀本场景所有将领就能得到奖励", potSprite->getParent()->convertToWorldSpace(potSprite->getPosition()));
}
