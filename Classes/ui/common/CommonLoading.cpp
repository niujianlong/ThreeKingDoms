//
//  CommonLoading.cpp
//  threeKingdoms
//  Created by sma11case on 14-3-5.
//
//

#include "CommonLoading.h"
#include "GameUtils.h"
#include "SceneManager.h"

bool CommonLoading::init()
{
    if(!CCLayer::create()){
        return false;
    }
    initContent();
    return true;
}

void CommonLoading::initContent()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 122));
    addChild(layer);
    CCSprite *fire = CCSprite::create("common/fire_loading.png");
    CCRepeatForever *action = CCRepeatForever::create(CCRotateBy::create(1.0, 360));
    fire->runAction(action);
    addChild(fire);
    fire->setPosition(ccp(winSize.width/2, winSize.height/2));
}

void CommonLoading::onEnter()
{
    ADD_TOUCH;
    CCLayer::onEnter();
}

void CommonLoading::onExit()
{
    REMOVE_TOUCH;
    CCLayer::onExit();
}

bool CommonLoading::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

bool CommonLoadingFacade::init()
{
    loading = NULL;
    return true;
}

void CommonLoadingFacade::showLoading()
{
    if(loading == NULL){
        loading = CommonLoading::create();
        INSTANCE(SceneManager)->addToCurrentScene(loading, zOrder_loading);
    }
    
}

void CommonLoadingFacade::hideLoading()
{
    if(loading != NULL){
        loading->removeFromParent();
        loading = NULL;
    }
}
