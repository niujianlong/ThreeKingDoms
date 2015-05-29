//
//  SingleCharacter.h
//  threeKingdoms
//  Created by sma11case 14-1-2.
//
//

#ifndef __threeKingdoms__SingleCharacter__
#define __threeKingdoms__SingleCharacter__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

#define UnselectAllSingleCharacter "UnselectAllSingleCharacter"

enum FrameType
{
    FrameType_role,
    FrameType_name,
    FrameType_lightEffect,
};

class SingleCharacter:public CCSprite
{
public:
    static SingleCharacter* create(int roleId);
    
    SingleCharacter(int roleId);
    ~SingleCharacter();
    
    virtual bool init();
    
    void setSelect(bool select);
    
    int getRoleId();
    
    void buyHandler();

private:
    int roleId;
    
    CCSprite *lightEffect;
    CCSprite *selectedFlag;
    CCSprite *roleName;
    
    string getFrameName(int roleId,FrameType type);
    string getLightEffect(int roleId);
    
    void initContent();
    
    void click(CCObject *object);
    
    void skillComplete();
    
    CCControlButton *buyBtn;
    
    void buy();
    
};

#endif /* defined(__threeKingdoms__SingleCharacter__) */
