//
//  EventManager.h
//  threeKingdoms
//
//  Created by .m on 14-1-2.
//
//

#ifndef __threeKingdoms__EventManager__
#define __threeKingdoms__EventManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace std;
USING_NS_CC_EXT;

class EventManager:public CCObject
{
public:
    CLASS_INSTANCE(EventManager);
    bool init();
    
    void addEventListener(CCNode *node,CCObject* target, SEL_CallFuncO function,bool swallowsTouches = false,CCPoint xTouchScale = ccp(1.0, 1.0),CCPoint offset = ccp(0,0));
};

class EventNode:public CCNode,public CCTouchDelegate
{
public:
    CREATE_FUNC(EventNode);
    
    EventNode();
    ~EventNode();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void setListener(CCObject* target, SEL_CallFuncO function);
    
    bool swallowsTouches;
private:
    CCObject *target;
    SEL_CallFuncO function;
    
    void click();
};

#endif /* defined(__threeKingdoms__EventManager__) */
