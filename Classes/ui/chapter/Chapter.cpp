//
//  Chapter.cpp
//  threeKingdoms
//
//  Created by .m on 14-1-4.
//
//

#include "Chapter.h"
#include "GameUtils.h"
#include "ButtonUtils.h"
#include "FightSceneFacade.h"
#include "CreateCharacterFacade.h"
#include "SingleSceneFrame.h"
#include "SceneRule.h"
#include "UserData.h"
#include "ChapterFacade.h"
#include "TitleRule.h"
#include "StringUtils.h"
#include "GameUtils.h"
#include "SoundManager.h"
#include "GameSet.h"
#include "LoadingScene.h"
#include "LoginReward.h"
#include "FightManager.h"
#include "TimeManager.h"
#include "CommonBg.h"
#include "Recharge.h"
#include "MessageBox.h"
#include "GuideManager.h"

Chapter::Chapter()
{
    frameSpace = 100;
    frameWidth = 620;
}

Chapter::~Chapter()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/chapter/chapter.plist");
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

bool Chapter::init()
{
    if(!CCLayer::init()){
        return false;
    }
    sceneIdVector = INSTANCE(SceneRule)->getAllSceneId();
    frameArray = CCArray::create();
    frameArray->retain();
    initContent();
    initScrollView();
    return true;
}

void Chapter::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::onEnter();
    INSTANCE(SoundManager)->playChapterMusic();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Chapter::updateMoney), NoticeUpdateMoney, NULL);

}

void Chapter::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    if(INSTANCE(TimeManager)->includeSomeWeekDay(INSTANCE(UserData)->getLastReceiveLoginRewardTime(), INSTANCE(TimeManager)->getSystemTimeM(), 6)){
        INSTANCE(UserData)->setContinuousDay(0);
    }
    if(INSTANCE(TimeManager)->isLaterDay(INSTANCE(UserData)->getLastReceiveLoginRewardTime(), INSTANCE(TimeManager)->getSystemTimeM())){
        INSTANCE(LoginRewardFacade)->open();
    }
    
    if(INSTANCE(UserData)->getLoginCount() == 0){
        INSTANCE(MessageBoxFacade)->showMessageBox("您第一次进入游戏，是否进入新手教程？", this, callfunc_selector(Chapter::startGuide),"进入");
    }
    INSTANCE(UserData)->addLoginCount(1);
}

void Chapter::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
    removeAllChildren();
    frameArray->removeAllObjects();
    frameArray->release();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NoticeUpdateMoney);
    
}

void Chapter::initContent()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    addChild(CommonBg::create("关卡选择"));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/chapter/chapter.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    
    CCControlButton *backBtn = INSTANCE(ButtonUtils)->createButton("common_backBtn.png", CCSizeMake(75, 81), "");
    CCControlButton *setBtn = INSTANCE(ButtonUtils)->createButton("common_setBtn.png", CCSizeMake(75, 81), "");
    CCControlButton *rechargeBtn = INSTANCE(ButtonUtils)->createButton("common_rechargeBtn.png", CCSizeMake(75, 81), "");
//    CCControlButton *rankBtn = INSTANCE(ButtonUtils)->createButton("common_rankBtn.png", CCSizeMake(93, 81), "");
    addChild(backBtn);
    addChild(setBtn);
    addChild(rechargeBtn);
//    addChild(rankBtn);
    backBtn->setPosition(ccp(winSize.width/2 - 60, 260));
    setBtn->setPosition(ccp(winSize.width/2 - 60, -260));
    rechargeBtn->setPosition(ccp(winSize.width/2 - 160, -260));
//    rankBtn->setPosition(ccp(winSize.width/2 - 260, -260));
    
    backBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(Chapter::onBack), CCControlEventTouchUpInside);
    setBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(Chapter::openSet), CCControlEventTouchDown);
    rechargeBtn->addTargetWithActionForControlEvents(INSTANCE(RechargeFacade), cccontrol_selector(RechargeFacade::open), CCControlEventTouchDown);
    
//    CCSprite *frame_1 = CCSprite::createWithSpriteFrameName("common_frame_1.png");
//    frame_1->setAnchorPoint(ccp(1, 0.5));
//    frame_1->setPosition(ccp( 338-winSize.width/2, 60 - winSize.height/2));
//    addChild(frame_1);
//    
//    CCProgressTimer *titleBar = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("common_frameBar_1.png"));
//    frame_1->addChild(titleBar);
//    titleBar->setPosition(ccp(frame_1->getContentSize().width/2,frame_1->getContentSize().height/2));
//    titleBar->setType(kCCProgressTimerTypeBar);
//    titleBar->setBarChangeRate(ccp(1, 0));
//    titleBar->setMidpoint(ccp(0, 0));
//    titleBar->setPercentage(((float)INSTANCE(UserData)->getCurrentMoney())/9999 * 100);
//    
//    CCSprite *ink1 = CCSprite::createWithSpriteFrameName("common_ink.png");
//    frame_1->addChild(ink1);
//    ink1->setPosition(ccp(10, frame_1->getContentSize().height/2));
//    
//    int currentTitleLevel = INSTANCE(UserData)->getTitleLevel();
//    string titleName = INSTANCE(TitleRule)->getTitleNameByTitleLevel(currentTitleLevel);
//    int nextTitleIntegral = INSTANCE(TitleRule)->getTitleIntegralByTitleLevel(currentTitleLevel + 1);
//    int currentUpgradeIntegral = INSTANCE(UserData)->getCurrentUpgradeIntegral();
//    titleBar->setPercentage(((float)currentUpgradeIntegral)/nextTitleIntegral * 100);
//    
//    CCLabelBMFont *titleLabel = CCLabelBMFont::create(titleName.c_str(), "font/font_title.fnt");
//    frame_1->addChild(titleLabel);
//    titleLabel->setPosition(ccpAdd(INSTANCE(GameUtils)->getNodeCenterPosition(frame_1),ccp(0, -8)));
//    
//    CCSprite *titleIcon = CCSprite::createWithSpriteFrameName("common_titleIcon.png");
//    frame_1->addChild(titleIcon);
//    titleIcon->setPosition(ccp(10, frame_1->getContentSize().height/2));
//    
//    CCLabelTTF *titleLevel = CCLabelTTF::create();
//    titleLevel->setFontSize(20);
//    titleLevel->setColor(ccYELLOW);
//    titleLevel->setString(CCString::createWithFormat("Lv%d",INSTANCE(UserData)->getTitleLevel())->getCString());
//    titleIcon->addChild(titleLevel);
//    titleLevel->setPosition(ccp(30, titleIcon->getContentSize().height/2 - 20));
    
    titleBar = CommonTitleBar::create();
    addChild(titleBar);
    titleBar->setPosition(ccp( 60-winSize.width/2, 60 - winSize.height/2));
    
    moneyBar = CommonMoneyBar::create();
    addChild(moneyBar);
    moneyBar->setPosition(ccp( 360 - winSize.width/2, 60 - winSize.height/2));
}

void Chapter::initScrollView()
{
    currentSelectedSceneIndex = INSTANCE(ChapterFacade)->getLastSelectedIndex();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    layer = CCLayer::create();
    scrollView = CCScrollView::create();
    scrollView->setContainer(layer);
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);
    addChild(scrollView);
    scrollView->setPosition(ccp(-winSize.width/2, -200));
    
    for(int i=0;i<sceneIdVector.size();i++){
        SingleSceneFrame *frame = SingleSceneFrame::create(sceneIdVector[i]);
        layer->addChild(frame);
        frame->setPosition(ccp(frameWidth/2 - 10 + i*frameWidth,200));
        frameArray->addObject(frame);
        if(CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID){
            if(i!=currentSelectedSceneIndex){
                frame->setScale(0.8);
            }
        }
    }
    
    scrollView->setViewSize(CCSizeMake(winSize.width, 400));
    scrollView->setContentSize(CCSizeMake(frameWidth*sceneIdVector.size(), scrollView->getViewSize().height));
    
    scrollView->setContentOffset(ccp((winSize.width - frameWidth)/2 - frameWidth *currentSelectedSceneIndex, 0));
    scrollView->setDelegate(this);
    
    
    startBtn = INSTANCE(ButtonUtils)->createButton("chapter_startBtn.png", CCSizeMake(226, 87), "开始游戏",40,ccBLACK);
    
    startBtn->setPosition(ccp(0, -160));
    startBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(Chapter::startGame), CCControlEventTouchUpInside);
    addChild(startBtn,1);
    
    
    INSTANCE(ButtonUtils)->setButtonTitle(startBtn, INSTANCE(SceneRule)->getSceneName(sceneIdVector[currentSelectedSceneIndex]).c_str());
}

void Chapter::startGame()
{
    int currentSelectedSceneId = sceneIdVector[currentSelectedSceneIndex];
    
    int currentTitleLevel = INSTANCE(UserData)->getTitleLevel();
    int needTitleLevel = INSTANCE(SceneRule)->getSceneNeedLevel(currentSelectedSceneId);
    int needVip = INSTANCE(SceneRule)->getSceneNeedVip(currentSelectedSceneId);
    if(currentTitleLevel < needTitleLevel || INSTANCE(UserData)->getVipLevel() < needVip){
        return;
    }
    INSTANCE(UserData)->setCurrentSceneId(sceneIdVector[currentSelectedSceneIndex]);
    INSTANCE(ChapterFacade)->setLastSelectedIndex(currentSelectedSceneIndex);
//    INSTANCE(FightSceneFacade)->openFightScene();
    
    INSTANCE(LoadingSceneFacade)->openLoadingScene();
    
}

void Chapter::onBack()
{
    INSTANCE(CreateCharacterFacade)->openCreateCharacterScene();
}

bool Chapter::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void Chapter::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    adjustScrollView();
}

void Chapter::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    adjustScrollView();
}

void Chapter::adjustScrollView()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int w = (winSize.width - frameWidth)/2;
    scrollView->unscheduleAllSelectors();
    int x = scrollView->getContentOffset().x;
    // 调整位置
    CCPoint adjustPos;
    // 调整动画时间
    float adjustAnimDelay;

    int current = w - currentSelectedSceneIndex * frameWidth;
    
    
    if(x < current)
    {
        //左边
        if(abs(x - current) >frameSpace/2){
            //向左翻页
            adjustPos = ccp(current - frameWidth,0);
            currentSelectedSceneIndex++;
        }else{
            //回滚
            adjustPos = ccp(current, 0);
        }
    }else{
        //右边
        if(abs(current - x) > frameSpace/2){
            //向右翻页
            adjustPos = ccp(current + frameWidth, 0);
            currentSelectedSceneIndex--;
        }else{
            //回滚
            adjustPos = ccp(current, 0);
        }
    }
    if(currentSelectedSceneIndex == -1)
    {
        currentSelectedSceneIndex =0;
        adjustPos=ccp(w, adjustPos.y);
    }
    else if(currentSelectedSceneIndex>=sceneIdVector.size())
    {
        currentSelectedSceneIndex = sceneIdVector.size()-1;
        adjustPos=ccp(current, adjustPos.y);
    }
    adjustAnimDelay = (float)abs(int(x - adjustPos.x)) / 2000;
    scrollView->setContentOffsetInDuration(adjustPos, adjustAnimDelay);
    
    INSTANCE(ButtonUtils)->setButtonTitle(startBtn, INSTANCE(SceneRule)->getSceneName(sceneIdVector[currentSelectedSceneIndex]).c_str());
}


void Chapter::scrollViewDidScroll(CCScrollView* view)
{
    int centerPointX = INSTANCE(GameUtils)->getWindowsCenterPosition().x;
    for(int i=0;i<frameArray->count();i++){
        SingleSceneFrame *frame = (SingleSceneFrame *) frameArray->objectAtIndex(i);
        int pX = frame->getParent()->convertToWorldSpace(frame->getPosition()).x;
        int scale = abs(pX - centerPointX);
        if(scale > 200){
            frame->setScale(0.8);
        }else{
            frame->setScale((100.0 - scale/10.0)/100.0);
            
        }
    }
}
void Chapter::scrollViewDidZoom(CCScrollView* view)
{
    
}

void Chapter::updateMoney()
{
    moneyBar->updateBar();
//    moneyBar->setPercentage(((float)INSTANCE(UserData)->getCurrentMoney())/9999 * 100);
//    moneyLabel->setString(INSTANCE(StringUtils)->intToString(INSTANCE(UserData)->getCurrentMoney()).c_str());
}

void Chapter::openSet()
{
    INSTANCE(GameSetFacade)->openGameSet(false);
}

void Chapter::startGuide()
{
    INSTANCE(GuideManager)->setIsGuiding(true);
    INSTANCE(UserData)->setCurrentSceneId(40001);
    INSTANCE(FightSceneFacade)->openFightScene();
}
