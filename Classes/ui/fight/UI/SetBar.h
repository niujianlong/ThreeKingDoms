//
//  SetBar.h
//  threeKingdoms
//  Created by sma11case on 14-1-2.
//
//

#ifndef __threeKingdoms__SetBar__
#define __threeKingdoms__SetBar__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class SetBar:public CCNode
{
public:
    CREATE_FUNC(SetBar);
    virtual bool init();
    
    SetBar();
    ~SetBar();
    
    virtual void onEnter();
    virtual void onExit();
private:
    void initContent();
    CCSprite *barBg;
    CCControlButton *showBtn;
    
    CCControlButton *setBtn;
    
    bool isShow;
    void showBtnHandler();
    void showBar();
    void hideBar();
    void openSet();
    void openRecharge();
    void back();
};

#endif /* defined(__threeKingdoms__SetBar__) */
