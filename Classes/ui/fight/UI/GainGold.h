//
//  GainGold.h
//  threeKingdoms
//  Created by sma11case on 14-1-8.
//
//

#ifndef __threeKingdoms__GainGold__
#define __threeKingdoms__GainGold__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

USING_NS_CC;
using namespace std;

class GainGold:public CCNode
{
public:
    static GainGold* create(int goldNum);
    GainGold(int goldNum);
    ~GainGold();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
private:
    int goldNum;
    void initContent();
};

class GainGoldFacade:public CCObject
{
public:
    CLASS_INSTANCE(GainGoldFacade);
    bool init();
    
    void showGainGold(int goldNum);
};

#endif /* defined(__threeKingdoms__GainGold__) */
