//
//  CommonBg.h
//  threeKingdoms
//  Created by sma11case 14-2-7.
//
//

#ifndef __threeKingdoms__CommonBg__
#define __threeKingdoms__CommonBg__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class CommonBg:public CCNode
{
public:
//    CREATE_FUNC(CommonBg);
    static CommonBg *create(string title);
    CommonBg(string title);
    ~CommonBg();
    
    virtual bool init();
private:
    void initContent();
    string title;
};

#endif /* defined(__threeKingdoms__CommonBg__) */
