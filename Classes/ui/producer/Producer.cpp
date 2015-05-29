//
//  Producer.cpp
//  threeKingdoms
//  Created by sma11case 14-2-23.
//
//

#include "Producer.h"
#include "GameUtils.h"
#include "CreateCharacterBg.h"

Producer::Producer()
{
    
}

Producer::~Producer()
{
    
}

bool Producer::init()
{
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 255))){
        return false;
    }
    initContent();
    return true;
}

void Producer::initContent()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/createCharacter/createCharacter.plist");
    
    addChild(CreateCharacterBg::create());
    
    CCSprite *fg = CCSprite::createWithSpriteFrameName("createCharacter_fontground.png");
    addChild(fg);
    fg->setAnchorPoint(ccp(0.5,0));
    fg->setPosition(ccp(INSTANCE(GameUtils)->getWindowsCenterPosition().x, 0));
    
    
    CCSprite* producerSprite = CCSprite::create("ui/producer/producer.png");
    addChild(producerSprite);
    producerSprite->setPosition(ccp(winSize.width/2, -600));
    
    CCMoveBy *move = CCMoveBy::create(18.0f, ccp(0, 2000));
    CCSequence *action = CCSequence::create(move,CCCallFunc::create(this, callfunc_selector(CCLayerColor::removeFromParent)),NULL);
    producerSprite->runAction(action);
}

void Producer::onEnter()
{
    ADD_TOUCH;
    CCLayerColor::onEnter();
}

void Producer::onExit()
{
    REMOVE_TOUCH;
    CCLayerColor::onExit();
}

bool Producer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
//    removeFromParent();
    return true;
}

