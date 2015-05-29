//
//  SingleRecharge.cpp
//  threeKingdoms
//  Created by sma11case 14-2-8.
//
//

#include "SingleRecharge.h"
#include "ButtonUtils.h"
#include "GameUtils.h"
#include "StringUtils.h"
#include "UserData.h"
#include "RechargeManager.h"
#include "RechargeRule.h"

SingleRecharge* SingleRecharge::create(int rechargeId)
{
    SingleRecharge *singleRecharge = new SingleRecharge(rechargeId);
    if(singleRecharge && singleRecharge->init()){
        singleRecharge->autorelease();
        return singleRecharge;
    }else{
        delete singleRecharge;
        singleRecharge = NULL;
        return NULL;
    }
}

SingleRecharge::SingleRecharge(int rechargeId)
{
    this->rechargeId = rechargeId;
}

SingleRecharge::~SingleRecharge()
{
    
}

bool SingleRecharge::init()
{
    if(!CCNode::init()){
        return false;
    }
    initContent();
    return true;
}

void SingleRecharge::initContent()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/recharge/recharge.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    CCSprite *frameTop = CCSprite::createWithSpriteFrameName("recharge_frame_top.png");
    addChild(frameTop);
    frameTop->setPosition(ccp(0, frameTop->getContentSize().height/2));
    
    CCSprite *frameBottom = CCSprite::createWithSpriteFrameName("recharge_frame_bottom.png");
    addChild(frameBottom);
    frameBottom->setPosition(ccp(0, -frameBottom->getContentSize().height/2 + 3));
    
    CCSprite *moneyIcon = CCSprite::createWithSpriteFrameName(getMoneyIconImgName().c_str());
    frameTop->addChild(moneyIcon);
    moneyIcon->setPosition(getCenterPosition(frameTop));
    
    CCSprite *labelBg = CCSprite::createWithSpriteFrameName("recharge_nameBg.png");
    frameTop->addChild(labelBg);
    labelBg->setPosition(ccp(frameTop->getContentSize().width/2, 30));
    
    CCLabelTTF *label = CCLabelTTF::create();
    label->setFontSize(24);
    label->setColor(ccRED);
    labelBg->addChild(label);
    label->setPosition(getCenterPosition(labelBg));
    label->setString(CCString::createWithFormat("%s元宝",INSTANCE(StringUtils)->numToString(getGoldNum()).c_str())->getCString());
    
    CCControlButton *btn = INSTANCE(ButtonUtils)->createButton("common_redBtn_1.png", CCSizeMake(152, 48), CCString::createWithFormat("%s元",INSTANCE(StringUtils)->numToString(getMoneyNum()).c_str())->getCString());
    frameBottom->addChild(btn);
    btn->setPosition(getCenterPosition(frameBottom));
    btn->addTargetWithActionForControlEvents(this, cccontrol_selector(SingleRecharge::rechargeHandler), CCControlEventTouchUpInside);
}

int SingleRecharge::getMoneyNum()
{
    return INSTANCE(RechargeRule)->getRechargePrice(rechargeId);
}

int SingleRecharge::getGoldNum()
{
    return INSTANCE(RechargeRule)->getRechargeGoldCount(rechargeId);
}

string SingleRecharge::getMoneyIconImgName()
{
    string result = "";
    int temp = (rechargeId - 1)%6;
    switch (temp) {
        case 0:
            result = "recharge_moneyIcon_1.png";
            break;
        case 1:
            result = "recharge_moneyIcon_2.png";
            break;
        case 2:
            result = "recharge_moneyIcon_3.png";
            break;
        case 3:
            result = "recharge_moneyIcon_4.png";
            break;
        case 4:
            result = "recharge_moneyIcon_5.png";
            break;
        case 5:
            result = "recharge_moneyIcon_6.png";
            break;
        default:
            break;
    }
    return result;
}

void SingleRecharge::rechargeHandler()
{
    INSTANCE(RechargeManager)->recharge(rechargeId);
}
