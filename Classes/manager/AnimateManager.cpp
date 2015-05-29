//
//  AnimateManager.cpp
//  threeKingdoms
//
//  Created by .m on 14-2-12.
//
//

#include "AnimateManager.h"

bool AnimateManager::init()
{
    return true;
}

void AnimateManager::showScaleAnimate(cocos2d::CCNode *target)
{
    target->setScale(0.2);
    CCScaleTo *scale_1 = CCScaleTo::create(0.2, 1.2);
    CCScaleTo *scale_2 = CCScaleTo::create(0.1, 1.0);
    CCSequence *action = CCSequence::create(scale_1,scale_2,CCDelayTime::create(2.0),CCCallFunc::create(target, callfunc_selector(CCNode::removeFromParent)),NULL);
    target->runAction(action);
}

void AnimateManager::showAnimate(cocos2d::CCNode *target)
{
    target->setScale(0.2);
    CCScaleTo *scale_1 = CCScaleTo::create(0.2, 1.2);
    CCScaleTo *scale_2 = CCScaleTo::create(0.1, 1.0);
    CCSequence *action = CCSequence::create(scale_1,scale_2,NULL);
    target->runAction(action);
}

void AnimateManager::hideAnimate(cocos2d::CCNode *target)
{
    CCScaleTo *scale_1 = CCScaleTo::create(0.1, 1.2);
    CCScaleTo *scale_2 = CCScaleTo::create(0.2, 0.1);
    CCSequence *action = CCSequence::create(scale_1,scale_2,CCCallFunc::create(target, callfunc_selector(CCNode::removeFromParent)),NULL);
    target->runAction(action);
}