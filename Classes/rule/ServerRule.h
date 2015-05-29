//
//  ServerRule.h
//  threeKingdoms
//  Created by sma11case 14-3-6.
//
//

#ifndef __threeKingdoms__ServerRule__
#define __threeKingdoms__ServerRule__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class ServerRule:public CCObject
{
public:
    CLASS_INSTANCE(ServerRule);
    bool init();
    
    string getVersion();
    string getRechargeUrl();
    string getNewVersionUrl();
private:
    string getServerAttribute(const char *attributeName);
};

#endif /* defined(__threeKingdoms__ServerRule__) */
