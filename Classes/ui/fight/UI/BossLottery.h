//
//  BossLottery.h
//  threeKingdoms
//
//  Created by .m on 14-2-11.
//
//

#ifndef __threeKingdoms__BossLottery__
#define __threeKingdoms__BossLottery__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "cocos-ext.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class BossLottery:public CCLayer
{
public:
    CREATE_FUNC(BossLottery);
    BossLottery();
    ~BossLottery();
    
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
    void initContent();
    
    void btnHandler();
    
    void rotateComplete();
    
    CCSprite *circle;
    
    CCControlButton *btn;
    CCControlButton *closeBtn;
    
    CCLabelTTF *costLabel;
    
    int getMultiple(int p);
    
    int lightFlag;
    
    void updateLight();
    
    CCArray *array;
    
    void close();
    
    int result;
    
    int times;
};

class BossLotteryLight:public CCSprite
{
public:
    CREATE_FUNC(BossLotteryLight);
    virtual bool init();
    
    void extinguish();
    void light();
private:
    
};

class BossLotteryNotice:public CCNode
{
public:
    static BossLotteryNotice* create(int multiple);
    BossLotteryNotice(int multiple);
    ~BossLotteryNotice();
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
private:
    void initContent();
    int multiple;
};

class BossLotteryFacade:public CCObject
{
public:
    CLASS_INSTANCE(BossLotteryFacade);
    bool init();
    
    void open();
    
    void setBossMultiple(int multiple);
    int getBossMultiple();
    
    void setLotteryStatus(bool show);
    bool getLotteryStatus();
private:
    int bossMultiple;
    bool lotteryShow;
};



#endif /* defined(__threeKingdoms__BossLottery__) */
