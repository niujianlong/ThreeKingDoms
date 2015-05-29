//
//  CommonMoneyBar.cpp
//  threeKingdoms
//  Created by sma11case 14-2-8.
//
//

#include "CommonMoneyBar.h"
#include "UserData.h"
#include "StringUtils.h"
#include "GameUtils.h"

CommonMoneyBar::CommonMoneyBar()
{
    
}

CommonMoneyBar::~CommonMoneyBar()
{
    
}

bool CommonMoneyBar::init()
{
    if(!CCNode::init()){
        return false;
    }
    initContent();
    return true;
}

void CommonMoneyBar::initContent()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    
    CCSprite *frame_2 = CCSprite::createWithSpriteFrameName("common_frame_1.png");
    frame_2->setAnchorPoint(ccp(0, 0.5));
    addChild(frame_2);
    
    moneyBar = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("common_frameBar_1.png"));
    frame_2->addChild(moneyBar);
    moneyBar->setPosition(ccp(frame_2->getContentSize().width/2,frame_2->getContentSize().height/2));
    moneyBar->setType(kCCProgressTimerTypeBar);
    moneyBar->setBarChangeRate(ccp(1, 0));
    moneyBar->setMidpoint(ccp(0, 0));
    moneyBar->setPercentage(((float)INSTANCE(UserData)->getCurrentMoney())/9999 * 100);
    
    CCSprite *ink2 = CCSprite::createWithSpriteFrameName("common_ink.png");
    frame_2->addChild(ink2);
    ink2->setPosition(ccp(10, frame_2->getContentSize().height/2));
    
    moneyLabel = CCLabelBMFont::create(INSTANCE(StringUtils)->intToString(INSTANCE(UserData)->getCurrentMoney()).c_str(), "font/font_yellowNum.fnt");
    frame_2->addChild(moneyLabel);
    moneyLabel->setPosition(ccpAdd(INSTANCE(GameUtils)->getNodeCenterPosition(frame_2),ccp(0, -8)));
    
    CCSprite *moneyIcon = CCSprite::createWithSpriteFrameName("common_money_3.png");
    moneyIcon->setScale(0.6);
    frame_2->addChild(moneyIcon);
    moneyIcon->setPosition(ccp(10, frame_2->getContentSize().height/2));
}

void CommonMoneyBar::updateBar()
{
    moneyBar->setPercentage(((float)INSTANCE(UserData)->getCurrentMoney())/9999 * 100);
    moneyLabel->setString(INSTANCE(StringUtils)->intToString(INSTANCE(UserData)->getCurrentMoney()).c_str());
}