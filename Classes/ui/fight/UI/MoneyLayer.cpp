//
//  MoneyLayer.cpp
//  threeKingdoms
//
//  Created by .m on 13-12-31.
//
//

#include "MoneyLayer.h"
#include "SceneManager.h"
#include "GameUtils.h"
#include "SoundManager.h"

bool MoneyLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    
    initContent();
    
    return true;
}

void MoneyLayer::initContent()
{
    
}

void MoneyLayer::onEnter()
{
    CCLayer::onEnter();
}

void MoneyLayer::onExit()
{
    CCLayer::onExit();
    removeAllChildren();
    INSTANCE(MoneyLayerManager)->removeLayer();
}

SingleMoney* SingleMoney::create(int money)
{
    SingleMoney *singleMoney = new SingleMoney(money);
    if(singleMoney && singleMoney->init()){
        singleMoney->autorelease();
        return singleMoney;
    }else{
        delete singleMoney;
        singleMoney = NULL;
        return NULL;
    }
}

SingleMoney::SingleMoney(int money)
{
    num = money;
}

SingleMoney::~SingleMoney()
{
    
}

void SingleMoney::onEnter()
{
    CCSprite::onEnter();
}

void SingleMoney::onExit()
{
    CCSprite::onExit();
    removeAllChildren();
    
}

bool SingleMoney::init()
{
    if(!CCSprite::createWithSpriteFrameName(getImage().c_str())){
        return false;
    }
    setAnchorPoint(ccp(0.5, 0.5));
    spriteWidth = getContentSize().width/2;
    return true;
}

string SingleMoney::getImage()
{
    string moneyNum;
    if(num >=1 && num<=5){
        moneyNum = "common_money_1.png";
    }else if(num >=6 && num <= 10){
        moneyNum = "common_money_2.png";
    }else if(num >=11 && num <= 50){
        moneyNum = "common_money_3.png";
    }else if(num >=51 && num <= 80){
        moneyNum = "common_money_4.png";
    }else{
        moneyNum = "common_money_5.png";
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    return moneyNum;
}

int SingleMoney::getSpriteWidth()
{
    return spriteWidth;
}

void SingleMoney::removeAndPlaySound()
{
    INSTANCE(SoundManager)->playGainMoney();
    removeFromParent();
}

bool MoneyLayerManager::init()
{
    layer = NULL;
    return true;
}

void MoneyLayerManager::showMoney(cocos2d::CCPoint position, int num)
{
    if(num <= 0){
        return;
    }
    if(layer == NULL){
        layer = MoneyLayer::create();
        INSTANCE(SceneManager)->addToCurrentScene(layer, zOrder_moneyNotice);
        layer->setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
        
        iconNode = CCSpriteBatchNode::create("common/common.png");
        layer->addChild(iconNode);
        
        labelNode = CCSpriteBatchNode::create("font/font_gold.png");
        layer->addChild(labelNode);
    }
    
//    SingleMoney *money = SingleMoney::create(num);
    CCSprite *money = CCSprite::createWithSpriteFrameName(getImage(num).c_str());
    iconNode->addChild(money);
    money->setAnchorPoint(ccp(0, 0.5));
    CCPoint p = ccpAdd(position, ccp(0, 70));
    money->setPosition(p);
    
    float duration_1;
    if(num >=1 && num<=5){
        duration_1 = 0.6;
    }else if(num >=6 && num <= 10){
        duration_1 = 0.8;
    }else if(num >=11 && num <= 50){
        duration_1 = 1.0;
    }else if(num >=51 && num <= 80){
        duration_1 = 1.1;
    }else{
        duration_1 = 1.2;
    }
    
    CCMoveBy *move_1 = CCMoveBy::create(duration_1, ccp(0, 100*duration_1));
    CCEaseOut *easeOut = CCEaseOut::create((CCActionInterval *) (move_1->copy()->autorelease()),1.5f);
    CCPoint tp = ccpSub(p, ccp(-250, -280));
    float duration_2 = powf(tp.x * tp.x + tp.y *tp.y,0.5) / 1000;
    CCMoveTo *move_2 = CCMoveTo::create(duration_2, ccp(-230, -240));
    CCEaseIn *easeIn = CCEaseIn::create((CCActionInterval *) (move_2->copy()->autorelease()),duration_2);
    CCAction *action = CCSequence::create(easeOut,easeIn,CCCallFuncN::create(money, callfuncN_selector(SingleMoney::removeAndPlaySound)),NULL);
    money->runAction(action);
    
    
    
    CCString *labelNum = CCString::createWithFormat("+%d",num);
    CCLabelBMFont *moneyLabel = CCLabelBMFont::create(labelNum->getCString(), "font/font_gold.fnt");
    layer->addChild(moneyLabel);
    moneyLabel->setAnchorPoint(ccp(1, 0.5));
    moneyLabel->setPosition(p);
    
    CCMoveBy *move_3 = CCMoveBy::create(duration_1 * 1.5, ccp(0, 150 * duration_1 * 1.5));
    CCFadeOut *fadeOut = CCFadeOut::create(1.2);
    CCAction *action_2 = CCSequence::create(move_3,CCCallFuncN::create(moneyLabel, callfuncN_selector(CCLabelBMFont::removeFromParent)),NULL);
    moneyLabel->runAction(action_2);
    moneyLabel->runAction(fadeOut);
}

void MoneyLayerManager::removeLayer()
{
    layer = NULL;
}

string MoneyLayerManager::getImage(int num)
{
    string moneyNum;
    if(num >=1 && num<=5){
        moneyNum = "common_money_1.png";
    }else if(num >=6 && num <= 10){
        moneyNum = "common_money_2.png";
    }else if(num >=11 && num <= 50){
        moneyNum = "common_money_3.png";
    }else if(num >=51 && num <= 80){
        moneyNum = "common_money_4.png";
    }else{
        moneyNum = "common_money_5.png";
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    return moneyNum;
}

void MoneyLayerManager::createMoney(int num,CCPoint position)
{
    CCNode *node = CCNode::create();
    node->setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    CCSprite *money = CCSprite::createWithSpriteFrameName(INSTANCE(MoneyLayerManager)->getImage(num).c_str());
    node->addChild(money);
    money->setAnchorPoint(ccp(0, 0.5));
    CCPoint p = ccpAdd(position, ccp(0, -30));
    money->setPosition(p);
    
    float duration_1;
    if(num >=1 && num<=5){
        duration_1 = 0.6;
    }else if(num >=6 && num <= 10){
        duration_1 = 0.8;
    }else if(num >=11 && num <= 50){
        duration_1 = 1.0;
    }else if(num >=51 && num <= 80){
        duration_1 = 1.1;
    }else{
        duration_1 = 1.2;
    }
    
    CCMoveBy *move_1 = CCMoveBy::create(duration_1, ccp(0, 100*duration_1));
    CCEaseOut *easeOut = CCEaseOut::create((CCActionInterval *) (move_1->copy()->autorelease()),1.5f);
    CCPoint tp = ccpSub(p, ccp(-230, -240));
    float duration_2 = powf(tp.x * tp.x + tp.y *tp.y,0.5) / 1000;
    CCMoveTo *move_2 = CCMoveTo::create(duration_2, ccp(-230, -240));
    CCEaseIn *easeIn = CCEaseIn::create((CCActionInterval *) (move_2->copy()->autorelease()),duration_2);
    CCAction *action = CCSequence::create(easeOut,easeIn,CCCallFuncN::create(money, callfuncN_selector(SingleMoney::removeAndPlaySound)),NULL);
    money->runAction(action);
    
    
    
    CCString *labelNum = CCString::createWithFormat("+%d",num);
    CCLabelBMFont *moneyLabel = CCLabelBMFont::create(labelNum->getCString(), "font/font_gold.fnt");
    node->addChild(moneyLabel);
    moneyLabel->setAnchorPoint(ccp(1, 0.5));
    moneyLabel->setPosition(p);
    
    CCMoveBy *move_3 = CCMoveBy::create(duration_1 * 1.5, ccp(0, 150 * duration_1 * 1.5));
    CCFadeOut *fadeOut = CCFadeOut::create(1.2);
    CCAction *action_2 = CCSequence::create(move_3,CCCallFuncN::create(node, callfuncN_selector(CCNode::removeFromParent)),NULL);
    moneyLabel->runAction(action_2);
    moneyLabel->runAction(fadeOut);
    
    INSTANCE(SceneManager)->addToCurrentScene(node, zOrder_notice);
}


void MoneyLayerManager::createReduceMoney(int num)
{
    CCNode *node = CCNode::create();
    node->setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    CCSprite *money = CCSprite::createWithSpriteFrameName(INSTANCE(MoneyLayerManager)->getImage(num).c_str());
    node->addChild(money);
    money->setAnchorPoint(ccp(0, 0.5));
    CCPoint p = ccp(-200, -240);
    money->setPosition(p);
    
    CCString *labelNum = CCString::createWithFormat("-%d",num);
    CCLabelBMFont *moneyLabel = CCLabelBMFont::create(labelNum->getCString(), "font/font_gold.fnt");
    node->addChild(moneyLabel);
    moneyLabel->setAnchorPoint(ccp(1, 0.5));
    moneyLabel->setPosition(p);
    moneyLabel->setColor(ccRED);
    
    CCMoveBy *move_3 = CCMoveBy::create(1.2, ccp(0, 100));
    CCEaseOut *easeOut = CCEaseOut::create((CCActionInterval *) (move_3->copy()->autorelease()),1.5f);
    CCFadeOut *fadeOut = CCFadeOut::create(1.2);
    CCAction *action_2 = CCSequence::create(easeOut,CCCallFuncN::create(node, callfuncN_selector(CCNode::removeFromParent)),NULL);
    
    node->runAction(action_2);
    node->runAction(fadeOut);
    
    INSTANCE(SceneManager)->addToCurrentScene(node, zOrder_notice);
}
