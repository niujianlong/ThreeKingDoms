//
//  CommonTitleBar.cpp
//  threeKingdoms
//  Created by sma11case on 14-2-8.
//
//

#include "CommonTitleBar.h"
#include "UserData.h"
#include "GameUtils.h"
#include "TitleRule.h"

CommonTitleBar::CommonTitleBar()
{
    
}

CommonTitleBar::~CommonTitleBar()
{
    
}

bool CommonTitleBar::init()
{
    if(!CCNode::init()){
        return false;
    }
    
    initContent();
    return true;
}

void CommonTitleBar::initContent()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    
    CCSprite *frame_1 = CCSprite::createWithSpriteFrameName("common_frame_1.png");
    frame_1->setAnchorPoint(ccp(0, 0.5));
    addChild(frame_1);
    
    titleBar = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("common_frameBar_1.png"));
    frame_1->addChild(titleBar);
    titleBar->setPosition(ccp(frame_1->getContentSize().width/2,frame_1->getContentSize().height/2));
    titleBar->setType(kCCProgressTimerTypeBar);
    titleBar->setBarChangeRate(ccp(1, 0));
    titleBar->setMidpoint(ccp(0, 0));
    titleBar->setPercentage(((float)INSTANCE(UserData)->getCurrentMoney())/9999 * 100);
    
    CCSprite *ink1 = CCSprite::createWithSpriteFrameName("common_ink.png");
    frame_1->addChild(ink1);
    ink1->setPosition(ccp(10, frame_1->getContentSize().height/2));
    
    int currentTitleLevel = INSTANCE(UserData)->getTitleLevel();
    string titleName = INSTANCE(TitleRule)->getTitleNameByTitleLevel(currentTitleLevel);
    int nextTitleIntegral = INSTANCE(TitleRule)->getTitleIntegralByTitleLevel(currentTitleLevel + 1);
    int currentUpgradeIntegral = INSTANCE(UserData)->getCurrentUpgradeIntegral();
    titleBar->setPercentage(((float)currentUpgradeIntegral)/nextTitleIntegral * 100);
    
    titleLabel = CCLabelBMFont::create(titleName.c_str(), "font/font_title.fnt");
    frame_1->addChild(titleLabel);
    titleLabel->setPosition(ccpAdd(INSTANCE(GameUtils)->getNodeCenterPosition(frame_1),ccp(0, -8)));
    
    CCSprite *titleIcon = CCSprite::createWithSpriteFrameName("common_titleIcon.png");
    frame_1->addChild(titleIcon);
    titleIcon->setPosition(ccp(10, frame_1->getContentSize().height/2));
    
    titleLevel = CCLabelTTF::create();
    titleLevel->setFontSize(20);
    titleLevel->setColor(ccYELLOW);
    titleLevel->setString(CCString::createWithFormat("Lv%d",INSTANCE(UserData)->getTitleLevel())->getCString());
    titleIcon->addChild(titleLevel);
    titleLevel->setPosition(ccp(20, titleIcon->getContentSize().height/2 - 20));
}

void CommonTitleBar::updateBar()
{
    int currentTitleLevel = INSTANCE(UserData)->getTitleLevel();
    string titleName = INSTANCE(TitleRule)->getTitleNameByTitleLevel(currentTitleLevel);
    int nextTitleIntegral = INSTANCE(TitleRule)->getTitleIntegralByTitleLevel(currentTitleLevel + 1);
    int currentUpgradeIntegral = INSTANCE(UserData)->getCurrentUpgradeIntegral();
    
    titleBar->setPercentage(((float)currentUpgradeIntegral)/nextTitleIntegral * 100);
    titleLabel->setString(titleName.c_str());
    titleLevel->setString(CCString::createWithFormat("Lv%d",INSTANCE(UserData)->getTitleLevel())->getCString());
}

CCNode* CommonTitleBar::getEventNode()
{
    return titleBar;
}