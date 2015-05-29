//
//  MoneyLayer.h
//  threeKingdoms
//  Created by sma11case on 13-12-31.
//
//

#ifndef __threeKingdoms__MoneyLayer__
#define __threeKingdoms__MoneyLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class MoneyLayer:public CCLayer
{
public:
    CREATE_FUNC(MoneyLayer);
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
private:
    void initContent();
    
};

class SingleMoney:public CCSprite
{
public:
    static SingleMoney* create(int money);
    SingleMoney(int money);
    ~SingleMoney();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    void removeAndPlaySound();
    
    int getSpriteWidth();
private:
    int num;
    int spriteWidth;
    
    string getImage();
};

class MoneyLayerManager:public CCObject
{
public:
    CLASS_INSTANCE(MoneyLayerManager);
    bool init();
    
    void showMoney(CCPoint position, int num);
    
    void removeLayer();
    string getImage(int num);
    
    void createMoney(int num,CCPoint position);
    void createReduceMoney(int num);
private:
    MoneyLayer *layer;
    CCSpriteBatchNode *iconNode;
    CCSpriteBatchNode *labelNode;
    
    
};

#endif /* defined(__threeKingdoms__MoneyLayer__) */
