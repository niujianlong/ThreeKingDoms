//
//  GameSet.cpp
//  threeKingdoms
//  Created by sma11case on 14-1-7.
//
//

#include "GameSet.h"
#include "ButtonUtils.h"
#include "SceneManager.h"
#include "GameCommon.h"
#include "GameUtils.h"
#include "SimpleAudioEngine.h"
#include "Help.h"
#include "UserData.h"
#include "FightManager.h"
#include "Producer.h"
#include "GuideManager.h"
#include "FightSceneFacade.h"
#include "ContactUs.h"

GameSet* GameSet::create(bool showHelp)
{
    GameSet* gameSet = new GameSet(showHelp);
    if(gameSet && gameSet->init()){
        gameSet->autorelease();
        return gameSet;
    }else{
        delete gameSet;
        gameSet = NULL;
        return NULL;
    }
}

GameSet::GameSet(bool showHelp)
{
    this->showHelp = showHelp;
    wikiBtn = NULL;
}

GameSet::~GameSet()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/gameSet/gameSet.plist");
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

bool GameSet::init()
{
    if(!CCLayer::init()){
        return false;
    }
    
    initContent();
    return true;
}

void GameSet::initContent()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor *colorlayer = CCLayerColor::create(ccc4(0, 0, 0, 120));
    addChild(colorlayer);
    colorlayer->setPosition(ccp(-winSize.width/2, -winSize.height/2));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/gameSet/gameSet.plist");
    
    CCSprite *bg = CCSprite::create("common/commonBg_451_305.png");
    addChild(bg);
    
    CCSprite *titleBg = CCSprite::createWithSpriteFrameName("common_titleBg.png");
    bg->addChild(titleBg);
    titleBg->setPosition(ccp(bg->getContentSize().width/2 + 50, bg->getContentSize().height));
    
    CCLabelBMFont *title = CCLabelBMFont::create("设置", "font/font_uiTitle.fnt");
    titleBg->addChild(title);
    title->setPosition(ccp(titleBg->getContentSize().width/2 - 50, titleBg->getContentSize().height/2));
    
    CCScale9Sprite *frame = CCScale9Sprite::create("common/common_scale_1.png");
    frame->setPreferredSize(CCSizeMake(328, 150));
    frame->setAnchorPoint(ccp(0.5, 0.5));
    bg->addChild(frame);
    frame->setPosition(ccp(bg->getContentSize().width/2, bg->getContentSize().height/2 + 40));

    
//    CCSprite *title = CCSprite::createWithSpriteFrameName("set_title.png");
//    bg->addChild(title);
//    title->setPosition(ccp(bg->getContentSize().width/2, bg->getContentSize().height - 20));
    
    
    CCControlButton *closeBtn = INSTANCE(ButtonUtils)->createButton("common_backBtn.png", CCSizeMake(75, 81), "");
    bg->addChild(closeBtn);
    closeBtn->setPosition(ccp(bg->getContentSize().width - 20, bg->getContentSize().height - 20));
    closeBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameSet::close), CCControlEventTouchUpInside);
    
    CCLabelBMFont *musicLabel = CCLabelBMFont::create("音乐", "font/font_common.fnt");
    bg->addChild(musicLabel);
    musicLabel->setPosition(ccp(115, 235));
    
    CCControlSlider *musicSlider = CCControlSlider::create(CCSprite::createWithSpriteFrameName("set_barFrame.png"), CCSprite::createWithSpriteFrameName("set_barFrame.png"), CCSprite::createWithSpriteFrameName("set_barBtn.png"));
    musicSlider->setAnchorPoint(ccp(0.5f, 1.0f));
    musicSlider->setMinimumValue(0.0f); // Sets the min value of range
    musicSlider->setMaximumValue(1.0f); // Sets the max value of range
    musicSlider->setTag(1);
    musicSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(GameSet::musicCallBack), CCControlEventValueChanged);
    musicSlider->setPosition(ccp(260, 250));
    musicSlider->setTouchPriority(0);
    float musicVolume = CCUserDefault::sharedUserDefault()->getFloatForKey(GameSet_musicVolume, 0.5);
    musicSlider->setValue(musicVolume);
    bg->addChild(musicSlider);
    
    CCLabelBMFont *soundLabel = CCLabelBMFont::create("音效", "font/font_common.fnt");
    bg->addChild(soundLabel);
    soundLabel->setPosition(ccp(115, 185));
    
    CCControlSlider *soundSlider = CCControlSlider::create(CCSprite::createWithSpriteFrameName("set_barFrame.png"), CCSprite::createWithSpriteFrameName("set_barFrame.png"), CCSprite::createWithSpriteFrameName("set_barBtn.png"));
    soundSlider->setAnchorPoint(ccp(0.5f, 1.0f));
    soundSlider->setMinimumValue(0.0f); // Sets the min value of range
    soundSlider->setMaximumValue(1.0f); // Sets the max value of range
    soundSlider->setTag(1);
    soundSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(GameSet::soundCallBack), CCControlEventValueChanged);
    soundSlider->setPosition(ccp(260, 200));
    soundSlider->setTouchPriority(0);
    float soundVolume = CCUserDefault::sharedUserDefault()->getFloatForKey(GameSet_soundVolume, 0.5);
    soundSlider->setValue(soundVolume);
    bg->addChild(soundSlider);
    
    
    CCControlButton *btn1 = INSTANCE(ButtonUtils)->createButton("set_guide.png", CCSizeMake(84, 87), "");
    
    CCControlButton *btn3 = INSTANCE(ButtonUtils)->createButton("set_contact.png", CCSizeMake(83, 84), "");
    CCControlButton *btn4 = INSTANCE(ButtonUtils)->createButton("set_develep.png", CCSizeMake(83, 92), "");
    
    bg->addChild(btn1);
    
    bg->addChild(btn3);
    bg->addChild(btn4);
    
    if(showHelp){
        wikiBtn = INSTANCE(ButtonUtils)->createButton("set_wiki.png", CCSizeMake(87, 89), "");
        bg->addChild(wikiBtn);
        btn1->setPosition(ccp(80, 50));
        wikiBtn->setPosition(ccp(180, 50));
        btn3->setPosition(ccp(280, 50));
        btn4->setPosition(ccp(380, 50));
        
        wikiBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameSet::btn2Handler), CCControlEventTouchUpInside);
    }else{
        btn1->setPosition(ccp(80, 50));
        btn3->setPosition(ccp(230, 50));
        btn4->setPosition(ccp(380, 50));
    }
    
    btn1->addTargetWithActionForControlEvents(this, cccontrol_selector(GameSet::btn1Handler), CCControlEventTouchUpInside);
    btn3->addTargetWithActionForControlEvents(this, cccontrol_selector(GameSet::btn3Handler), CCControlEventTouchUpInside);
    btn4->addTargetWithActionForControlEvents(this, cccontrol_selector(GameSet::btn4Handler), CCControlEventTouchUpInside);
    
    
    
}

void GameSet::btn1Handler()
{
    close();
    if(INSTANCE(FightManager)->getIsFighting()){
        INSTANCE(FightManager)->startGuide();
    }else{
        INSTANCE(GuideManager)->setIsGuiding(true);
        INSTANCE(UserData)->setCurrentSceneId(40001);
        INSTANCE(FightSceneFacade)->openFightScene();
    }
    
    
}

void GameSet::btn2Handler()
{
    INSTANCE(HelpFacade)->open(INSTANCE(UserData)->getCurrentSceneId());
    if(INSTANCE(GuideManager)->getIsGuiding() && INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10011){
        INSTANCE(GuideManager)->goToNext();
    }
}

void GameSet::btn3Handler()
{
    close();
    INSTANCE(ContactUsFacade)->open();
}

void GameSet::btn4Handler()
{
    INSTANCE(SceneManager)->addToCurrentScene(Producer::create(), zOrder_scene);
}

void GameSet::onEnter()
{
    ADD_TOUCH;
    CCLayer::onEnter();
    
    setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    if(wikiBtn){
        INSTANCE(GuideManager)->registerPosition(GuideStep_10011, ccpAdd(wikiBtn->getParent()->convertToWorldSpace(wikiBtn->getPosition()), ccp(0, -20)));
    }
    
}

void GameSet::onExit()
{
    REMOVE_TOUCH;
    CCLayer::onExit();
    removeAllChildren();
    CCUserDefault::sharedUserDefault()->flush();
}

bool GameSet::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void GameSet::close()
{
    INSTANCE(GameSetFacade)->closeGameSet();
}

void GameSet::musicCallBack(CCControlSlider *sender, CCControlEvent controlEvent)
{
    CCUserDefault::sharedUserDefault()->setFloatForKey(GameSet_musicVolume, sender->getValue());
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(sender->getValue());
}

void GameSet::soundCallBack(CCControlSlider *sender, CCControlEvent controlEvent)
{
    CCUserDefault::sharedUserDefault()->setFloatForKey(GameSet_soundVolume, sender->getValue());
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(sender->getValue());
}





bool GameSetFacade::init()
{
    gameSet = NULL;
    return true;
}

void GameSetFacade::openGameSet(bool showHelp)
{
    gameSet = GameSet::create(showHelp);
    INSTANCE(SceneManager)->addToCurrentScene(gameSet, zOrder_ui);
    INSTANCE(FightManager)->pauseFight();
}

void GameSetFacade::closeGameSet()
{
    if(gameSet){
        gameSet->removeFromParent();
        gameSet = NULL;
    }
    INSTANCE(FightManager)->resumeFight();
}