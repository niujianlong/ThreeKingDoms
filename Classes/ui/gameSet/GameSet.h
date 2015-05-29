//
//  GameSet.h
//  threeKingdoms
//
//  Created by .m on 14-1-7.
//
//

#ifndef __threeKingdoms__GameSet__
#define __threeKingdoms__GameSet__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;


#define GameSet_musicVolume "gameSetMusicVolume"
#define GameSet_soundVolume "gameSetSoundVolume"


class GameSet:public CCLayer
{
public:
    static GameSet* create(bool showHelp);
    GameSet(bool showHelp);
    ~GameSet();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    void initContent();
    void close();
    
    void musicCallBack(CCControlSlider *sender, CCControlEvent controlEvent);
    void soundCallBack(CCControlSlider *sender, CCControlEvent controlEvent);
    
    void btn1Handler();
    void btn2Handler();
    void btn3Handler();
    void btn4Handler();
    
    bool showHelp;
    
    CCControlButton *wikiBtn;
};




class GameSetFacade:public CCObject
{
public:
    CLASS_INSTANCE(GameSetFacade);
    
    void openGameSet(bool showHelp);
    void closeGameSet();
private:
    GameSet *gameSet;
    bool init();
};

#endif /* defined(__threeKingdoms__GameSet__) */
