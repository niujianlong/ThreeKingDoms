//
//  CreateCharacterBg.cpp
//  threeKingdoms
//
//  Created by .m on 14-1-21.
//
//

#include "CreateCharacterBg.h"
#include "ButtonUtils.h"

bool CreateCharacterBg::init()
{
    if(!CCSpriteBatchNode::initWithFile("ui/createCharacter/createCharacter_bg.png",2)){
        return false;
    }
    initContent();
    return true;
}

void CreateCharacterBg::initContent()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    setPosition(ccp(0, winSize.height));
    bg1 = CCSprite::create("ui/createCharacter/createCharacter_bg.png");
    bg2 = CCSprite::create("ui/createCharacter/createCharacter_bg.png");
    addChild(bg1);
    bg1->setAnchorPoint(ccp(0, 1));
    addChild(bg2);
    bg2->setAnchorPoint(ccp(0, 1));
    bg2->setFlipX(true);
    bg2->setPosition(ccp(-bg1->getContentSize().width, 0));
    
    scheduleUpdate();
}

void CreateCharacterBg::update(float t)
{
    bg1->setPosition(ccpAdd(bg1->getPosition(), ccp(1, 0)));
    bg2->setPosition(ccpAdd(bg2->getPosition(), ccp(1, 0)));
    
    if(bg1->getPosition().x > 0 && bg2->getPosition().x > 0){
        if(bg1->getPosition().x > bg2->getPosition().x){
            bg1->setPosition(ccpSub(bg2->getPosition(), ccp(bg2->getContentSize().width, 0)));
        }else{
            bg2->setPosition(ccpSub(bg1->getPosition(), ccp(bg1->getContentSize().width, 0)));
        }
    }
}