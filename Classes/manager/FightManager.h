//
//  FightManager.h
//  threeKingdoms
//  Created by sma11case on 13-12-25.
//
//

#ifndef __threeKingdoms__FightManager__
#define __threeKingdoms__FightManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "BaseRole.h"
#include "NPC.h"
#include "BossAvatar.h"

#define NoticeUpdateMoney "noticeUpdateMoney"
#define NoticeUpdateIntegral "noticeUpdateIntegral"
#define NoticeSkillShake "noticeSkillShake"
#define NoticeDebugInfo "noticeDebugInfo"
#define NoticeUpdatePot "noticeUpdatePot"

using namespace std;
USING_NS_CC;

//boss出现时间间隔
#define BossAppearTime 300
//npc逃离速度系数
#define NpcRunAwaySpeedCoefficient 3
//清屏时npc逃离系数
#define ClearNpcSpeedCoefficient 4

class FightManager:public CCObject
{
public:
    CLASS_INSTANCE(FightManager);
    bool init();
    
    void enterFight();
    void exitFight();
    
//    void roleAttack();
    void roleAttack_new(int multiple);
    void roleSkill();
    
    void npcAttack(NPC *npc);
    void npcSkill(int skillId);
    
    int getCurrentRate();

    
    void addMoney(int money);
    void addIntegral(int integral);
    void addAnger(int anger);
    
    bool enoughMoney();
    bool enoughAnger();
    float getAnger();
    
    int getRow(int positionY);
    
    vector<int> getDebugInfo();
    
    int getAttackMultiple();
    void setAttackMultiple(int multiple);
    
    int getEvenStrokes();
    
    void setCreateBossCallSelect();
    //生产boss
    void createBoss();
    //生产部队
    void createTroops(int type);
    
    void setBossDeadStatus(BossStatus status);
    BossStatus getBossDeadStatus();
    void setTroopsAppear(bool appear);
    bool getTroopsAppear();
    
    bool npcCanAttackRole(NPC *npc);
    
    void addBossIndex();
    
    void setMustHitbale(bool param);
    
    int getCurrentBossId();
    
    bool getSomethingGood();
    
    bool isFinalBoss(int bossId);
    
    bool getIsFighting();
    
    void pauseFight();
    void resumeFight();
    
    vector<int> getCurrentBossVector();
    
    void startGuide();
    void endGuide();
private:
    BaseRole* getRole();
    //当前倍率
    int currentRate;
    //当前怒气
    int currentAnger;
    //攻击消耗
    int attackCost;
    //连招最大次数
    int evenStrokes;
    //boss状态 (出现、消失、死亡)
    BossStatus bossStatus;
    //送分部队出现
    bool troopsAppear;
    //本轮是否结束
    bool currentFightEnd;
    //百分百命中技能
    bool mustHitable;
    
//    //当前阵型index
//    int currentFormationIndex;
    //当前阵型数组
    vector<vector<int> > formationVector;
    //当前boss index
    int currentBossIndex;
    //boss数组
    vector<int> bossVector;
    //从boss数组中选取id至currentBossVector中
    void selectBossId();
    //当前boss数组
    vector<int> currentBossVector;
    //当前技能兵数组
    vector<int> skillNpcVector;
    
    //生产npc
    void createNpc();
   
    //生产技能npc
    void createSkillNpc();
    
    //是否闪避
    bool npcMiss(NPC *npc);
    //是否攻击范围内
    bool attackabel(CCRect attackRect,CCRect hurtRect);
    
    
    //各种参数什么的,好烦人orz
//    float crpW,dp,dpW,ccpW,acpW;
//    
//    float getCRP(CCRect attackRect,CCRect hurtRect);
//    
//    float getCCP();
//    
    float getACP();
//
//    int getRoleCurrentDamage(BaseRole *role, NPC *npc);
//
//
//
//    float currentCCP;
    
    
    void changeCCP();
    int loseTotle;
    int winTotle;
    //就是出分周期啦
    bool somethingGood;
    
    //出分周期开始、结束时间
    int startTime,endTime;
    
    
    void skill(int skillId);
    
    void skill_30001();
    void skill_30002();
    void skill_30003();
    void skill_30004();
    void skill_30005();
    void skill_30006();
    
    //本轮攻击是否成功
    bool attackNpcSuccess();
    //获取本轮攻击获得分数
    int getGainScore();
    int currentGainScore;
    bool attackSuccess;
    
    //得分系数
    float scoreCoefficient;
    //周期得分系数加成
    float cycleScoreCoefficient;
    //攻击得分系数加成
    float attackScoreCoefficient;
    //攻击得分倍数
    int attackMultiple;
    vector<int> scoreVector;
    
    int fightMusicType;
    int bossMusicType;
    int troopsMusicType;
    
    bool isFighting;
};

#endif /* defined(__threeKingdoms__FightManager__) */
