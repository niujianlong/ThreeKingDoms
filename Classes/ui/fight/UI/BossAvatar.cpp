//
//  BossAvatar.cpp
//  threeKingdoms
//  Created by sma11case on 14-1-16.
//
//

#include "BossAvatar.h"
#include "SceneManager.h"
#include "SceneRule.h"
#include "FightManager.h"
#include "StringUtils.h"
#include "NPCRule.h"
#include "BossLottery.h"
#include "TipsManager.h"
#include "EventManager.h"

BossAvatar* BossAvatar::create(int bossId)
{
    BossAvatar *avatar = new BossAvatar(bossId);
    if(avatar && avatar->init()){
        avatar->autorelease();
        return avatar;
    }else{
        delete avatar;
        avatar = NULL;
        return NULL;
    }
}

BossAvatar::BossAvatar(int bossId){
    this->bossId = bossId;
}

BossAvatar::~BossAvatar()
{
    
}

bool BossAvatar::init()
{
    CCString *fileName = CCString::createWithFormat("bossAvatar/bossAvatar_%d.png",bossId);
    if(!CCSprite::initWithFile(fileName->getCString())){
        return false;
    }
    CCSprite *circle = CCSprite::create("bossAvatar/bossAvatar_circle.png");
    addChild(circle);
    circle->setPosition(getCenterPosition(this));
    
    deadFlag = CCLabelBMFont::create("斩", "font/font_kill.fnt");
    addChild(deadFlag);
    deadFlag->setPosition(getCenterPosition(this));
    
    time = CCLabelTTF::create();
    time->setFontSize(30);
    time->setColor(ccRED);
    time->setString("");
    addChild(time);
    time->setPosition(ccp(getContentSize().width/2,30));
    time->setVisible(false);
    currentTime = BossAppearTime;
    return true;
}

void BossAvatar::setStatus(BossStatus status)
{
    CCString *fileName;
    if(status == BossStatus_disappear){
        getScheduler()->unscheduleAllForTarget(this);
        fileName = CCString::createWithFormat("bossAvatar/bossAvatar_%d_gray.png",bossId);
        deadFlag->setVisible(false);
        time->setVisible(false);
    }else if(status == BossStatus_appear){
        currentTime = BossAppearTime;
        getScheduler()->scheduleSelector(schedule_selector(BossAvatar::updateTime), this, 1, false);
        updateTime();
        fileName = CCString::createWithFormat("bossAvatar/bossAvatar_%d.png",bossId);
        deadFlag->setVisible(false);
        time->setVisible(true);
    }else{
        getScheduler()->unscheduleAllForTarget(this);
        fileName = CCString::createWithFormat("bossAvatar/bossAvatar_%d_gray.png",bossId);
        deadFlag->setVisible(true);
        time->setVisible(false);
    }
    setTexture(CCTextureCache::sharedTextureCache()->addImage(fileName->getCString()));
}

void BossAvatar::updateTime()
{
    
    if(currentTime > 0){
        if(currentTime >10){
            time->setColor(ccRED);
        }else{
            time->setColor(ccGREEN);
        }
        time->setString(INSTANCE(StringUtils)->dountDownToString(currentTime * 1000).c_str());
    }else{
        getScheduler()->unscheduleAllForTarget(this);
//        time->setVisible(false);
        updateMultiple();
        INSTANCE(FightManager)->createBoss();
    }
    currentTime--;
}

void BossAvatar::updateMultiple()
{
    time->setColor(ccYELLOW);
    time->setString(CCString::createWithFormat("x%d",INSTANCE(BossLotteryFacade)->getBossMultiple())->getCString());
}

void BossAvatar::onEnter()
{
    CCSprite::onEnter();
    INSTANCE(EventManager)->addEventListener(this, this, callfuncO_selector(BossAvatar::showTips));
}

void BossAvatar::onExit()
{
    CCSprite::onExit();
}

void BossAvatar::showTips()
{
    INSTANCE(TipsManager)->showTips("倒计时结束时将会出现将领", getParent()->convertToWorldSpace(getPosition()));
}

bool BossAvatarLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    
    return true;
}

void BossAvatarLayer::onEnter()
{
    CCLayer::onEnter();
}

void BossAvatarLayer::onExit()
{
    CCLayer::onExit();
    INSTANCE(BossAvatarFacade)->removeAll();
}


bool BossAvatarFacade::init()
{
    layer = NULL;
    dic = CCDictionary::create();
    dic->retain();
    return true;
}

BossAvatarLayer* BossAvatarFacade::setBossAvatar(int currentBossId)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if(layer == NULL){
        layer = BossAvatarLayer::create();
    }else{
        layer->removeAllChildren();
    }
    vector<int> bossId = INSTANCE(FightManager)->getCurrentBossVector();
    dic->removeAllObjects();
    int index = -1;
    for(int i=0;i<bossId.size();i++){
        bossId[i] = INSTANCE(NPCRule)->getNpcModelId(bossId[i]);
        BossAvatar *avatar = BossAvatar::create(bossId[i]);
        dic->setObject(avatar, CCString::createWithFormat("%d",bossId[i])->getCString());
        layer->addChild(avatar);
        avatar->setPosition(ccp(winSize.width/2 - 180 - (bossId.size() - i - 1) * 130, 250));
        
        if(currentBossId == bossId[i]){
            index = i;
        }
    }

    for(int i=0;i<bossId.size();i++){
        if(i < index){
            showBossAvatar(bossId[i],BossStatus_dead);
        }else{
            showBossAvatar(bossId[i],BossStatus_disappear);
        }
        
    }
    return layer;
}

void BossAvatarFacade::showBossAvatar(int bossId,BossStatus status)
{
    BossAvatar *avatar = (BossAvatar *)dic->objectForKey(CCString::createWithFormat("%d",bossId)->getCString());
    if(avatar){
        avatar->setStatus(status);
    }
}

void BossAvatarFacade::resetBossStatus()
{
    if(layer)
    {
        CCMoveBy *moveOut = CCMoveBy::create(1.0, ccp(0, 200));
        CCMoveBy *moveIn = CCMoveBy::create(1.0, ccp(0, -200));
        CCSequence *action = CCSequence::create(moveOut,CCCallFunc::create(this, callfunc_selector(BossAvatarFacade::disappearHandler)),moveIn,NULL);
        layer->runAction(action);
    }
}

void BossAvatarFacade::disappearHandler()
{
    CCArray *array = dic->allKeys();
    for(int i=0;i<array->count();i++){
        BossAvatar *avatar = (BossAvatar *) dic->objectForKey(((CCString *) array->objectAtIndex(i))->getCString());
        if(i == 0){
            avatar->setStatus(BossStatus_appear);
        }else{
            avatar->setStatus(BossStatus_disappear);
        }
        
    }
}

void BossAvatarFacade::removeAll()
{
    dic->removeAllObjects();
    layer = NULL;
}

void BossAvatarFacade::showBossMultiple(int bossId)
{
    BossAvatar *avatar = (BossAvatar *)dic->objectForKey(CCString::createWithFormat("%d",bossId)->getCString());
    if(avatar){
        avatar->updateMultiple();
    }
}

void BossAvatarFacade::pause()
{
    CCArray *array = dic->allKeys();
    if(array){
        for(int i=0;i<array->count();i++){
            BossAvatar *avatar = (BossAvatar *) dic->objectForKey(((CCString *) array->objectAtIndex(i))->getCString());
            CCDirector::sharedDirector()->getScheduler()->pauseTarget(avatar);
        }
    }
}


void BossAvatarFacade::resume()
{
    CCArray *array = dic->allKeys();
    if(array){
        for(int i=0;i<array->count();i++){
            BossAvatar *avatar = (BossAvatar *) dic->objectForKey(((CCString *) array->objectAtIndex(i))->getCString());
            CCDirector::sharedDirector()->getScheduler()->resumeTarget(avatar);
        }
    }
}

void BossAvatarFacade::setAvatarVisible(bool param)
{
    if(layer){
        layer->setVisible(param);
    }
    
    if(param){
        
    }else{
        
    }
}
