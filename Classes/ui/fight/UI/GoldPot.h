//
//  GoldPot.h
//  threeKingdoms
//
//  Created by .m on 14-2-12.
//
//

#ifndef __threeKingdoms__GoldPot__
#define __threeKingdoms__GoldPot__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class GoldPot:public CCNode
{
public:
    CREATE_FUNC(GoldPot);
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
private:
    void initContent();
    int gainGold;
};

class GoldPotFacade:public CCObject
{
public:
    CLASS_INSTANCE(GoldPotFacade);
    bool init();
    
    void showGoldPot();
    
private:
    
};

#endif /* defined(__threeKingdoms__GoldPot__) */
