//
//  FightManager.cpp
//  threeKingdoms
//
//  Created by .m on 13-12-25.
//
//

#include "FightManager.h"
#include "FightSceneFacade.h"
#include "NPCManager.h"
#include "GameUtils.h"
#include "RoleRule.h"
#include "RoleManager.h"
#include "FormationRule.h"
#include "SceneRule.h"
#include "StringUtils.h"
#include "SystemConfigRule.h"
#include "AnimationUtils.h"
#include "ModelRule.h"
#include "UserData.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "GainGold.h"
#include "NPCRule.h"
#include "LevelUp.h"
#include "NewChapterOpen.h"
#include "TitleRule.h"
#include "ComboLayer.h"
#include "NoticeManager.h"
#include "BossAvatar.h"
#include "BossLottery.h"
#include "Task.h"
#include "GuideManager.h"

bool FightManager::init()
{
    currentRate = 1;
    currentAnger = INSTANCE(UserData)->getAnger();
    
    currentBossIndex = 0;
    
    attackCost = INSTANCE(SystemConfigRule)->getAttackCost();
    
    loseTotle = INSTANCE(UserData)->getTotleCost();
    winTotle = INSTANCE(UserData)->getTotleGain();

    somethingGood = true;
    
    isFighting = false;
    return true;
}

void FightManager::enterFight()
{
    int sceneId = INSTANCE(UserData)->getCurrentSceneId();
//    bossVector = INSTANCE(SceneRule)->getSceneBossId(sceneId);
    selectBossId();
    INSTANCE(BossAvatarFacade)->setBossAvatar(INSTANCE(UserData)->getChapterStatus(INSTANCE(UserData)->getCurrentSceneId()));
    int tempChapterStatus = INSTANCE(UserData)->getChapterStatus(sceneId);
    for(int i=0;i<currentBossVector.size();i++){
        if(currentBossVector[i] == tempChapterStatus){
            currentBossIndex = i;
        }
    }
    
    
    bossStatus = BossStatus_appear;
    
    formationVector = INSTANCE(SceneRule)->getSceneFormationVector(sceneId);
    
    skillNpcVector = INSTANCE(SceneRule)->getSkillNpcId(sceneId);
    changeCCP();
    
    scoreCoefficient = INSTANCE(SceneRule)->getScoreCoefficient(sceneId);
    cycleScoreCoefficient = INSTANCE(SceneRule)->getCycleScoreCoefficientAddition(sceneId);
    attackScoreCoefficient = INSTANCE(SceneRule)->getAttackScoreCoefficientAddition(sceneId);
    
    int moneyType = 1;
    int currentWinMoney = INSTANCE(UserData)->getTotleGain();
    if(currentWinMoney <2000){
        moneyType = 1;
    }else if(currentWinMoney >= 2000 && currentWinMoney < 5000){
        moneyType = 2;
    }else{
        moneyType = 3;
    }
    scoreVector = INSTANCE(SceneRule)->getScoreVector(sceneId,moneyType);
    evenStrokes = INSTANCE(TitleRule)->getEvenStrokes(INSTANCE(UserData)->getTitleLevel());
    
    //实时生产npc
    createNpc();
    //定时60秒生产一个技能npc
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(FightManager::createSkillNpc), this, 60, false);
    
    setCreateBossCallSelect();
    
    INSTANCE(NPCManager)->startUpdate();
    mustHitable = false;
    currentRate = INSTANCE(SceneRule)->getSceneMagnification(sceneId);
    CCLOG("场景倍率:%d",currentRate);
    
    fightMusicType = 1 + INSTANCE(GameUtils)->getRandom(2);
    bossMusicType = 1 + INSTANCE(GameUtils)->getRandom(2);
    troopsMusicType = 1 + INSTANCE(GameUtils)->getRandom(2);
    
    INSTANCE(SoundManager)->playFightMusic(fightMusicType);
    
    isFighting = true;
    
    INSTANCE(TaskFacade)->startTask();
}

void FightManager::exitFight()
{
    INSTANCE(UserData)->setChapterStatus(INSTANCE(UserData)->getCurrentSceneId(), getCurrentBossId());
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(INSTANCE(TaskFacade));
    
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    currentBossIndex = 0;
    currentRate = 1;
    somethingGood = true;
    
    INSTANCE(NPCManager)->stopUpdate();
    
    isFighting = false;
    
    if(INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(GuideManager)->setIsGuiding(false);
    }
}

void FightManager::createNpc()
{
    
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(FightManager::createNpc), this);
    //npc数量3-5个
    int npcNum = INSTANCE(SystemConfigRule)->getSentTroopsMinNumber() + INSTANCE(GameUtils)->getRandom(INSTANCE(SystemConfigRule)->getSentTroopsMaxNumber() - INSTANCE(SystemConfigRule)->getSentTroopsMinNumber() + 1);
    //时间间隔5-10秒
    int refreshTime = INSTANCE(SystemConfigRule)->getSendTroopsMinTime() + INSTANCE(GameUtils)->getRandom(INSTANCE(SystemConfigRule)->getSendTroopsMaxTime() - INSTANCE(SystemConfigRule)->getSendTroopsMinTime() + 1);
    
    if(!INSTANCE(GuideManager)->getIsGuiding()){
        if(bossStatus == BossStatus_appear){
            int sceneId = INSTANCE(UserData)->getCurrentSceneId();
            vector< vector<float> > nv;
            vector<int> npcId = INSTANCE(SceneRule)->getNpcId(sceneId);
            vector<float> npcP = INSTANCE(SceneRule)->getNpcProbabilitys(sceneId);
            for(int i=0;i<npcId.size();i++){
                vector<float> temp;
                temp.push_back(npcId[i]);
                temp.push_back(npcP[i]);
                nv.push_back(temp);
            }
            
            for(int i=0;i<npcNum;i++){
                int npcId = INSTANCE(GameUtils)->getRandomFromVector(nv);
                INSTANCE(NPCManager)->createRandomNpc(npcId);
            }
        }
    }
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(FightManager::createNpc), this, refreshTime, false);
}

void FightManager::createBoss()
{
    //提示 xxx出现
    //boss死后重新倒计时
    int bossId = currentBossVector[currentBossIndex];
    INSTANCE(NPCManager)->createRandomNpc(bossId,true);
    
    INSTANCE(NoticeManager)->showNotice(ccp(CCDirector::sharedDirector()->getWinSize().width/2, 500), 3, "fightImg/bossNoticeBg.png", "font/font_common.fnt", INSTANCE(NPCRule)->getNpcName(bossId) + "出现",ccp(-50,-6));
    
    INSTANCE(SoundManager)->playBossMusic(bossMusicType);
    INSTANCE(BossLotteryFacade)->open();
}

void FightManager::createSkillNpc()
{
    if(bossStatus == BossStatus_appear){
        int sceneId = INSTANCE(UserData)->getCurrentSceneId();
        if(INSTANCE(UserData)->getSkillNum() == 0){
            int skillNpcId = skillNpcVector[INSTANCE(GameUtils)->getRandom(skillNpcVector.size())];
            INSTANCE(NPCManager)->createRandomNpc(skillNpcId,false);
        }else{
            if(INSTANCE(GameUtils)->getRandomFromFloat(INSTANCE(SceneRule)->getSkillNpcProbability(sceneId))){
                int skillNpcId = skillNpcVector[INSTANCE(GameUtils)->getRandom(skillNpcVector.size())];
                INSTANCE(NPCManager)->createRandomNpc(skillNpcId,false);
            }
        }
    }
    
}

void FightManager::createTroops(int type)
{
    //提示 xx部队出现
    //部队出现后主角命中几率上升至100%
    troopsAppear = true;
    int formationId;
    if(type == 0){
        //出征部队
        formationId = formationVector[0][INSTANCE(GameUtils)->getRandom(formationVector[0].size())];
    }else{
        //巡逻部队
        formationId = formationVector[1][INSTANCE(GameUtils)->getRandom(formationVector[1].size())];
    }
    
    vector<int> npcIds = INSTANCE(FormationRule)->getFormationNpcVector(formationId);
    RoleDirection direction = INSTANCE(GameUtils)->getRandomFromFloat(0.5)?RoleDirection_left:RoleDirection_right;
    int formationType = INSTANCE(FormationRule)->getFormationType(formationId);
    TroopsType troopsType = formationType == 1?TroopsType_attack:TroopsType_noAttack;
    for(int i=0;i<npcIds.size();i++){
        if(npcIds[i] != 0){
            INSTANCE(NPCManager)->createTroopsNPC(npcIds[i], i, direction,INSTANCE(FormationRule)->getFormationSpeed(formationId),troopsType);
        }
    }
    
    string troopsNotice;
    if(troopsType == TroopsType_attack){
        troopsNotice = "征战部队出现";
    }else{
        troopsNotice = "巡逻部队出现";
    }
    INSTANCE(NoticeManager)->showNotice(ccp(CCDirector::sharedDirector()->getWinSize().width/2, 500), 3, "fightImg/bossNoticeBg.png", "font/font_common.fnt", troopsNotice,ccp(-50,-6));
    
    INSTANCE(SoundManager)->playTroopsMusic(troopsMusicType);
}

void FightManager::addBossIndex()
{
    if(currentBossIndex + 1 >= currentBossVector.size()){
        currentBossIndex = 0;
        currentFightEnd = true;
    }else{
        currentBossIndex++;
    }
}

BaseRole* FightManager::getRole()
{
    return INSTANCE(FightSceneFacade)->getRole();
}

bool FightManager::enoughMoney()
{
    int currentMoney = INSTANCE(UserData)->getCurrentMoney();
    if(currentMoney < (attackCost * currentRate * attackMultiple)){
        return false;
    }
    return true;
}

bool FightManager::enoughAnger()
{
    if(currentAnger >= getRole()->getSkillCost()){
        int skillNum = INSTANCE(UserData)->getSkillNum();
        INSTANCE(UserData)->setSkillNum(skillNum + 1);
        return true;
    }
    return false;
}

float FightManager::getAnger()
{
    return float(currentAnger) / float(getRole()->getSkillCost());
}

void FightManager::roleSkill()
{
//    currentAnger -= getRole()->getSkillCost();
    currentAnger = 0;
    INSTANCE(UserData)->setAnger(currentAnger);
    skill(getRole()->getSkillId());
}

void FightManager::roleAttack_new(int multiple)
{
    attackMultiple = multiple;

    attackSuccess = attackNpcSuccess();
    
    int gainGold = 0;
    CCRect rR = getRole()->getAttackRect();
    CCArray *array = INSTANCE(NPCManager)->getAllNpc();
    
    CCArray *attackedNpc = CCArray::create();
    
    for(int i=array->count() - 1;i >= 0;i--){
        NPC *npc = (NPC *)array->objectAtIndex(i);
        CCRect nR = npc->getHurtRect();
        
        if(attackabel(rR,nR)){
            attackedNpc->addObject(npc);
        }
    }
    
    currentGainScore = 0;
    int finalScore=0;
    if(attackSuccess){
        currentGainScore = getGainScore();
        //周期加成
        float coefficient = somethingGood?(scoreCoefficient + cycleScoreCoefficient):scoreCoefficient;
        //攻击加成
        coefficient = coefficient + getACP() * attackScoreCoefficient;
        finalScore = currentGainScore * coefficient;
    }
    
    
    for(int i=0;i<attackedNpc->count();i++){
        NPC *npc = (NPC *)attackedNpc->objectAtIndex(i);
        int npcGold = INSTANCE(NPCRule)->getNpcMoney(npc->getNpcId());
        if(attackSuccess){
            if((gainGold + npcGold) <= finalScore){
                gainGold += npcGold;
                npc->playHurt(true);
            }else{
                npc->playHurt(false);
            }
        }else{
            npc->playHurt(false);
        }
    }
    
    
    addMoney(-attackCost * attackMultiple);
    loseTotle += attackCost*currentRate;
    INSTANCE(UserData)->setTotleCost(loseTotle);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeDebugInfo);
    if(gainGold >= 80){
        INSTANCE(GainGoldFacade)->showGainGold(gainGold * currentRate * attackMultiple);
    }

    if(attackedNpc->count() > 0){
        INSTANCE(ComboManager)->showCombo(attackMultiple);
    }
}

bool FightManager::npcMiss(NPC *npc)
{
    if(INSTANCE(GameUtils)->getRandomFromFloat(npc->getMiss())){
        return true;
    }else{
        return false;
    }
}

bool FightManager::attackabel(CCRect attackRect,CCRect hurtRect)
{
    return attackRect.intersectsRect(hurtRect);
}

int FightManager::getCurrentRate()
{
    return currentRate;
}

void FightManager::addMoney(int money)
{
    money = money * currentRate;
    if(money > 0){
        winTotle += money;
        INSTANCE(UserData)->setTotleGain(winTotle);
        INSTANCE(UserData)->addCurrentMoney(money);
    }else{
        INSTANCE(UserData)->costCurrentMoney(-money);
    }
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
}


void FightManager::addIntegral(int integral)
{
    int currentIntegral = INSTANCE(UserData)->getCurrentIntegral();
    INSTANCE(UserData)->setCurrentIntegral(currentIntegral + integral);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateIntegral);
    
    evenStrokes = INSTANCE(TitleRule)->getEvenStrokes(INSTANCE(UserData)->getTitleLevel());
}


float FightManager::getACP()
{
    return ((float)loseTotle)/(winTotle + loseTotle + 1);
}

void FightManager::changeCCP()
{
    
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(FightManager::changeCCP), this);
    somethingGood = !somethingGood;
    
    int changeTime;
    if(somethingGood){
        changeTime= INSTANCE(SystemConfigRule)->getScoreConversionCycleMinTime() + INSTANCE(GameUtils)->getRandom( INSTANCE(SystemConfigRule)->getScoreConversionCycleMaxTime() - INSTANCE(SystemConfigRule)->getScoreConversionCycleMinTime() );
    }else{
        changeTime= INSTANCE(SystemConfigRule)->getLoseScoreConversionCycleMinTime() + INSTANCE(GameUtils)->getRandom( INSTANCE(SystemConfigRule)->getLoseScoreConversionCycleMaxTime() - INSTANCE(SystemConfigRule)->getLoseScoreConversionCycleMinTime() );
    }
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(FightManager::changeCCP), this, changeTime, false);
    startTime = INSTANCE(TimeManager)->getSystemTime();
    endTime = startTime + changeTime;
}

void FightManager::addAnger(int anger)
{
    currentAnger += anger;
    INSTANCE(UserData)->setAnger(currentAnger);
}


void FightManager::skill(int skillId)
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeSkillShake);
    
    switch (skillId) {
        case 30001:
            skill_30001();
            break;
        case 30002:
            skill_30002();
            break;
        case 30003:
            skill_30003();
            break;
        case 30004:
            skill_30004();
            break;
        case 30005:
            skill_30005();
            break;
        case 30006:
            skill_30006();
            break;
    }
}

int FightManager::getRow(int positionY)
{
    int result = 0;
    if(positionY >=-280 && positionY < -220){
        result=5;
    }else if(positionY >=-220 && positionY < -160){
        result=4;
    }else if(positionY >=-160 && positionY < -100){
        result=3;
    }else if(positionY >=-100 && positionY < -40){
        result=2;
    }else if(positionY >=-40 && positionY < 20){
        result=1;
    }
    return result;
}

void FightManager::skill_30001()
{
    int gainGold = 0;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCArray *array = INSTANCE(NPCManager)->getAllNpc();
    int roleRow = getRole()->getRow();
    for(int i=array->count() - 1;i >= 0;i--){
        NPC *npc = (NPC *)array->objectAtIndex(i);
        if(roleRow == npc->getRow() && npc->getPosition().x >= -winSize.width/2 && npc->getPosition().x <= winSize.width/2){
            npc->playHurt(true);
            if(npc->getNpcIsDead()){
                gainGold += INSTANCE(NPCRule)->getNpcMoney(npc->getNpcId());
            }
        }
    }
    if(gainGold >= 80){
        INSTANCE(GainGoldFacade)->showGainGold(gainGold * currentRate);
    }
}

void FightManager::skill_30002()
{
    int gainGold = 0;
    CCArray *array = INSTANCE(NPCManager)->getAllNpc();
    CCPoint rp = getRole()->getPosition();
    CCRect rect = CCRectMake(rp.x - 200, rp.y - 200, 400, 400);
    
    for(int i=array->count() - 1;i >= 0;i--){
        NPC *npc = (NPC *)array->objectAtIndex(i);
        if(rect.containsPoint(npc->getPosition())){
            npc->playHurt(true);
            if(npc->getNpcIsDead()){
                gainGold += INSTANCE(NPCRule)->getNpcMoney(npc->getNpcId());
            }
        }
    }
    if(gainGold >= 80){
        INSTANCE(GainGoldFacade)->showGainGold(gainGold * currentRate);
    }
}

void FightManager::skill_30003()
{
    int gainGold = 0;
    CCArray *array = INSTANCE(NPCManager)->getAllNpc();
    int finalScore= 80;
    for(int i=0;i<array->count();i++){
        NPC *npc = (NPC *)array->objectAtIndex(i);
        int npcGold = INSTANCE(NPCRule)->getNpcMoney(npc->getNpcId());
        if((gainGold + npcGold) <= finalScore){
            gainGold += npcGold;
            npc->playHurt(true);
        }else{
            npc->playHurt(false);
        }
    }
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeDebugInfo);
    if(gainGold >= 80){
        INSTANCE(GainGoldFacade)->showGainGold(gainGold * currentRate * attackMultiple);
    }
    INSTANCE(FightSceneFacade)->showSkillHit(30003);
}

void FightManager::skill_30004()
{
    INSTANCE(NPCManager)->keepAllNpcStop(10);
    INSTANCE(FightSceneFacade)->showSkillHit(30004);
    mustHitable = true;
}

void FightManager::skill_30005()
{
    int gainGold = 0;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCArray *array = INSTANCE(NPCManager)->getAllNpc();
    int row_1 = getRole()->getRow();
    int row_2 = 1 + INSTANCE(GameUtils)->getRandom(5);
    while (row_1 == row_2) {
        row_2 = 1 + INSTANCE(GameUtils)->getRandom(5);
    }
    for(int i=array->count() - 1;i >= 0;i--){
        NPC *npc = (NPC *)array->objectAtIndex(i);
        if((row_1 == npc->getRow() || row_2 == npc->getRow()) && npc->getPosition().x >= -winSize.width/2 && npc->getPosition().x <= winSize.width/2){
            npc->playHurt(true);
            if(npc->getNpcIsDead()){
                gainGold += INSTANCE(NPCRule)->getNpcMoney(npc->getNpcId());
            }
        }
    }
    if(gainGold >= 80){
        INSTANCE(GainGoldFacade)->showGainGold(gainGold * currentRate);
    }
}

void FightManager::skill_30006()
{
    int gainGold = 0;
    CCArray *array = INSTANCE(NPCManager)->getAllNpc();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    for(int i=array->count() - 1;i >= 0;i--){
        NPC *npc = (NPC *)array->objectAtIndex(i);
        if(npc->getPosition().x >= -winSize.width/2 && npc->getPosition().x <= winSize.width/2){

            gainGold += INSTANCE(NPCRule)->getNpcMoney(npc->getNpcId());
            npc->stopAll();
            
            CCPoint tp = npc->getPosition();
            float duration = powf(tp.x * tp.x + tp.y *tp.y,0.5) / 200;
            
            CCRotateBy *rotate = CCRotateBy::create(duration, 1600.0f);
            CCScaleTo *scale = CCScaleTo::create(duration, 0.1f);
            CCMoveTo *move = CCMoveTo::create(duration, ccp(0, 0));

            CCSpawn *spawn = CCSpawn::create(scale,rotate,move,NULL);
            CCSequence *action = CCSequence::create(spawn,CCCallFunc::create(npc, callfunc_selector(NPC::removeFromParent)),NULL);
            npc->getSprite()->setAnchorPoint(ccpAdd(ccp(0.0f, 0.3f), npc->getSprite()->getAnchorPoint()));
            npc->runAction(action);
            
            INSTANCE(NPCManager)->removeNPC(npc);
        }
        
    }
    if(gainGold >= 80){
        INSTANCE(GainGoldFacade)->showGainGold(gainGold * currentRate);
    }
}

void FightManager::npcSkill(int skillId)
{
    skill(skillId);
    INSTANCE(SoundManager)->playFightSkill(skillId);
}

void FightManager::npcAttack(NPC *npc)
{
    if(npcCanAttackRole(npc)){
        getRole()->playHurt(npc->getNpcAttackPenalty());
    }
    
}

bool FightManager::npcCanAttackRole(NPC *npc)
{
    CCRect rR = getRole()->getHurtRect();
    CCRect nR = npc->getAttackRect();
    if(attackabel(rR,nR)){
        return true;
    }
    return false;
}


vector<int> FightManager::getDebugInfo()
{
    vector<int> result;

    result.push_back(attackSuccess?1:0);
    result.push_back(currentGainScore);
    result.push_back(somethingGood?1:0);
    return result;
}

bool FightManager::attackNpcSuccess()
{
    if(mustHitable){
        return true;
    }else{
        int currentSceneId = INSTANCE(UserData)->getCurrentSceneId();
        if(troopsAppear){
            //得分部队
            return INSTANCE(GameUtils)->getRandomFromFloat(INSTANCE(SceneRule)->getTroopsHitRate(currentSceneId));
        }else{
            if(somethingGood){
                //得分周期
                return INSTANCE(GameUtils)->getRandomFromFloat(INSTANCE(SceneRule)->getSceneScoreHitRate(currentSceneId));
            }else{
                //吃分周期
                return INSTANCE(GameUtils)->getRandomFromFloat(INSTANCE(SceneRule)->getSceneLoseHitRate(currentSceneId));
            }
        }
    }
}

int FightManager::getGainScore()
{
    int totleSocre = 0;
    for(int i=0;i<scoreVector.size();i++){
        totleSocre += scoreVector[i];
    }
    
    vector<vector<float> > p;
    for(int i=0;i<scoreVector.size();i++){
        vector<float> temp;
        temp.push_back(scoreVector[i]);
        temp.push_back(float(scoreVector[scoreVector.size() - i - 1])/totleSocre);
        p.push_back(temp);
    }
    
    int result = INSTANCE(GameUtils)->getRandomFromVector(p);
    return result;
}

int FightManager::getAttackMultiple()
{
    return attackMultiple;
}

void FightManager::setAttackMultiple(int multiple)
{
    attackMultiple = multiple;
}

int FightManager::getEvenStrokes()
{
    return evenStrokes;
}

void FightManager::setCreateBossCallSelect()
{
    //定时300秒生产一个boss
    if(currentFightEnd){
        INSTANCE(BossAvatarFacade)->resetBossStatus();
        currentFightEnd = false;
        selectBossId();
        INSTANCE(BossAvatarFacade)->setBossAvatar(INSTANCE(UserData)->getChapterStatus(INSTANCE(UserData)->getCurrentSceneId()));
    }else{
        INSTANCE(BossAvatarFacade)->showBossAvatar(currentBossVector[currentBossIndex],BossStatus_appear);
    }
}

void FightManager::setBossDeadStatus(BossStatus status)
{
    bossStatus = status;
    if(bossStatus == BossStatus_disappear || bossStatus == BossStatus_dead){
        //清屏
        CCArray *array = INSTANCE(NPCManager)->getAllNpc();
        for(int i=array->count() - 1;i >= 0;i--){
            NPC *npc = (NPC *)array->objectAtIndex(i);
            npc->acceleratedMove();
        }
        if(bossStatus == BossStatus_dead){
            INSTANCE(BossAvatarFacade)->showBossAvatar(currentBossVector[currentBossIndex],BossStatus_dead);
            addBossIndex();
        }
    }
    
}

BossStatus FightManager::getBossDeadStatus()
{
    return bossStatus;
}

void FightManager::setTroopsAppear(bool appear)
{
    troopsAppear = appear;
    if(!troopsAppear){
        INSTANCE(SoundManager)->playFightMusic(fightMusicType);
    }
}

bool FightManager::getTroopsAppear()
{
    return troopsAppear;
}

void FightManager::setMustHitbale(bool param)
{
    mustHitable = param;
}

int FightManager::getCurrentBossId()
{
    int bossId = currentBossVector[currentBossIndex];
    return bossId;
}

bool FightManager::getSomethingGood()
{
    return somethingGood;
}

bool FightManager::isFinalBoss(int bossId)
{
    if(currentBossVector[currentBossVector.size() - 1] == bossId){
        return true;
    }
    return false;
}

bool FightManager::getIsFighting()
{
    return isFighting;
}

void FightManager::pauseFight()
{
    if(isFighting){
        INSTANCE(NPCManager)->keepAllNpcStop(0);
        CCDirector::sharedDirector()->getScheduler()->pauseTarget(INSTANCE(FightManager));
        CCDirector::sharedDirector()->getScheduler()->pauseTarget(INSTANCE(FightSceneFacade)->getFightScene());
        if(INSTANCE(TaskFacade)->getTask()){
            CCDirector::sharedDirector()->getScheduler()->pauseTarget(INSTANCE(TaskFacade)->getTask());
        }
        CCDirector::sharedDirector()->getScheduler()->pauseTarget(INSTANCE(TaskFacade));
        INSTANCE(BossAvatarFacade)->pause();
    }
}

void FightManager::resumeFight()
{
    if(isFighting){
        INSTANCE(NPCManager)->allNpcStopComplete();
        CCDirector::sharedDirector()->getScheduler()->resumeTarget(INSTANCE(FightManager));
        CCDirector::sharedDirector()->getScheduler()->resumeTarget(INSTANCE(FightSceneFacade)->getFightScene());
        if(INSTANCE(TaskFacade)->getTask()){
            CCDirector::sharedDirector()->getScheduler()->resumeTarget(INSTANCE(TaskFacade)->getTask());
        }
        CCDirector::sharedDirector()->getScheduler()->resumeTarget(INSTANCE(TaskFacade));
        INSTANCE(BossAvatarFacade)->resume();
    }
}

void FightManager::selectBossId()
{
    int sceneId = INSTANCE(UserData)->getCurrentSceneId();
    if(bossVector.size() == 0){
        bossVector = INSTANCE(SceneRule)->getSceneBossId(sceneId);
    }
    currentBossVector.clear();
    int count = INSTANCE(SceneRule)->getSceneBossCount(sceneId);
    for(int i=0;i<count;i++){
        currentBossVector.push_back(bossVector[0]);
        bossVector.erase(bossVector.begin());
    }
}

vector<int> FightManager::getCurrentBossVector()
{
    return currentBossVector;
}

void FightManager::startGuide()
{
    INSTANCE(GuideManager)->setIsGuiding(true);
    INSTANCE(UserData)->setCurrentMoney(500);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(INSTANCE(FightManager));
    if(INSTANCE(TaskFacade)->getTask()){
        CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(INSTANCE(TaskFacade)->getTask());
    }
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(INSTANCE(TaskFacade));
    CCArray *array = INSTANCE(NPCManager)->getAllNpc();
    for(int i=array->count() - 1;i >= 0;i--){
        NPC *npc = (NPC *)array->objectAtIndex(i);
        npc->acceleratedMove();
    }
    INSTANCE(BossAvatarFacade)->pause();
    INSTANCE(TaskFacade)->closeTask();
}


void FightManager::endGuide()
{
    CCArray *array = INSTANCE(NPCManager)->getAllNpc();
    for(int i=array->count() - 1;i >= 0;i--){
        NPC *npc = (NPC *)array->objectAtIndex(i);
        npc->acceleratedMove();
    }
    INSTANCE(GuideManager)->setIsGuiding(false);
    INSTANCE(UserData)->reloadData();
    INSTANCE(BossAvatarFacade)->resume();
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateIntegral);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
    currentAnger = INSTANCE(UserData)->getAnger();
    enterFight();
}
