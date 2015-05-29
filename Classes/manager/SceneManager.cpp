//
//  SceneManager.cpp
//  threeKingdoms
//  Created by sma11case on 13-12-26.
//
//

#include "SceneManager.h"

bool SceneManager::init()
{
    return true;
}

void SceneManager::addToCurrentScene(cocos2d::CCNode *child, Child_zOrder zOrder)
{
    CCDirector::sharedDirector()->getRunningScene()->addChild(child,getZOrderByType(zOrder));
}

int SceneManager::getZOrderByType(Child_zOrder zOrder)
{
    int result = 0;
    switch (zOrder) {
        case zOrder_moneyNotice:
            result = 100;
            break;
        case zOrder_gainLabelTips:
            result = 101;
            break;
        case zOrder_ui:
            result = 102;
            break;
        case zOrder_tips:
            result = 103;
            break;
        case zOrder_notice:
            result = 104;
            break;
        case zOrder_scene:
            result = 105;
            break;
        case zOrder_guide:
            result = 106;
            break;
        case zOrder_loading:
            result = 107;
            break;
        default:
            break;
    }
    return result;
}
