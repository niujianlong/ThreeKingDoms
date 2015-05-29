//
//  AnimateManager.h
//  threeKingdoms
//  Created by sma11case 14-2-12.
//
//

#ifndef __threeKingdoms__AnimateManager__
#define __threeKingdoms__AnimateManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

USING_NS_CC;
using namespace std;

class AnimateManager:public CCObject
{
public:
    CLASS_INSTANCE(AnimateManager);
    bool init();
    
    void showScaleAnimate(CCNode *target);
    
    void showAnimate(CCNode *target);
    void hideAnimate(CCNode *target);
private:
    
};

#endif /* defined(__threeKingdoms__AnimateManager__) */
