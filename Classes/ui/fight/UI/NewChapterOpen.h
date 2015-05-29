//
//  NewChapterOpen.h
//  threeKingdoms
//  Created by sma11case 14-1-8.
//
//

#ifndef __threeKingdoms__NewChapterOpen__
#define __threeKingdoms__NewChapterOpen__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class NewChapterOpen:public CCNode
{
public:
    static NewChapterOpen* create(int sceneId);
    NewChapterOpen(int sceneId);
    ~NewChapterOpen();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
private:
    int sceneId;
    void initContent();
};

class NewChapterOpenManager:public CCObject
{
public:
    CLASS_INSTANCE(NewChapterOpenManager);
    bool init();
    
    void showNewChapterOpen(int sceneId);
};

#endif /* defined(__threeKingdoms__NewChapterOpen__) */
