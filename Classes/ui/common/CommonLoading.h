//
//  CommonLoading.h
//  threeKingdoms
//  Created by sma11case 14-3-5.
//
//

#ifndef __threeKingdoms__CommonLoading__
#define __threeKingdoms__CommonLoading__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class CommonLoading:public CCLayer
{
public:
    CREATE_FUNC(CommonLoading);
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
    void initContent();
};

class CommonLoadingFacade:public CCObject
{
public:
    CLASS_INSTANCE(CommonLoadingFacade);
    bool init();
    
    void showLoading();
    void hideLoading();
private:
    CommonLoading *loading;
};

#endif /* defined(__threeKingdoms__CommonLoading__) */
