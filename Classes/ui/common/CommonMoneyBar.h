//
//  CommonMoneyBar.h
//  threeKingdoms
//  Created by sma11case on 14-2-8.
//
//

#ifndef __threeKingdoms__CommonMoneyBar__
#define __threeKingdoms__CommonMoneyBar__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class CommonMoneyBar:public CCNode
{
public:
    CREATE_FUNC(CommonMoneyBar);
    CommonMoneyBar();
    ~CommonMoneyBar();
    
    virtual bool init();
    
//    void setNum(int num);
    void updateBar();
private:
    void initContent();
    
    CCProgressTimer *moneyBar;
    CCLabelBMFont *moneyLabel;
};

#endif /* defined(__threeKingdoms__CommonMoneyBar__) */
