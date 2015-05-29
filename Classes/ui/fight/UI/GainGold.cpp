//
//  GainGold.cpp
//  threeKingdoms
//  Created by sma11case on 14-1-8.
//
//

#include "GainGold.h"
#include "SceneManager.h"
#include "GameUtils.h"
#include "StringUtils.h"
#include "AnimateManager.h"

GainGold* GainGold::create(int goldNum)
{
    GainGold *gainGold = new GainGold(goldNum);
    if(gainGold && gainGold->init()){
        gainGold->autorelease();
        return gainGold;
    }else{
        delete gainGold;
        gainGold = NULL;
        return NULL;
    }
}

GainGold::GainGold(int goldNum)
{
    this->goldNum = goldNum;
}

GainGold::~GainGold()
{
    
}

bool GainGold::init()
{
    if(!CCNode::init()){
        return false;
    }
    initContent();
    return true;
}

void GainGold::initContent()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/fightUI/gainGold.plist");
    CCSprite *bg = CCSprite::createWithSpriteFrameName("gainGold_bg.png");
    addChild(bg);
    
    CCSprite *title = CCSprite::createWithSpriteFrameName("gainGold_title.png");
    bg->addChild(title);
    title->setPosition(ccp(bg->getContentSize().width/2, bg->getContentSize().height - 30));
    
    CCSprite *label = CCSprite::createWithSpriteFrameName("gainGold_label.png");
    bg->addChild(label);
    label->setPosition(ccp(bg->getContentSize().width/2, bg->getContentSize().height/2 + 40));
    
    CCSprite *gold = CCSprite::createWithSpriteFrameName("gainGold_gold.png");
    bg->addChild(gold);
    gold->setPosition(ccp(bg->getContentSize().width/2, gold->getContentSize().height/2 + 50));
    
    CCLabelBMFont *goldLabel = CCLabelBMFont::create(INSTANCE(StringUtils)->intToString(goldNum).c_str(), "font/font_gold.fnt");
    bg->addChild(goldLabel);
    goldLabel->setPosition(label->getPosition());
}

void GainGold::onEnter()
{
    CCNode::onEnter();
    setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    INSTANCE(AnimateManager)->showScaleAnimate(this);
}

void GainGold::onExit()
{
    CCNode::onExit();
}


bool GainGoldFacade::init()
{
    return true;
}

void GainGoldFacade::showGainGold(int goldNum)
{
    GainGold *gainGold = GainGold::create(goldNum);
    INSTANCE(SceneManager)->addToCurrentScene(gainGold, zOrder_notice);
}




