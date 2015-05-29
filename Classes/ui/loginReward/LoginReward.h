//
//  LoginReward.h
//  threeKingdoms
//  Created by sma11case 14-1-17.
//
//

#ifndef __threeKingdoms__LoginReward__
#define __threeKingdoms__LoginReward__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class LoginReward:public CCLayerColor
{
public:
    CREATE_FUNC(LoginReward);
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
    void initContent();
    
    void receiveReward();
    
    int receiveNum;
};

class LoginRewardSingleReward:public CCSprite
{
public:
    static LoginRewardSingleReward* create(int day);
    LoginRewardSingleReward(int day);
    ~LoginRewardSingleReward();
    
    virtual bool init();
    
private:
    int day;
    string getMoneyIcon();
};

class LoginRewardFacade:public CCObject
{
public:
    CLASS_INSTANCE(LoginRewardFacade);
    bool init();
    
    void open();
};

#endif /* defined(__threeKingdoms__LoginReward__) */
