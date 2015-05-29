//
//  CommonTitleBar.h
//  threeKingdoms
//  Created by sma11case on 14-2-8.
//
//

#ifndef __threeKingdoms__CommonTitleBar__
#define __threeKingdoms__CommonTitleBar__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class CommonTitleBar:public CCNode
{
public:
    CREATE_FUNC(CommonTitleBar);
    CommonTitleBar();
    ~CommonTitleBar();
    
    virtual bool init();
    
    void updateBar();
    
    CCNode* getEventNode();
private:
    void initContent();
    
    CCLabelBMFont *titleLabel;
    CCProgressTimer *titleBar;
    CCLabelTTF *titleLevel;
};

#endif /* defined(__threeKingdoms__CommonTitleBar__) */
