//
//  FightUI.h
//  threeKingdoms
//  Created by sma11case on 13-12-27.
//
//

#ifndef __threeKingdoms__FightUI__
#define __threeKingdoms__FightUI__

#include <iostream>
#include "cocos2d.h"
#include "CommonTitleBar.h"
#include "OnlineReward.h"
#include "SetBar.h"

using namespace std;
USING_NS_CC;

class FightUI:public CCLayer
{
public:
    CREATE_FUNC(FightUI);
    
    FightUI();
    ~FightUI();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
private:
    void initContent();
    
    CommonTitleBar *titleBar;
    
    CCProgressTimer *moneyBar;
    CCLabelBMFont *currentRateLabel;
    CCLabelBMFont *moneyLabel;
    CCProgressTimer *potBar;
    CCLabelTTF *potLabel;
    
//    CCLabelTTF *titleLevel;
    
//    int currentRate;
    int currentMoney;
    int currentIntegral;
    int currentUpgradeIntegral;
    
    int maxRate;
    
    int differenceMoney;
    
    void updateMoney();
    void updateIntegral();
    void updatePot();
    
    void showMoneyAnimation();
    
    void update(float t);
    
    OnlineReward* onlineReward;
    
    CCSprite *potSprite;
    SetBar *setBar;
    
    void showPotTips();
    void showExpTips();
};

#endif /* defined(__threeKingdoms__FightUI__) */
