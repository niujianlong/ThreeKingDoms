//
//  LoadingScene.cpp
//  threeKingdoms
//  Created by sma11case 14-1-13.
//
//

#include "LoadingScene.h"
#include "GameUtils.h"
#include "FightSceneFacade.h"
#include "UserData.h"
#include "SceneRule.h"
#include "NPCRule.h"
#include "ResourceManager.h"
#include "AnimationUtils.h"

CCScene* LoadingScene::scene()
{
    CCScene *scene = CCScene::create();
    LoadingScene *loading = LoadingScene::create();
    scene->addChild(loading);
    return scene;
}

LoadingScene::LoadingScene()
{
    
}

LoadingScene::~LoadingScene()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/loadingScene/loadingScene.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("loadingScene.png");
}

bool LoadingScene::init()
{
    if(!CCLayer::init()){
        return false;
    }
    
    initContent();
    return true;
}

void LoadingScene::initContent()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/loadingScene/loadingScene.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/loadingScene/loading_fire.plist");
    CCSprite *role = CCSprite::createWithSpriteFrameName("loadingScene_role.png");
    addChild(role);
    role->setPosition(ccp(240, 0));
    
    CCSprite *logo = CCSprite::createWithSpriteFrameName("loadingScene_logo.png");
    addChild(logo);
    logo->setPosition(ccp(0, 20));
    
    frame = CCSprite::createWithSpriteFrameName("loadingScene_frame.png");
    addChild(frame);
    frame->setPosition(ccp(0, -150));
    
    loadingBar = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("loadingScene_bar.png"));
    loadingBar->setType(kCCProgressTimerTypeBar);
    loadingBar->setBarChangeRate(ccp(1, 0));
    loadingBar->setMidpoint(ccp(0, 0));
    loadingBar->setPercentage(0);
    
    frame->addChild(loadingBar);
    loadingBar->setPosition(getCenterPosition(frame));
    
    fire = CCSprite::createWithSpriteFrameName("loading_fire_0000.png");
    fire->setAnchorPoint(ccp(1, 0.5));
    frame->addChild(fire);
    fire->setPosition(ccp(50, frame->getContentSize().height/2));
    
    CCAnimate *animate = CCAnimate::create(INSTANCE(AnimationUtils)->getCommonAnimation("ui/loadingScene/loading_fire.plist", "loading_fire",0.07f));
    CCRepeatForever *repeat = CCRepeatForever::create(animate);
    fire->runAction(repeat);
    
    
}

void LoadingScene::onEnter()
{
    CCLayer::onEnter();
    setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    startLoad();
}

void LoadingScene::onExit()
{
    CCLayer::onExit();
    removeAllChildren();
}

void LoadingScene::startLoad()
{
    int sceneId = INSTANCE(UserData)->getCurrentSceneId();
    
    //npc资源
    vector<int> npcId = INSTANCE(SceneRule)->getAllNpcId(sceneId);
    for(int i=0;i<npcId.size();i++){
        vector<string> tv = INSTANCE(ResourceManager)->getNpcResourceImg(npcId[i]);
        resourceVector.insert(resourceVector.end(), tv.begin(),tv.end());
    }
    //主角资源
    vector<string> rv = INSTANCE(ResourceManager)->getRoleResourceImg(INSTANCE(UserData)->getCurrentRoleId());
    resourceVector.insert(resourceVector.end(), rv.begin(), rv.end());
    //地图和ui资源
    resourceVector.push_back(CCString::createWithFormat("maps/%d.png",sceneId)->getCString());
    resourceVector.push_back("ui/fightUI/fightUI.png");
    
    currentLoadNum = 0;
    for(int i=0;i<resourceVector.size();i++){
        CCTextureCache::sharedTextureCache()->addImageAsync(resourceVector[i].c_str(), this, callfuncO_selector(LoadingScene::loadHandler));
    }
}

void LoadingScene::loadHandler()
{
    currentLoadNum++;
    
    loadingBar->setPercentage(100.0f * float(currentLoadNum) / resourceVector.size());
    int py =25 + 545 * (loadingBar->getPercentage() / 100);
    if(py >= 50){
        fire->setPosition(ccp(py , fire->getPositionY()));
    }
    
    if(currentLoadNum >= resourceVector.size()){
        resourceVector.clear();
        INSTANCE(FightSceneFacade)->openFightScene();
    }
}



bool LoadingSceneFacade::init()
{
    return true;
}

void LoadingSceneFacade::openLoadingScene()
{
    CCDirector::sharedDirector()->replaceScene(LoadingScene::scene());
}