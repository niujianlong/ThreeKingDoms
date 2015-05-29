//
//  Help.h
//  threeKingdoms
//  Created by sma11case 14-2-13.
//
//

#ifndef __threeKingdoms__Help__
#define __threeKingdoms__Help__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class Help:public CCLayer
{
public:
    static Help* create(int sceneId);
    Help(int sceneId);
    ~Help();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
    void initContent();
    int sceneId;
};



class HelpFacade:public CCObject
{
public:
    CLASS_INSTANCE(HelpFacade);
    bool init();
    
    void open(int sceneId);
private:
    
};

bool compareNpc(int npcId_1,int npcId_2);

#endif /* defined(__threeKingdoms__Help__) */
