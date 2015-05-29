//
//  BossAvatar.h
//  threeKingdoms
//  Created by sma11case 14-1-16.
//
//

#ifndef __threeKingdoms__BossAvatar__
#define __threeKingdoms__BossAvatar__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "GameUtils.h"

using namespace std;
USING_NS_CC;

enum BossStatus
{
    BossStatus_appear,
    BossStatus_disappear,
    BossStatus_dead,
};

class BossAvatar:public CCSprite
{
public:
    static BossAvatar* create(int bossId);
    BossAvatar(int bossId);
    ~BossAvatar();
    
    virtual bool init();
    
    void setStatus(BossStatus status);
    
    void updateMultiple();
    
    virtual void onEnter();
    virtual void onExit();
private:
    int bossId;
    CCLabelBMFont *deadFlag;
    CCLabelTTF *time;
    void updateTime();
    int currentTime;
    
    void showTips();
};

class BossAvatarLayer:public CCLayer
{
public:
    CREATE_FUNC(BossAvatarLayer);
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    
};

class BossAvatarFacade:public CCObject
{
public:
    CLASS_INSTANCE(BossAvatarFacade);
    bool init();
    
    BossAvatarLayer* setBossAvatar(int currentBossId = 0);
    void showBossAvatar(int bossId,BossStatus status);
    void showBossMultiple(int bossId);
    void resetBossStatus();
    void removeAll();
    
    void pause();
    void resume();
    
    void setAvatarVisible(bool param);
private:
    BossAvatarLayer *layer;
    CCDictionary *dic;
    
    void disappearHandler();
};



#endif /* defined(__threeKingdoms__BossAvatar__) */
