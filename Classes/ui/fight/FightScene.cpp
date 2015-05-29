//
//  FightScene.cpp
//  threeKingdoms
//  Created by sma11case on 13-12-24.
//
//

#include "FightScene.h"
#include "GameUtils.h"
#include "JoyStickLayer.h"
#include "NPCManager.h"
#include "FightSceneFacade.h"
#include "SoundManager.h"
#include "FightUI.h"
#include "SystemConfigRule.h"
#include "FightManager.h"
#include "ModelRule.h"
#include "AnimationUtils.h"
#include "SkillRule.h"
#include "UserData.h"
#include "DebugInfoUI.h"
#include "SceneRule.h"
#include "ParticleManager.h"
#include "NoticeManager.h"
#include "BossAvatar.h"
#include "NPCRule.h"
#include "Task.h"
#include "GuideManager.h"

FightScene::FightScene()
{
    handseling = false;
}

FightScene::~FightScene()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

bool FightScene::init()
{
    if(!CCLayer::init()){
        return false;
    }
    this->setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    initMap();
    initRole();
    initUI();
    this->scheduleUpdate();
    return true;
}

void FightScene::onEnter()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(FightScene::shake), NoticeSkillShake, NULL);
    CCLayer::onEnter();
    INSTANCE(FightManager)->enterFight();
    
}

void FightScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    if(INSTANCE(GuideManager)->getIsGuiding()){
        INSTANCE(FightManager)->startGuide();
    }
}

void FightScene::onExit()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NoticeSkillShake);
    INSTANCE(SoundManager)->stopMusic();
    INSTANCE(NPCManager)->removeAllNpc();
    CCLayer::onExit();
    removeAllChildren();
    INSTANCE(FightManager)->exitFight();
    
}

void FightScene::initMap()
{
    mapNode = CCNode::create();
    mapNode->setAnchorPoint(ccp(0.5, 0.5));
    addChild(mapNode);
    CCString *mapName = CCString::createWithFormat("maps/%d.png",INSTANCE(SceneRule)->getSceneImgId(INSTANCE(UserData)->getCurrentSceneId()));
    bg = CCSprite::create(mapName->getCString());
    mapNode->addChild(bg);
    bg->setPosition(ccp(0, 20));
}

void FightScene::initRole()
{
    role = BaseRole::create(INSTANCE(UserData)->getCurrentRoleId());
    role->setPosition(ccp(0, -170));
    mapNode->addChild(role);
    INSTANCE(FightSceneFacade)->setRole(role);
    
}

void FightScene::initUI()
{
    addChild(FightUI::create());
//    addChild(DebugInfoUI::create());
    int sceneId = INSTANCE(UserData)->getCurrentSceneId();
    addChild(INSTANCE(BossAvatarFacade)->setBossAvatar(INSTANCE(UserData)->getChapterStatus(sceneId)));
}

void FightScene::update(float t)
{
    role->setZOrder(320 - role->getPosition().y);
    CCArray *npcArray = INSTANCE(NPCManager)->getAllNpc();
    
    for(int i=0;i<npcArray->count();i++){
        NPC *npc = (NPC *)npcArray->objectAtIndex(i);
        npc->setZOrder(320 - npc->getPosition().y);
    }
    
    if(INSTANCE(UserData)->getCurrentMoney() >= 50 && handseling){
        stopHandsel();
    }else if(INSTANCE(UserData)->getCurrentMoney() < 50 && handseling == false){
        startHandsel();
    }
}

void FightScene::addNpcToScene(NPC *npc)
{
    mapNode->addChild(npc);
}

void FightScene::showSkillHit(int skillId)
{
    float duration;
    if(skillId == 30001){
        CCSprite *skillHit_1 = getSkillHit(skillId);
        skillHit_1->setPosition(role->getPosition());
        skillHit_1->setAnchorPoint(ccp(0.1, skillHit_1->getAnchorPoint().y));
        skillHit_1->setFlipX(true);
        CCSprite *skillHit_2 = getSkillHit(skillId);
        skillHit_2->setPosition(role->getPosition());
        skillHit_2->setAnchorPoint(ccp(0.9, skillHit_1->getAnchorPoint().y));
        
        skillHit_1->setZOrder(role->getZOrder() + 1);
        skillHit_2->setZOrder(role->getZOrder() + 1);
        duration = ((CCActionInterval *)skillHit_1->getActionByTag(-9))->getDuration();
    }else if(skillId == 30002){
        CCSprite *skillHit = getSkillHit(skillId);
        skillHit->setPosition(role->getPosition());
        skillHit->setZOrder(role->getZOrder() + 1);
        duration = ((CCActionInterval *)skillHit->getActionByTag(-9))->getDuration();
    }else if(skillId == 30003){
        CCSprite *skillHit_1 = getSkillHit(skillId);
        skillHit_1->setPosition(ccp(0, -160));
        skillHit_1->setAnchorPoint(ccp(1, skillHit_1->getAnchorPoint().y));
        
        CCSprite *skillHit_2 = getSkillHit(skillId);
        skillHit_2->setPosition(ccp(0, -160));
        skillHit_2->setFlipX(true);
        skillHit_2->setAnchorPoint(ccp(0, skillHit_2->getAnchorPoint().y));
        
        skillHit_1->setZOrder(480);
        skillHit_2->setZOrder(480);
        duration = ((CCActionInterval *)skillHit_1->getActionByTag(-9))->getDuration();
    }else if(skillId == 30004){
        CCSprite *skillHit = getSkillHit(skillId);
        skillHit->setPosition(ccp(0, -260));
        skillHit->setZOrder(580);
        duration = ((CCActionInterval *)skillHit->getActionByTag(-9))->getDuration();
    }else if(skillId == 30005){
        CCSprite *skillHit_3 = getSkillHit(skillId);
        skillHit_3->setPosition(ccp(-100, -100));
        skillHit_3->setZOrder(580);
        skillHit_3->setFlipX(true);
        duration = ((CCActionInterval *)skillHit_3->getActionByTag(-9))->getDuration();
        
        CCSprite *skillHit = getSkillHit(skillId);
        skillHit->setPosition(ccp(100, -200));
        skillHit->setZOrder(580);
        duration = ((CCActionInterval *)skillHit->getActionByTag(-9))->getDuration();
        
        CCSprite *skillHit_2 = getSkillHit(skillId);
        skillHit_2->setPosition(ccp(-100, -300));
        skillHit_2->setZOrder(580);
        skillHit_2->setFlipX(true);
        duration = ((CCActionInterval *)skillHit_2->getActionByTag(-9))->getDuration();
    }else if(skillId == 30006){
        CCSprite *skillHit = CCSprite::create();
        skillHit->setAnchorPoint(INSTANCE(ModelRule)->getSkillHitAnchorPoint(skillId));
        string img = INSTANCE(ModelRule)->getSkillHitFrameName(skillId);
        CCAnimation *animation_1 = INSTANCE(AnimationUtils)->getModelAnimation(skillId, img.c_str(),img.c_str(),0.12,0,16);
        CCAnimation *animation_2 = INSTANCE(AnimationUtils)->getModelAnimation(skillId, img.c_str(),img.c_str(),0.12,17,20);
        
        CCArray *array = CCArray::create();
        for(int i= animation_1->getFrames()->count() - 1;i>=0;i--){
            array->addObject(animation_1->getFrames()->objectAtIndex(i));
        }

        CCAnimation *animation_3 = CCAnimation::create(array, 0.12);
        
        
        CCSequence *action = CCSequence::create(CCAnimate::create(animation_1),CCRepeat::create(CCAnimate::create(animation_2), 4),CCAnimate::create(animation_3),CCCallFuncN::create(skillHit, callfuncN_selector(CCSprite::removeFromParent)),NULL);
        
        skillHit->runAction(action);
        
        skillHit->setPosition(ccp(0, -255));
//        skillHit->setZOrder(580);
        duration = action->getDuration();
        mapNode->addChild(skillHit);
    }
    showSkillName(skillId,duration);
}

CCSprite *FightScene::getSkillHit(int skillId)
{
    string img = INSTANCE(ModelRule)->getSkillHitFrameName(skillId);
    CCAnimation *animation = INSTANCE(AnimationUtils)->getModelAnimation(skillId, img.c_str(),img.c_str(),0.12);
    
    CCSprite *skillHit = CCSprite::createWithSpriteFrameName((img + "_0000.png").c_str());
    
    string imgPath = INSTANCE(ModelRule)->getModelPath(skillId) + img + ".png";
    CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create(imgPath.c_str());
    
    CCSequence *action = CCSequence::create(CCAnimate::create(animation),CCCallFuncN::create(batchNode, callfuncN_selector(CCSpriteBatchNode::removeFromParent)),NULL);
    action->setTag(-9);
    skillHit->runAction(action);
    skillHit->setAnchorPoint(INSTANCE(ModelRule)->getSkillHitAnchorPoint(skillId));
    
    
    mapNode->addChild(batchNode);
    batchNode->addChild(skillHit);
    
    return skillHit;
}

void FightScene::showSkillName(int skillId, float duration)
{
    INSTANCE(NoticeManager)->showNotice(ccp(CCDirector::sharedDirector()->getWinSize().width/2, 500), duration, "fightImg/skillBg.png", "font/font_skillName.fnt", INSTANCE(SkillRule)->getSkillName(skillId));
}

void FightScene::shake()
{
    CCMoveBy *move_1 = CCMoveBy::create(0.08, ccp(8, 8));
    CCMoveBy *move_2 = CCMoveBy::create(0.16, ccp(-16, -16));
    CCMoveBy *move_3 = CCMoveBy::create(0.14, ccp(14, 14));
    CCMoveBy *move_4 = CCMoveBy::create(0.08, ccp(-8, -8));
    CCMoveBy *move_5 = CCMoveBy::create(0.06, ccp(6, 6));
    CCMoveBy *move_6 = CCMoveBy::create(0.04, ccp(-4, -4));
    CCSequence *action = CCSequence::create(move_1,move_2,move_3,move_4,move_5,move_6,NULL);
    mapNode->runAction(action);
}

void FightScene::showAngerEffect(NPC *npc)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCParticleSystem *effect = INSTANCE(ParticleManager)->getParticleByName("angerEffect.plist");
    mapNode->addChild(effect,1000);
    effect->setPosition(ccpAdd(npc->getPosition(),ccp(0, 100)));
    CCPoint p;
    
    if(winSize.width == 1136){
        p = ccp(328,-200);
    }else{
        p = ccp(240,-200);
    }
    
    CCPoint tp = ccpSub(effect->getPosition(), p);
    float duration_2 = powf(tp.x * tp.x + tp.y *tp.y,0.5) / 600;
    
    CCMoveTo *move = CCMoveTo::create(duration_2, p);
    CCSequence *action = CCSequence::create(move,CCDelayTime::create(0.5f),CCCallFunc::create(effect, callfunc_selector(CCParticleSystem::removeFromParent)),NULL);
    effect->runAction(action);
}

void FightScene::startHandsel()
{
    getScheduler()->scheduleSelector(schedule_selector(FightScene::handselGold), this, 10.0f, false);
    handseling=true;
}

void FightScene::stopHandsel()
{
    getScheduler()->unscheduleSelector(schedule_selector(FightScene::handselGold), this);
    handseling=false;
}

void FightScene::handselGold()
{
    if(INSTANCE(UserData)->getCurrentMoney() < 50){
        INSTANCE(UserData)->addCurrentMoney(5);
        CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
    }else{
        stopHandsel();
    }
}

