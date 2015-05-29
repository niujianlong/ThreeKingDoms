//
//  CreateCharacter.h
//  threeKingdoms
//  Created by sma11case on 14-1-2.
//
//

#ifndef __threeKingdoms__CreateCharacter__
#define __threeKingdoms__CreateCharacter__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "TimeManager.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class CreateCharacter:public CCLayer
{
public:
    CREATE_FUNC(CreateCharacter);
    
    CreateCharacter();
    ~CreateCharacter();
    
    virtual bool init();
    
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    void onChangeAccount(CCObject* sender);
private:
    CCArray *characterArray;
    
    void initContent();
    
    void startGame();
    
    void unselectAll();
    
    ccColor4B getColor(TimeType type);
    
    CCControlButton* changeAccount;
    CCLabelBMFont* text;
};

#endif /* defined(__threeKingdoms__CreateCharacter__) */
