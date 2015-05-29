//
//  OnlineReward.cpp
//  threeKingdoms
//  Created by sma11case on 14-2-14.
//
//

#include "OnlineReward.h"
#include "EventManager.h"
#include "TimeManager.h"
#include "StringUtils.h"
#include "UserData.h"
#include "FightManager.h"
#include "MoneyLayer.h"
#include "SystemConfigRule.h"
#include "GuideManager.h"
#include "TipsManager.h"

OnlineReward::OnlineReward()
{
    
}

OnlineReward::~OnlineReward()
{
    
}

bool OnlineReward::init()
{
    if(!CCNode::init()){
        return false;
    }
    initContent();
    return true;
}

void OnlineReward::initContent()
{
    time = INSTANCE(SystemConfigRule)->getOnlineRewardTime();
    times = INSTANCE(SystemConfigRule)->getOnlineRewardTimes();
    money = INSTANCE(SystemConfigRule)->getOnlineReward();
    
    CCSprite *frame = CCSprite::createWithSpriteFrameName("fightUI_onlineReward_frame.png");
    addChild(frame);
    INSTANCE(EventManager)->addEventListener(frame, this, callfuncO_selector(OnlineReward::receiveHandler));
    
    bar = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("fightUI_onlineReward_bar.png"));
    frame->addChild(bar);
    bar->setPosition(ccp(frame->getContentSize().width/2,10));
    bar->setType(kCCProgressTimerTypeBar);
    bar->setBarChangeRate(ccp(1, 0));
    bar->setMidpoint(ccp(0, 0));
    bar->setPercentage(((float)INSTANCE(UserData)->getReceiveOnlineRewardTimes())/times * 100);
    
    for(int i=1;i<times;i++){
        CCSprite *line = CCSprite::createWithSpriteFrameName("fightUI_onlineReward_line.png");
        frame->addChild(line);
        line->setPosition(ccp(8+i*(90/times), 10));
    }
    
    label = CCLabelTTF::create();
    label->setPosition(ccp(frame->getContentSize().width/2,32));
    label->setFontSize(20);
    label->setColor(ccRED);
    frame->addChild(label);
    updateTime();
    getScheduler()->scheduleSelector(schedule_selector(OnlineReward::updateTime), this, 1.0f, false);
}

void OnlineReward::updateTime()
{
    int64_t currentTime = INSTANCE(TimeManager)->getSystemTimeM();
    int64_t receiveTime = INSTANCE(UserData)->getLastReceiveOnlineRewardTime();
    

    
    if(INSTANCE(TimeManager)->isLaterDay(receiveTime, currentTime)){
        INSTANCE(UserData)->setReceiveOnlineRewardTimes(0);
        bar->setPercentage(((float)INSTANCE(UserData)->getReceiveOnlineRewardTimes())/times * 100);
    }
    
    if(INSTANCE(UserData)->getReceiveOnlineRewardTimes() == times){
        label->setColor(ccRED);
        label->setString("今日已领取");
        receivable = false;
    }else{
        if(receiveTime == 0){
            label->setColor(ccGREEN);
            label->setString("领取奖励");
            receivable = true;
        }else{
            int64_t t = currentTime - (receiveTime + time * 1000);
            if(t >= 0){
                label->setColor(ccGREEN);
                label->setString("领取奖励");
                receivable = true;
            }else{
                label->setColor(ccRED);
                label->setString(INSTANCE(StringUtils)->dountDownToString(t>=0?t:-t).c_str());
                receivable = false;
            }
        }
    }
}

void OnlineReward::receiveHandler()
{
    if(receivable){
        CCLog("领取");
        INSTANCE(UserData)->addReceiveOnlineRewardTimes(1);
        INSTANCE(UserData)->setLastReceiveOnlineRewardTime(INSTANCE(TimeManager)->getSystemTimeM());
        bar->setPercentage(((float)INSTANCE(UserData)->getReceiveOnlineRewardTimes())/times * 100);
        updateTime();
        
        INSTANCE(UserData)->addCurrentMoney(money);
        CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
        
        INSTANCE(MoneyLayerManager)->createMoney(money, getPosition());
        
        
    }else{
        INSTANCE(TipsManager)->showTips("倒计时结束后可领取奖励", this->getParent()->convertToWorldSpace(getPosition()));
    }
    if(INSTANCE(GuideManager)->getIsGuiding() && INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10008){
        INSTANCE(GuideManager)->goToNext();
    }
    
}

void OnlineReward::onEnter()
{
    CCNode::onEnter();
    INSTANCE(GuideManager)->registerPosition(GuideStep_10008, label->getParent()->convertToWorldSpace(label->getPosition()));
}

void OnlineReward::onExit()
{
    CCNode::onExit();
}
