//
//  NPC.h
//  threeKingdoms
//  Created by sma11case 13-12-24.
//
//

#ifndef __threeKingdoms__NPC__
#define __threeKingdoms__NPC__

#include <iostream>
#include "cocos2d.h"
#include "RoleRule.h"

using namespace std;
USING_NS_CC;

enum RunAwayStatus
{
    RunAwayStatus_none,
    RunAwayStatus_speedDown,
    RunAwayStatus_speedUp,
};

enum TroopsType
{
    TroopsType_none,
    TroopsType_attack,
    TroopsType_noAttack,
};

class NPC:public CCNode
{
public:
    static NPC* create(int npcId,RoleDirection direction,int speed,bool isBoss,TroopsType troopsType);
    
    NPC(int npcId,RoleDirection direction,int speed,bool isBoss,TroopsType troopsType);
    ~NPC();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    int getNpcId();
    
    void playWalk();
    void playHurt(bool hit);
    void playDie();
    void playStop();
    void playStand();
    void playAttack();
    
    void setNpcStatus(RoleStatus status);
    RoleStatus getNpcStatus();
    
    RoleDirection getCurrentDirection();
    
    CCRect getHurtRect();
    
    CCRect getAttackRect();
    
    float getMiss();
    
    int getRow();
    
    void setIsStop(bool stop);
    
//    int getNpcHp();
    bool getNpcIsDead();
    
    int getNpcMoney();
    int getNpcIntegral();
    int getNpcAnger();
    bool getNpcIsBoss();
    
    void acceleratedMove();
    
    int getNpcAttackType();
    
    TroopsType getNpcTroopsType();
    
    int getNpcAttackPenalty();
    
    void stopAll();
    
    CCSprite *getSprite();
    
    int getSkillId();
private:
    int npcId;
    bool isDead;
    bool isBoss;
    int npcSpeed;
    TroopsType troopsType;
    RoleStatus currentStatus;
    RoleDirection currentDirection;
    CCSprite *npcRole;
    
    void hurtComplete();
    void dieComplete();
    void standComplete();
    
    void startMove(bool changeY);
    void stopMove();
    
    CCAnimate* getAnimate(RoleStatus status);
    
    bool isStop;
    
    CCSize hurtSize;
    int skillId;
    int missRate;
    
    int npcMoney;
    int npcIntegral;
    int npcAnger;
    
    void playBlood();
    
    //加速离开
    bool accelerated;
    
    float standProbability;
    
    void startAttack();
    void attackComplete();
    //被击后反击
    void playAttackBack();
    void attackBackComplete();
    void startAttackBack();
    //被击后逃跑
    void runAway(bool speedUp);
    void runAwayComplete();
    
    RunAwayStatus runAwayStatus;
    
    void playWalkAnimate(bool changeY = false);
    
    int getNpcPositionY();
    
    int npcAttackType;
    
    bool attackable;
    
    void setAttackableHandler();
    
    int attackPenalty;
};


#endif /* defined(__threeKingdoms__NPC__) */
