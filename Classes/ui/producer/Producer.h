//
//  Producer.h
//  threeKingdoms
//  Created by sma11case 14-2-23.
//
//

#ifndef __threeKingdoms__Producer__
#define __threeKingdoms__Producer__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class Producer:public CCLayerColor
{
public:
    CREATE_FUNC(Producer);
    Producer();
    ~Producer();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
    void initContent();
    
};

#endif /* defined(__threeKingdoms__Producer__) */
