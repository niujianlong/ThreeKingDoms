//
//  IosNetState.h
//  threeKingdoms
//  Created by sma11case on 14-3-6.
//
//

#ifndef __threeKingdoms__IosNetState__
#define __threeKingdoms__IosNetState__

#include <iostream>
#include "cocos2d.h"
#include "NetStateManager.h"

USING_NS_CC;
using namespace std;

class IosNetState:public CCObject
{
public:
    NetState static getIosNetState();
    string static getIosVersion();
    
    void static goToAppStore(const char* url);
};

#endif /* defined(__threeKingdoms__IosNetState__) */
