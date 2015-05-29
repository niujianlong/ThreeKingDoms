//
//  NoticeManager.cpp
//  threeKingdoms
//  Created by sma11case 14-1-16.
//
//

#include "NoticeManager.h"
#include "SceneManager.h"
#include "GameUtils.h"

bool NoticeManager::init()
{
    winSize = CCDirector::sharedDirector()->getWinSize();
    return true;
}

void NoticeManager::showNotice(cocos2d::CCPoint targetPosition, cocos2d::CCNode *targetNode,float duration)
{
    targetNode->setPosition(ccp(-200, targetPosition.y));
    CCMoveTo *moveIn = CCMoveTo::create(0.1, targetPosition);
    CCEaseIn *easeIn = CCEaseIn::create( (CCActionInterval *)(moveIn->copy()->autorelease()), 0.1);
    CCMoveTo *moveOut = CCMoveTo::create(0.1, ccp(1300, targetPosition.y));
    CCEaseOut *easeOut = CCEaseOut::create( (CCActionInterval *)(moveOut->copy()->autorelease()), 0.1);
    CCSequence *action = CCSequence::create(easeIn,CCDelayTime::create(duration),easeOut,CCCallFuncN::create(targetNode, callfuncN_selector(CCSprite::removeFromParent)),NULL);
    targetNode->runAction(action);
    INSTANCE(SceneManager)->addToCurrentScene(targetNode, zOrder_notice);
}

void NoticeManager::showNotice(cocos2d::CCPoint targetPosition, float duration, string bgImgPath, string fontPath, string content,CCPoint offset)
{
    CCSprite *bg = CCSprite::create(bgImgPath.c_str());
    CCLabelBMFont *label = CCLabelBMFont::create(content.c_str(), fontPath.c_str());
    bg->addChild(label);
    label->setPosition(ccpAdd(getCenterPosition(bg),offset));
    showNotice(ccpSub(targetPosition,offset), bg, duration);
}