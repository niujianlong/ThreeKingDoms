//
//  CreateCharacterBg.h
//  threeKingdoms
//  Created by sma11case 14-1-21.
//
//

#ifndef __threeKingdoms__CreateCharacterBg__
#define __threeKingdoms__CreateCharacterBg__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameUtils.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class CreateCharacterBg:public CCSpriteBatchNode
{
public:
    CREATE_FUNC(CreateCharacterBg);
    virtual bool init();
    
private:
    void initContent();
    CCSprite *bg1;
    CCSprite *bg2;
    
    void update(float t);
};

#endif /* defined(__threeKingdoms__CreateCharacterBg__) */
