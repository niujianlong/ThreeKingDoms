//
//  LoginReward.cpp
//  threeKingdoms
//  Created by sma11case on 14-1-17.
//
//

#include "LoginReward.h"
#include "GameUtils.h"
#include "SceneManager.h"
#include "ButtonUtils.h"
#include "FightManager.h"
#include "UserData.h"
#include "TimeManager.h"
#include "SystemConfigRule.h"
#include "StringUtils.h"
#include "AnimationUtils.h"

bool LoginReward::init()
{
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 122))){
        return false;
    }
    initContent();
    return true;
}

void LoginReward::onEnter()
{
    ADD_TOUCH;
    CCLayerColor::onEnter();
    
}

void LoginReward::onExit()
{
    REMOVE_TOUCH;
    CCLayerColor::onExit();
    removeAllChildren();
}

void LoginReward::initContent()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/loginReward/loginReward.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    CCSprite *bg = CCSprite::create("common/commonBg_451_305.png");
    addChild(bg);
    bg->setPosition(ccpAdd(INSTANCE(GameUtils)->getWindowsCenterPosition(),ccp(0, 50)));
    
    CCSprite *titleBg = CCSprite::createWithSpriteFrameName("common_titleBg.png");
    bg->addChild(titleBg);
    titleBg->setPosition(ccp(bg->getContentSize().width/2 + 50, bg->getContentSize().height));
    
    CCLabelBMFont *title = CCLabelBMFont::create("登陆奖励", "font/font_uiTitle.fnt");
    titleBg->addChild(title);
    title->setPosition(ccpAdd(getCenterPosition(titleBg),ccp(-50, 0)));
    
    CCControlButton *receiveBtn = INSTANCE(ButtonUtils)->createButton("common_redBtn_1.png","common_redBtn_2.png","common_redBtn_1.png", CCSizeMake(151, 48), "领取奖励",24,ccYELLOW);
    bg->addChild(receiveBtn);
    receiveBtn->setPosition(ccp(bg->getContentSize().width/2, 60));
    receiveBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LoginReward::receiveReward), CCControlEventTouchUpInside);
    
//    CCSprite *moneyIcon = CCSprite::createWithSpriteFrameName("common_money_5.png");
//    bg->addChild(moneyIcon);
//    moneyIcon->setPosition(ccpAdd(getCenterPosition(bg),ccp(0, 50)));
//    
//    CCSprite *frame = CCSprite::createWithSpriteFrameName("loginReward_frame.png");
//    bg->addChild(frame);
//    frame->setPosition(ccpAdd(getCenterPosition(bg),ccp(0, 20)));
//    
//    CCLabelTTF *num = CCLabelTTF::create();
//    num->setFontSize(30);
//    num->setColor(ccRED);
//    frame->addChild(num);
//    num->setPosition(getCenterPosition(frame));
//    
    int dayNum;
    
    if(INSTANCE(UserData)->getContinuousDay() + 1 >=8){
        dayNum = 1;
    }else{
        dayNum = INSTANCE(UserData)->getContinuousDay() + 1;
    }
    receiveNum = INSTANCE(SystemConfigRule)->getLoginReward(dayNum);
//    CCString *temp = CCString::createWithFormat("元宝x%d",receiveNum);
//    num->setString(temp->getCString());
//    
//    CCLabelTTF *nextReward = CCLabelTTF::create();
//    nextReward->setFontSize(22);
//    nextReward->setColor(ccBLACK);
//    nextReward->setString("明日登陆可领取");
//    nextReward->setAnchorPoint(ccp(1, 0.5));
//    bg->addChild(nextReward);
//    nextReward->setPosition(ccp(bg->getContentSize().width/2 + 20, 120));
//    
//    CCLabelTTF *reward = CCLabelTTF::create();
//    reward->setFontSize(22);
//    reward->setColor(ccRED);
//    reward->setAnchorPoint(ccp(0, 0.5));
//    bg->addChild(reward);
//    
//    int rewardNum;
//    int weekDay = INSTANCE(TimeManager)->getWeekDay(INSTANCE(TimeManager)->getSystemTimeM());
//    if(weekDay == 6 || dayNum == 7){
//        rewardNum = INSTANCE(SystemConfigRule)->getLoginReward(1);
//    }else{
//        rewardNum = INSTANCE(SystemConfigRule)->getLoginReward(dayNum + 1);
//    }
//    reward->setString(CCString::createWithFormat("%d元宝",rewardNum)->getCString());
//    reward->setPosition(ccp(bg->getContentSize().width/2 + 25, 120));
    for(int i=0;i<7;i++){
        LoginRewardSingleReward *singleReward = LoginRewardSingleReward::create(i+1);
        bg->addChild(singleReward);
        singleReward->setPosition(ccp((i%4) *90 + 90, ((7-i)/4)*90 + 130));
    }
}

bool LoginReward::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void LoginReward::receiveReward()
{
    removeFromParent();
    INSTANCE(UserData)->addCurrentMoney(receiveNum);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
    
    int64_t t = INSTANCE(TimeManager)->getSystemTimeM();
    INSTANCE(UserData)->setLastReceiveLoginRewardTime(t);
    int dayNum = INSTANCE(UserData)->getContinuousDay();
    int weekDay = INSTANCE(TimeManager)->getWeekDay(INSTANCE(TimeManager)->getSystemTimeM());
    if(weekDay == 6 || dayNum >= 7){
        dayNum = 0;
    }else{
        dayNum++;
    }
    CCLOG("%d",dayNum);
    INSTANCE(UserData)->setContinuousDay(dayNum);
}


LoginRewardSingleReward* LoginRewardSingleReward::create(int day)
{
    LoginRewardSingleReward *reward = new LoginRewardSingleReward(day);
    if(reward && reward->init()){
        reward->autorelease();
        return reward;
    }else{
        delete reward;
        reward = NULL;
        return NULL;
    }
}

LoginRewardSingleReward::LoginRewardSingleReward(int day)
{
    this->day = day;
}

LoginRewardSingleReward::~LoginRewardSingleReward()
{
    
}

bool LoginRewardSingleReward::init()
{
    if(!CCSprite::initWithSpriteFrameName("common_rewardFrame.png")){
        return false;
    }
    int rewardNum = INSTANCE(SystemConfigRule)->getLoginReward(day);
    
    
    CCSprite *moneyIcon = CCSprite::createWithSpriteFrameName(getMoneyIcon().c_str());
    addChild(moneyIcon);
    moneyIcon->setPosition(getCenterPosition(this));
    moneyIcon->setScale(0.6);
    
    CCSprite *frame = CCSprite::createWithSpriteFrameName("loginReward_frame.png");
    addChild(frame);
    frame->setPosition(ccpAdd(getCenterPosition(this),ccp(0, -15)));
    
    CCLabelTTF *num = CCLabelTTF::create();
    num->setFontSize(18);
    num->setColor(ccRED);
    num->setString((INSTANCE(StringUtils)->intToString(rewardNum) + "元宝").c_str());
    frame->addChild(num);
    num->setPosition(getCenterPosition(frame));
    
    int dayNum;
    if(INSTANCE(UserData)->getContinuousDay() + 1 >=8){
        dayNum = 1;
    }else{
        dayNum = INSTANCE(UserData)->getContinuousDay() + 1;
    }
    
    if(day == dayNum){
        CCSprite *effect = CCSprite::create();
        CCAnimate *animate = CCAnimate::create(INSTANCE(AnimationUtils)->getCommonAnimation("ui/loginReward/loginReward.plist", "loginReward_effect",0.12));
        effect->runAction(CCRepeatForever::create(animate));
        addChild(effect);
        effect->setPosition(getCenterPosition(this));
    }else if(day < dayNum){
        CCSprite *flag = CCSprite::createWithSpriteFrameName("loginReward_received.png");
        addChild(flag);
        flag->setPosition(ccp(30, 50));
    }
    
    return true;
}

string LoginRewardSingleReward::getMoneyIcon()
{
    if(day == 1){
        return "common_money_1.png";
    }else if(day == 5 || day == 6){
        return "common_money_3.png";
    }else if(day == 7){
        return "common_money_5.png";
    }else{
        return "common_money_2.png";
    }
}

bool LoginRewardFacade::init()
{
    return true;
}

void LoginRewardFacade::open()
{
    INSTANCE(SceneManager)->addToCurrentScene(LoginReward::create(), zOrder_ui);
}