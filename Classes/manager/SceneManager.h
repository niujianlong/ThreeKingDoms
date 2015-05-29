//
//  SceneManager.h
//  threeKingdoms
//  Created by sma11case 13-12-26.
//
//

#ifndef __threeKingdoms__SceneManager__
#define __threeKingdoms__SceneManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

enum Child_zOrder
{
    zOrder_moneyNotice,
    zOrder_gainLabelTips,
    zOrder_ui,
    zOrder_tips,
    zOrder_notice,
    zOrder_scene,
    zOrder_guide,
    zOrder_loading,
};

class SceneManager:public CCObject
{
public:
    CLASS_INSTANCE(SceneManager);
    bool init();
    
    void addToCurrentScene(CCNode *child, Child_zOrder zOrder);
private:
    
    int getZOrderByType(Child_zOrder zOrder);
};

#endif /* defined(__threeKingdoms__SceneManager__) */
