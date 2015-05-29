//
//  NoticeBox.cpp
//  threeKingdoms
//  Created by sma11case 14-2-8.
//
//

#include "NoticeBox.h"

#include "ButtonUtils.h"
#include "SceneManager.h"

NoticeBox *NoticeBox::create(string messageContent,CCObject *target ,SEL_CallFunc selector ,string btn1Label)
{
    NoticeBox *messageBox = new NoticeBox(messageContent,target,selector,btn1Label);
    if(messageBox && messageBox->init()){
        messageBox->autorelease();
        return messageBox;
    }else{
        delete messageBox;
        messageBox = NULL;
        return NULL;
    }
}

NoticeBox::NoticeBox(string messageContent,CCObject *target ,SEL_CallFunc selector , string btn1Label){
    this->messageContent = messageContent;
    this->btn1Label = btn1Label;
    this->target = target;
    this->selector = selector;
}

NoticeBox::~NoticeBox()
{
    
}

bool NoticeBox::init()
{
    if(!CCLayer::init()){
        return false;
    }
    initContent();
    return true;
}

void NoticeBox::onEnter()
{
    ADD_TOUCH;
    CCLayer::onEnter();
}

void NoticeBox::onExit()
{
    REMOVE_TOUCH;
    CCLayer::onExit();
    INSTANCE(NoticeBoxFacade)->setIsShow(false);
}

bool NoticeBox::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void NoticeBox::initContent()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *bg = CCSprite::create("common/commonBg_451_305.png");
    addChild(bg);
    
    bg->setPosition(ccp(winSize.width/2, winSize.height/2));
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    
    CCSprite *title = CCSprite::createWithSpriteFrameName("common_titleBg.png");
    bg->addChild(title);
    title->setPosition(ccpAdd(ccp(bg->getContentSize().width/2, bg->getContentSize().height), ccp(40, 0)));
    
    CCLabelBMFont *titleLabel = CCLabelBMFont::create("提示", "font/font_uiTitle.fnt");
    title->addChild(titleLabel);
    titleLabel->setPosition(ccp(title->getContentSize().width/2 - 40, title->getContentSize().height/2));
    
    CCLabelTTF *content = CCLabelTTF::create();
    content->setFontSize(24);
    content->setPosition(ccp(bg->getContentSize().width/2, bg->getContentSize().height/2 + 50));
    bg->addChild(content);
    content->setColor(ccBLACK);
    content->setString(messageContent.c_str());
    content->setDimensions(CCSizeMake(bg->getContentSize().width - 80, 180));
    content->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    content->setHorizontalAlignment(kCCTextAlignmentCenter);
    
    CCControlButton *b1 = INSTANCE(ButtonUtils)->createButton("common_redBtn_1.png", "common_redBtn_2.png", "common_redBtn_1.png", CCSizeMake(140, 55), btn1Label.c_str());
    bg->addChild(b1);
    b1->setPosition(ccp(bg->getContentSize().width / 2.0f, 60));
    b1->addTargetWithActionForControlEvents(this, cccontrol_selector(NoticeBox::comfirmHandler), CCControlEventTouchUpInside);
}

void NoticeBox::comfirmHandler()
{
    removeFromParent();
    if(target && selector){
        (target->*selector)();
    }
}



bool NoticeBoxFacade::init()
{
    isShow = false;
    return true;
}

void NoticeBoxFacade::showNoticeBox(string messageContent,CCObject *target,SEL_CallFunc selector,string btn1Label)
{
    if(isShow){
        return;
    }
    INSTANCE(SceneManager)->addToCurrentScene(NoticeBox::create(messageContent,target,selector,btn1Label), zOrder_notice);
    isShow = true;
}

void NoticeBoxFacade::exitGame()
{
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void NoticeBoxFacade::setIsShow(bool param)
{
    isShow = param;
}
