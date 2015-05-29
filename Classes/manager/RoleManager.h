//
//  RoleManager.h
//  threeKingdoms
//  Created by sma11case 13-12-27.
//
//

#ifndef __threeKingdoms__RoleManager__
#define __threeKingdoms__RoleManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class RoleManager:public CCObject
{
public:
    CLASS_INSTANCE(RoleManager);
    bool init();
    
    int getRoleId();
};

#endif /* defined(__threeKingdoms__RoleManager__) */
