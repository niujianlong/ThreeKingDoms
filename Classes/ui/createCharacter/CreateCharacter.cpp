//
//  CreateCharacter.cpp
//  threeKingdoms
//
//  Created by .m on 14-1-2.
//
//

#include "CreateCharacter.h"
#include "GameUtils.h"
#include "ButtonUtils.h"
#include "FightSceneFacade.h"
#include "SingleCharacter.h"
#include "FightManager.h"
#include "ParticleManager.h"
#include "ChapterFacade.h"
#include "UserData.h"
#include "SoundManager.h"
#include "CreateCharacterBg.h"
#include "TimeManager.h"
#include "NoticeBox.h"
#include "MessageBox.h"
#include "VersionManager.h"
#include "NetStateManager.h"

//#ifdef VERSION_PP
//#include "PPLoginFacade.h"
//#endif

CreateCharacter::CreateCharacter()
{
    
}

CreateCharacter::~CreateCharacter()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("ui/createCharacter/createCharacter.plist");
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

bool CreateCharacter::init()
{
    if(!CCLayer::init()){
        return false;
    }
    initContent();
    return true;
}

void CreateCharacter::initContent()
{
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/createCharacter/createCharacter.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("model/20001/20001_stand.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("model/20002/20002_stand.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("model/20003/20003_stand.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("model/20005/20005_stand.plist");
    
    addChild(CreateCharacterBg::create());
    
    CCSprite *fg = CCSprite::createWithSpriteFrameName("createCharacter_fontground.png");
    addChild(fg);
    fg->setAnchorPoint(ccp(0.5,0));
    fg->setPosition(ccp(INSTANCE(GameUtils)->getWindowsCenterPosition().x, 0));
    
    CCLayerColor *color = CCLayerColor::create(getColor(INSTANCE(TimeManager)->getTimeType()));
    addChild(color);
    
    CCControlButton *startBtn = INSTANCE(ButtonUtils)->createButton("createCharacter_enterGameBtn1.png","createCharacter_enterGameBtn2.png","createCharacter_enterGameBtn2.png", CCSizeMake(232, 139), "");
    addChild(startBtn);
    
    startBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(CreateCharacter::startGame), CCControlEventTouchUpInside);
    
    startBtn->setPosition(ccp(INSTANCE(GameUtils)->getWindowsCenterPosition().x, 70));
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    
//    CCSprite *logo = CCSprite::createWithSpriteFrameName("createCharacter_logo.png");
//    addChild(logo);
//    logo->setPosition(ccp(size.width/2, size.height/2 + 200));
    
    characterArray = CCArray::create();
    characterArray->retain();
    
    vector<int> roleIds = INSTANCE(RoleRule)->getAllRoleId();
    vector<int> freeRoleIds = INSTANCE(RoleRule)->getFreeRolesVector();
    for(int i=0;i<roleIds.size();i++){
        
        int needVip = INSTANCE(RoleRule)->getRoleVip(roleIds[i]);
        if(needVip != 0 && INSTANCE(UserData)->getVipLevel() >= needVip){
            INSTANCE(UserData)->addRole(roleIds[i]);
        }
        
        SingleCharacter *singleCharacter = SingleCharacter::create(roleIds[i]);
        addChild(singleCharacter);
        singleCharacter->setPosition(ccp(size.width/5 * (i + 1), 150));
        characterArray->addObject(singleCharacter);
        
        if(INSTANCE(GameUtils)->vectorContainInt(freeRoleIds, roleIds[i])){
            singleCharacter->setSelect(true);
            INSTANCE(UserData)->setCurrentRoleId(roleIds[i]);
        }
    }
    
//#ifdef VERSION_PP
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
//    
//    changeAccount = INSTANCE(ButtonUtils)->createButton("common_titleBg.png", CCSizeMake(345, 66), "");
//    changeAccount->setPosition(ccp(size.width - changeAccount->getContentSize().width / 2, size.height - changeAccount->getContentSize().height / 2));
//    changeAccount->addTargetWithActionForControlEvents(this, cccontrol_selector(CreateCharacter::onChangeAccount), CCControlEventTouchUpInside);
//    
//    addChild(changeAccount);
//    
//    text = CCLabelBMFont::create("切换账号", "font/font_uiTitle.fnt");
//    text->setPosition(ccp(size.width - changeAccount->getContentSize().width / 2 - 30, size.height - changeAccount->getContentSize().height / 2));
//    addChild(text);
//#endif
}

void CreateCharacter::onEnter()
{
    CCLayer::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CreateCharacter::unselectAll), UnselectAllSingleCharacter, NULL);
    INSTANCE(SoundManager)->playCreateCharacter();
    
}

void CreateCharacter::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    if(INSTANCE(TimeManager)->getSystemTimeM() < INSTANCE(UserData)->getLastReceiveLoginRewardTime()){
        INSTANCE(NoticeBoxFacade)->showNoticeBox("游戏检测到当前系统时间和上次登陆游戏时间不符，请将系统时间修改回上次登录游戏时间",INSTANCE(NoticeBoxFacade),callfunc_selector(NoticeBoxFacade::exitGame),"退出游戏");
    }else{
        //联网情况下，一天检测一次
        INSTANCE(VersionManager)->checkVersion();
        
    }
}

void CreateCharacter::onExit()
{
    CCLayer::onExit();
    removeAllChildren();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, UnselectAllSingleCharacter);
    characterArray->removeAllObjects();
    characterArray->release();
}

void CreateCharacter::onChangeAccount(cocos2d::CCObject *sender)
{
//#ifdef VERSION_PP
//    PPLoginFacade login;
//    login.showGameCenterView();
//#endif
}

void CreateCharacter::startGame()
{
//#ifdef VERSION_PP
//    if (!INSTANCE(UserData)->isPPLogin) {
//        PPLoginFacade login;
//        login.showLoginView();
//    }
//#endif
    
    int roleId = INSTANCE(UserData)->getCurrentRoleId();
    CCObject *obj;
    CCARRAY_FOREACH(characterArray, obj)
    {
        if(((SingleCharacter *) obj)->getRoleId() == roleId)
        {
            break;
        }
    }
    if(!INSTANCE(RoleRule)->ownRole(roleId)){
        int needVip = INSTANCE(RoleRule)->getRoleVip(roleId);
        int goldCost = INSTANCE(RoleRule)->getRoleCost(roleId);
        string roleName = INSTANCE(RoleRule)->getRoleName(roleId);
        if(needVip == 0 && goldCost != 0){
            INSTANCE(MessageBoxFacade)->showMessageBox(CCString::createWithFormat("是否花费%d元宝购买%s",goldCost,roleName.c_str())->getCString(), (SingleCharacter *) obj, callfunc_selector(SingleCharacter::buyHandler));
        }else{
            INSTANCE(NoticeBoxFacade)->showNoticeBox(CCString::createWithFormat("VIP开放%s",roleName.c_str())->getCString());
        }
        
        return;
    }
    INSTANCE(ChapterFacade)->openChapterScene();
}

void CreateCharacter::unselectAll()
{
    CCObject *obj;
    CCARRAY_FOREACH(characterArray, obj)
    {
        ((SingleCharacter *) obj)->setSelect(false);
    }
}

ccColor4B CreateCharacter::getColor(TimeType type)
{
    if(type == TimeType_dayTime){
        return ccc4(255, 255, 255, 20);
    }else if(type == TimeType_night){
        return ccc4(0, 0, 0, 180);
    }else if(type == TimeType_morning){
        return ccc4(0, 0, 255, 20);
    }else{
        return ccc4(255, 200, 0, 60);
    }
}

