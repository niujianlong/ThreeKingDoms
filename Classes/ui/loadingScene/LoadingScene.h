//
//  LoadingScene.h
//  threeKingdoms
//  Created by sma11case 14-1-13.
//
//

#ifndef __threeKingdoms__LoadingScene__
#define __threeKingdoms__LoadingScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class LoadingScene:public CCLayer
{
public:
    static CCScene* scene();
    LoadingScene();
    ~LoadingScene();
    CREATE_FUNC(LoadingScene);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
private:
    CCSprite *frame;
    CCProgressTimer *loadingBar;
    CCSprite *fire;
    CCLabelTTF *currentLoad;
    void initContent();
    
    void startLoad();
    void loadHandler();
    
    vector<string> resourceVector;
    int currentLoadNum;
};

class LoadingSceneFacade:public CCObject
{
public:
    CLASS_INSTANCE(LoadingSceneFacade);
    bool init();
    
    void openLoadingScene();
private:
};

#endif /* defined(__threeKingdoms__LoadingScene__) */
