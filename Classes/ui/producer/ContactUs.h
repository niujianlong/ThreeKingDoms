//
//  ContactUs.h
//  threeKingdoms
//
//  Created by .m on 14-3-1.
//
//

#ifndef __threeKingdoms__ContactUs__
#define __threeKingdoms__ContactUs__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class ContactUs:public CCLayer
{
public:
    CREATE_FUNC(ContactUs);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
    void initContent();
};

class ContactUsFacade:public CCObject
{
public:
    CLASS_INSTANCE(ContactUsFacade);
    virtual bool init();
    
    void open();
private:
    
};

#endif /* defined(__threeKingdoms__ContactUs__) */
