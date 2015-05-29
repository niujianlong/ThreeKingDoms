//
//  TipsManager.cpp
//  threeKingdoms
//  Created by sma11case 14-2-24.
//
//

#include "TipsManager.h"
#include "SceneManager.h"
#include "AnimateManager.h"
#include "GameUtils.h"

bool TipsManager::init()
{
    isShowing = false;
    tips = NULL;
    return true;
}

void TipsManager::showTips(const char *tipsContent, cocos2d::CCPoint p)
{
    if(!isShowing){
        isShowing = true;
        tips = createTips(tipsContent);
        INSTANCE(SceneManager)->addToCurrentScene(tips, zOrder_tips);
        tips->setPosition(getTipsPosition(p));
        INSTANCE(AnimateManager)->showAnimate(tips);
        tips->getScheduler()->scheduleSelector(schedule_selector(TipsManager::hideHandler), this, 2.0f, false);
    }
}

CommonTips* TipsManager::createTips(const char *tipsContent)
{
    return CommonTips::create(tipsContent);
}

void TipsManager::hideHandler()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    isShowing = false;
    INSTANCE(AnimateManager)->hideAnimate(tips);
    tips = NULL;
}

CCPoint TipsManager::getTipsPosition(cocos2d::CCPoint p)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize size = tips->getContentSize();
    int _x;
    int _y;
    _y = p.y + size.height/2 + 50;
    if(_y + size.height/2 > winSize.height){
        _y = p.y - size.height/2 -50;
    }
    _x = p.x;
    if(_x - size.width/2 < 0){
        _x = size.width/2;
    }
    if(_x + size.width/2 > winSize.width){
        _x = winSize.width - size.width/2;
    }
    return ccp(_x,_y);
}


CommonTips* CommonTips::create(const char *tipsContent)
{
    CommonTips *tips = new CommonTips(tipsContent);
    if(tips && tips->init()){
        tips->autorelease();
        return tips;
    }else{
        delete tips;
        tips = NULL;
        return NULL;
    }
}

CommonTips::CommonTips(const char *tipsContent){
    this->tipsContent = tipsContent;
}

CommonTips::~CommonTips()
{
    
}

bool CommonTips::init()
{
    if(!CCNode::init()){
        return false;
    }
    
    label = CCLabelTTF::create();
    label->setString(tipsContent);
    label->setFontSize(24);
    label->setColor(ccBLACK);
    label->setDimensions(CCSizeMake(300, 0));
    label->setHorizontalAlignment(kCCTextAlignmentCenter);
    label->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    
    bg = CCScale9Sprite::create("common/common_scale_2.png");
    bg->setPreferredSize(CCSizeMake(20 + label->getContentSize().width, 20 + label->getContentSize().height));
    
    setContentSize(bg->getPreferredSize());
    setAnchorPoint(ccp(0.5,0.5));
    
    addChild(bg);
    addChild(label);
    
    label->setPosition(getCenterPosition(this));
    bg->setPosition(getCenterPosition(this));
    
    return true;
}

void CommonTips::setString(const char *tipsContent)
{
    this->tipsContent = tipsContent;
    label->setString(tipsContent);
    bg->setPreferredSize(CCSizeMake(20 + label->getContentSize().width, 20 + label->getContentSize().height));
    setContentSize(bg->getPreferredSize());
    setAnchorPoint(ccp(0.5,0.5));
    label->setPosition(getCenterPosition(this));
    bg->setPosition(getCenterPosition(this));
}


