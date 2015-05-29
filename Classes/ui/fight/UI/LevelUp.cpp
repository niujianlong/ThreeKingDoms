//
//  LevelUp.cpp
//  threeKingdoms
//  Created by sma11case on 14-1-8.
//
//

#include "LevelUp.h"
#include "SceneManager.h"
#include "StringUtils.h"
#include "GameUtils.h"
#include "ButtonUtils.h"
#include "TitleRule.h"
#include "MoneyLayer.h"
#include "FightManager.h"
#include "SceneRule.h"
#include "UserData.h"
#include "NewChapterOpen.h"
#include "AnimateManager.h"

LevelUp* LevelUp::create(int titleLevel)
{
    LevelUp *levelUp = new LevelUp(titleLevel);
    if(levelUp && levelUp->init()){
        levelUp->autorelease();
        return levelUp;
    }else{
        delete levelUp;
        levelUp = NULL;
        return NULL;
    }
}

LevelUp::LevelUp(int titleLevel)
{
    this->titleLevel = titleLevel;
}

LevelUp::~LevelUp()
{
    
}

bool LevelUp::init()
{
    if(!CCLayer::init()){
        return false;
    }
    setAnchorPoint(ccp(0, 0));
    initContent();
    return true;
}

void LevelUp::initContent()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/fightUI/levelUp.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    CCSprite *bg = CCSprite::createWithSpriteFrameName("levelUp_bg.png");
    addChild(bg);
    
    CCSprite *title = CCSprite::createWithSpriteFrameName("levelUp_title.png");
    bg->addChild(title);
    title->setPosition(ccp(bg->getContentSize().width/2, bg->getContentSize().height - 130));
    
    int money = INSTANCE(TitleRule)->getTitleUpgradeReward(titleLevel);
    INSTANCE(UserData)->addCurrentMoney(money);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
    
    CCSprite *moneyIcon = CCSprite::createWithSpriteFrameName("common_money_10.png");
    
    addChild(moneyIcon);
    moneyIcon->setPosition(ccp(-30, -30));
    
    CCLabelBMFont *goldLabel = CCLabelBMFont::create(INSTANCE(StringUtils)->intToString(money).c_str(), "font/font_gold.fnt");
    addChild(goldLabel);
    goldLabel->setAnchorPoint(ccp(0, 0.5));
    goldLabel->setPosition(ccp(30, -30));
    
//    CCLabelBMFont *titleLabel = CCLabelBMFont::create(INSTANCE(TitleRule)->getTitleNameByTitleLevel(titleLevel).c_str(), "font/font_title.fnt");
//    addChild(titleLabel);
//    titleLabel->setPosition(ccp(0, 100));
    
//    CCControlButton *closeBtn = INSTANCE(ButtonUtils)->createButton("levelUp_closeBtn.png", CCSizeMake(82, 82), "");
//    addChild(closeBtn);
//    closeBtn->setPosition(ccp(bg->getContentSize().width/2 - 10, bg->getContentSize().height/2 - 10));
//    closeBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LevelUp::close), CCControlEventTouchUpInside);
}

void LevelUp::onEnter()
{
//    ADD_TOUCH;
    CCLayer::onEnter();
    setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    INSTANCE(AnimateManager)->showScaleAnimate(this);
    
    
}

void LevelUp::showMoney()
{
    int num = INSTANCE(TitleRule)->getTitleUpgradeReward(titleLevel);
    if(num <= 0){
        return;
    }
    INSTANCE(MoneyLayerManager)->createMoney(num,ccp(0, 0));

}

void LevelUp::onExit()
{
//    REMOVE_TOUCH;
    CCLayer::onExit();
    
    int currentTitleLevel = INSTANCE(UserData)->getTitleLevel();
    vector<int> sceneIdVector = INSTANCE(SceneRule)->getAllSceneId();
    for(int i=0;i<sceneIdVector.size();i++){
        int openLevel = INSTANCE(SceneRule)->getSceneNeedLevel(sceneIdVector[i]);
        if(openLevel == currentTitleLevel){
            //显示新关卡开启特效
            INSTANCE(NewChapterOpenManager)->showNewChapterOpen(sceneIdVector[i]);
            break;
        }
    }
}

bool LevelUp::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void LevelUp::close()
{
    removeFromParent();
    
}


bool LevelUpFacade::init()
{
    return true;
}

void LevelUpFacade::showLevelUp(int titleId)
{
    LevelUp *levelUp = LevelUp::create(titleId);
    INSTANCE(SceneManager)->addToCurrentScene(levelUp, zOrder_notice);
}
