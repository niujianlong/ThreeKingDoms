//
//  BaseRole.h
//  threeKingdoms
//
//  Created by .m on 13-12-24.
//
//

#ifndef __threeKingdoms__BaseRole__
#define __threeKingdoms__BaseRole__

#include <iostream>
#include "cocos2d.h"
#include "RoleRule.h"

USING_NS_CC;
using namespace std;

class BaseRole:public CCNode
{
public:
    static BaseRole* create(int roleId);
    
    BaseRole(int roleId);
    ~BaseRole();
    
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    RoleDirection getRoleDirection();
    
    CCRect getAttackRect();
    CCRect getHurtRect();
    
    int getRoleId();
    
    int getSkillCost();
    
    int getSkillId();
    
    int getRow();
    
    void playHurt(int attackPenalty);
protected:
    int roleId;
    float speedX;
    float speedY;
    float attackSpeed;
    float speedCoefficient;
    
    RoleStatus currentRoleStatus;
    
    RoleDirection currentRoleDirection;
    CCSprite *role;
    
    void initRole();
    
    void playRun();
    void playStand();
    
    void playAttack();
    void attackComplete();
    void allowNextAttack();
    void startAttack();
    
    void hurtComplete();
    
    void playSkill();
    void skillComplete();
    void startSkill();
    
    void playEffect(RoleStatus status);
    
    void joyStickHandler(CCString *direction);
    
    void setRolePosition(CCPoint p);
    
    bool isAttacking();
    
    bool attackCompleted;
    
    int evenStrokes;
    
    int getAttackMultiple();
    
    CCAnimate* getAnimate(RoleStatus status,float duration = 0.10);
};

#endif /* defined(__threeKingdoms__BaseRole__) */
