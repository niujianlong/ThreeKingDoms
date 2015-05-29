//
//  BossLottery.cpp
//  threeKingdoms
//  Created by sma11case on 14-2-11.
//
//

#include "BossLottery.h"
#include "SceneManager.h"
#include "ButtonUtils.h"
#include "NPCManager.h"
#include "GameUtils.h"
#include "SystemConfigRule.h"
#include "UserData.h"
#include "FightManager.h"
#include "AnimateManager.h"
#include "NoticeBox.h"
#include "MessageBox.h"
#include "Recharge.h"
#include "MoneyLayer.h"

BossLottery::BossLottery()
{
    array = CCArray::create();
    array->retain();
}

BossLottery::~BossLottery()
{
    array->removeAllObjects();
    array->release();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/fightUI/bossLottery.plist");
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

bool BossLottery::init()
{
    if(!CCLayer::init()){
        return false;
    }
    
    initContent();
    return true;
    
}

void BossLottery::initContent()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/fightUI/bossLottery.plist");
    circle = CCSprite::createWithSpriteFrameName("bossLottery_bg.png");
    addChild(circle);
    
    btn = INSTANCE(ButtonUtils)->createButton("bossLottery_btn.png", CCSizeMake(157, 207), "");
    btn->setAnchorPoint(ccp(0.51, 0.37));
    addChild(btn);
    btn->setZoomOnTouchDown(false);
    
    btn->addTargetWithActionForControlEvents(this, cccontrol_selector(BossLottery::btnHandler), CCControlEventTouchUpInside);
    
    CCPoint cP = circle->getAnchorPointInPoints();
    for(int i=0;i<36;i++){
        BossLotteryLight *light = BossLotteryLight::create();
        circle->addChild(light);
        float t = i*10*3.14f/180;
        light->setPosition(ccpAdd(cP,ccp(200.0f * sin(t), 200.0f * cos(t))));
        array->addObject(light);
    }
    lightFlag = 0;
    
    getScheduler()->scheduleSelector(schedule_selector(BossLottery::updateLight), this, 0.1f, false);
    
    CCLabelTTF *desc = CCLabelTTF::create();
    desc->setFontSize(24);
    desc->setString("击杀将领");
    btn->addChild(desc);
    desc->setColor(ccYELLOW);
    desc->setPosition(ccpAdd(btn->getAnchorPointInPoints(), ccp(0, 33)));
    
    costLabel = CCLabelTTF::create();
    costLabel->setFontSize(24);
    costLabel->setColor(ccGREEN);
    btn->addChild(costLabel);
    costLabel->setPosition(ccpAdd(btn->getAnchorPointInPoints(), ccp(0, -34)));

    costLabel->setString("首次免费");

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    closeBtn = INSTANCE(ButtonUtils)->createButton("common_redBtn_1.png", "common_redBtn_2.png", "common_redBtn_1.png", CCSizeMake(151, 48), "关闭",24,ccYELLOW);
    addChild(closeBtn);
    closeBtn->setPosition(ccp(0, -190));
    closeBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(BossLottery::close), CCControlEventTouchUpInside);
    
    times = 1;
}

void BossLottery::updateLight()
{
    for(int i=0;i<array->count();i++){
        BossLotteryLight *light = (BossLotteryLight *)array->objectAtIndex(i);
        if(i%3 == lightFlag){
            light->light();
        }else{
            light->extinguish();
        }
    }
    lightFlag+1>2?lightFlag = 0:lightFlag++;
}

void BossLottery::onEnter()
{
    ADD_TOUCH;
    CCLayer::onEnter();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    setPosition(ccp(winSize.width/2, winSize.height/2));
    INSTANCE(BossLotteryFacade)->setLotteryStatus(true);
}

void BossLottery::onExit()
{
    REMOVE_TOUCH;
    CCLayer::onExit();
    INSTANCE(BossLotteryFacade)->setLotteryStatus(false);
}

bool BossLottery::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void BossLottery::btnHandler()
{
    int cost = INSTANCE(SystemConfigRule)->getBossLotteryCost();
    if(times > 1){
        if(cost >= INSTANCE(UserData)->getCurrentMoney()){
            INSTANCE(MessageBoxFacade)->showMessageBox("元宝不足，是否充值？", INSTANCE(RechargeFacade), callfunc_selector(RechargeFacade::open),"充值");
            return;
        }
        INSTANCE(UserData)->costCurrentMoney(cost);
        INSTANCE(MoneyLayerManager)->createReduceMoney(cost);
    }
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
    btn->setEnabled(false);
    closeBtn->setEnabled(false);
    int r = INSTANCE(SystemConfigRule)->getWheelMultiple();
    result = getMultiple(r);
    INSTANCE(BossLotteryFacade)->setBossMultiple(result);
    CCRotateBy *rotate = CCRotateBy::create(4.0f, 3600 + r * 60 - 30);
    CCEaseInOut *easeInOut = CCEaseInOut::create((CCActionInterval *)rotate->copy()->autorelease(), 1.5f);
    
    CCSequence *action = CCSequence::create(easeInOut,CCCallFunc::create(this, callfunc_selector(BossLottery::rotateComplete)),NULL);
    
    circle->setRotation(0);
    circle->runAction(action);
    
    costLabel->setString(CCString::createWithFormat("消耗%d元宝",cost)->getCString());
    INSTANCE(UserData)->addWheelTimes(1);
    
    times++;
}

int BossLottery::getMultiple(int p)
{
    switch (p) {
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        case 3:
            return 10;
            break;
        case 4:
            return 20;
            break;
        case 5:
            return 50;
            break;
        case 6:
            return 100;
            break;
        default:
            break;
    }
    return 1;
}

void BossLottery::close()
{
    removeFromParent();
    INSTANCE(FightManager)->resumeFight();
}

void BossLottery::rotateComplete()
{
    btn->setEnabled(true);
    closeBtn->setEnabled(true);
    INSTANCE(BossAvatarFacade)->showBossMultiple(INSTANCE(FightManager)->getCurrentBossId());
    if(result > 1){
        INSTANCE(SceneManager)->addToCurrentScene(BossLotteryNotice::create(result), zOrder_notice);
    }
}

bool BossLotteryLight::init()
{
    if(!CCSprite::initWithSpriteFrameName("bossLottery_light_1.png")){
        return false;
    }
    return true;
}

void BossLotteryLight::light()
{
    setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bossLottery_light_2.png"));
}

void BossLotteryLight::extinguish()
{
    setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bossLottery_light_1.png"));
}




BossLotteryNotice* BossLotteryNotice::create(int multiple)
{
    BossLotteryNotice *notice = new BossLotteryNotice(multiple);
    if(notice && notice->init()){
        notice->autorelease();
        return notice;
    }else{
        delete notice;
        notice = NULL;
        return NULL;
    }
}

BossLotteryNotice::BossLotteryNotice(int multiple)
{
    this->multiple = multiple;
}

BossLotteryNotice::~BossLotteryNotice()
{
    
}

bool BossLotteryNotice::init()
{
    if(!CCNode::init()){
        return false;
    }
    initContent();
    return true;
}

void BossLotteryNotice::initContent()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/fightUI/gainGold.plist");
    CCSprite *bg = CCSprite::createWithSpriteFrameName("gainGold_bg.png");
    addChild(bg);
    
    CCSprite *title = CCSprite::createWithSpriteFrameName("gainGold_title.png");
    bg->addChild(title);
    title->setPosition(ccp(bg->getContentSize().width/2, bg->getContentSize().height - 30));
    
    CCLabelTTF *content = CCLabelTTF::create();
    content->setFontSize(24);
    content->setColor(ccGREEN);
    bg->addChild(content);
    content->setPosition(ccp(bg->getContentSize().width/2, bg->getContentSize().height/2 + 30));
    content->setDimensions(CCSizeMake(bg->getContentSize().width - 40, 200));
    content->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    content->setHorizontalAlignment(kCCTextAlignmentCenter);
    content->setString(CCString::createWithFormat("恭喜获得击杀将领%d倍奖励",multiple)->getCString());
}

void BossLotteryNotice::onEnter()
{
    CCNode::onEnter();
    setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    INSTANCE(AnimateManager)->showScaleAnimate(this);
}

void BossLotteryNotice::onExit()
{
    CCNode::onExit();
}

bool BossLotteryFacade::init()
{
    bossMultiple = 1;
    return true;
}

void BossLotteryFacade::open()
{
    INSTANCE(SceneManager)->addToCurrentScene(BossLottery::create(), zOrder_ui);
    INSTANCE(FightManager)->pauseFight();
}

void BossLotteryFacade::setBossMultiple(int multiple)
{
    this->bossMultiple = multiple;
}

int BossLotteryFacade::getBossMultiple()
{
    return bossMultiple;
}

void BossLotteryFacade::setLotteryStatus(bool show)
{
    lotteryShow = show;
}

bool BossLotteryFacade::getLotteryStatus()
{
    return lotteryShow;
}

