//
//  SingleHelpNpc.h
//  threeKingdoms
//  Created by sma11case 14-2-13.
//
//

#ifndef __threeKingdoms__SingleHelpNpc__
#define __threeKingdoms__SingleHelpNpc__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class SingleHelpNpc:public CCNode
{
public:
    static SingleHelpNpc* create(int npcId,bool isRole = false);
    SingleHelpNpc(int npcId,bool isRole);
    ~SingleHelpNpc();
    
    virtual bool init();
    
private:
    void initContent();
    int npcId;
    bool isRole;
};

#endif /* defined(__threeKingdoms__SingleHelpNpc__) */
