//
//  LevelUp.h
//  threeKingdoms
//  Created by sma11case on 14-1-8.
//
//

#ifndef __threeKingdoms__LevelUp__
#define __threeKingdoms__LevelUp__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

USING_NS_CC;
using namespace std;

class LevelUp:public CCLayer
{
public:
    static LevelUp* create(int titleLevel);
    LevelUp(int titleLevel);
    ~LevelUp();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
    int titleLevel;
    void initContent();
    void close();
    void showMoney();
};

class LevelUpFacade:public CCObject
{
public:
    CLASS_INSTANCE(LevelUpFacade);
    bool init();
    
    void showLevelUp(int titleId);
};

#endif /* defined(__threeKingdoms__LevelUp__) */
