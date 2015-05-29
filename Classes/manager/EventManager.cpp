//
//  EventManager.cpp
//  threeKingdoms
//  Created by sma11case on 14-1-2.
//
//

#include "EventManager.h"

bool EventManager::init()
{
    return true;
}

void EventManager::addEventListener(CCNode *node,cocos2d::CCObject *target, SEL_CallFuncO function,bool swallowsTouches,CCPoint touchScale,CCPoint offset)
{
    EventNode *eventNode = EventNode::create();
    eventNode->setContentSize(CCSizeMake(node->getContentSize().width * touchScale.x, node->getContentSize().height * touchScale.y) );
    eventNode->swallowsTouches = swallowsTouches;
    node->addChild(eventNode);
    eventNode->setPosition(ccpAdd(node->getAnchorPointInPoints(), offset));
    eventNode->setListener(target, function);
}


EventNode::EventNode()
{
    
}

EventNode::~EventNode()
{
    
}

void EventNode::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, swallowsTouches);
    CCNode::onEnter();
    setAnchorPoint(ccp(0.5, 0.5));
}

void EventNode::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}


bool EventNode::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if(getParent()){
        if(!getParent()->isVisible()){
            return false;
        }
    }else{
        return false;
    }
    
    if(getParent()->getParent()){
        if(!getParent()->getParent()->isVisible()){
            return false;
        }
    }
    CCRect rect = CCRectMake(0, 0, getContentSize().width, getContentSize().height);
    CCPoint point = pTouch->getLocation();
    point = this->convertToNodeSpace(point);
    if(rect.containsPoint(point)){
        click();
        return true;
    }
    return false;
}
void EventNode::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void EventNode::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void EventNode::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void EventNode::setListener(CCObject *target, SEL_CallFuncO function)
{
    this->target = target;
    this->function = function;
}

void EventNode::click()
{
    if(target && function){
        (target->*function)(NULL);
    }
}