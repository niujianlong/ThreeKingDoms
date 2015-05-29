//
//  ResourceManager.h
//  threeKingdoms
//  Created by sma11case on 14-1-13.
//
//

#ifndef __threeKingdoms__ResourceManager__
#define __threeKingdoms__ResourceManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class ResourceManager:public CCObject
{
public:
    CLASS_INSTANCE(ResourceManager);
    bool init();
    
    vector<string> getNpcResourceImg(int npcId);
    
    vector<string> getRoleResourceImg(int roleId);
private:
};

#endif /* defined(__threeKingdoms__ResourceManager__) */
