//
//  Recharge.h
//  threeKingdoms
//  Created by sma11case on 14-2-7.
//
//

#ifndef __threeKingdoms__Recharge__
#define __threeKingdoms__Recharge__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "CommonMoneyBar.h"

using namespace std;
USING_NS_CC;

class Recharge:public CCLayer
{
public:
    CREATE_FUNC(Recharge);
    Recharge();
    ~Recharge();
    
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
    void initContent();
    
    CommonMoneyBar *moneyBar;
    
    void closeHandler();
    
};

class RechargeFacade:public CCObject
{
public:
    CLASS_INSTANCE(RechargeFacade);
    
    bool init();
    
    void open();
private:
    
};


#endif /* defined(__threeKingdoms__Recharge__) */
