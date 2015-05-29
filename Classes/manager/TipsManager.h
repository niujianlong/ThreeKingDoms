//
//  TipsManager.h
//  threeKingdoms
//  Created by sma11case 14-2-24.
//
//

#ifndef __threeKingdoms__TipsManager__
#define __threeKingdoms__TipsManager__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class CommonTips:public CCNode
{
public:
    static CommonTips* create(const char* tipsContent);
    virtual bool init();
    
    CommonTips(const char* tipsContent);
    ~CommonTips();
    
    void setString(const char* tipsContent);
    
private:
    const char* tipsContent;
    CCLabelTTF* label;
    CCScale9Sprite *bg;
};

class TipsManager:public CCObject
{
public:
    CLASS_INSTANCE(TipsManager);
    bool init();
    
    void showTips(const char* tipsContent,CCPoint p);
private:
    bool isShowing;
    CommonTips* createTips(const char* tipsContent);
    CommonTips* tips;
    
    void hideHandler();
    
    CCPoint getTipsPosition(CCPoint p);
};



#endif /* defined(__threeKingdoms__TipsManager__) */
