//
//  NetStateManager.h
//  threeKingdoms
//  Created by sma11case 14-3-6.
//
//

#ifndef __threeKingdoms__NetStateManager__
#define __threeKingdoms__NetStateManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

enum NetState
{
    NetState_noNetWork,
    NetState_wifi,
    NetState_other,
};

class NetStateManager:public CCObject
{
public:
    CLASS_INSTANCE(NetStateManager);
    bool init();
    
    bool getNetState();
};

#endif /* defined(__threeKingdoms__NetStateManager__) */
