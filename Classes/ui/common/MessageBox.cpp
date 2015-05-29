//
//  MessageBox.cpp
//  threeKingdoms
//  Created by sma11case on 14-2-8.
//
//

#include "MessageBox.h"
#include "ButtonUtils.h"
#include "SceneManager.h"

MessageBox *MessageBox::create(string messageContent, cocos2d::CCObject *target, SEL_CallFunc selector, string btn1Label, string btn2Label, SEL_CallFunc selector2)
{
    MessageBox *messageBox = new MessageBox(messageContent,target,selector,btn1Label,btn2Label,selector2);
    if(messageBox && messageBox->init()){
        messageBox->autorelease();
        return messageBox;
    }else{
        delete messageBox;
        messageBox = NULL;
        return NULL;
    }
}

MessageBox::MessageBox(string messageContent, cocos2d::CCObject *target, SEL_CallFunc selector, string btn1Label, string btn2Label, SEL_CallFunc selector2){
    this->messageContent = messageContent;
    this->target = target;
    this->selector = selector;
    this->selector2 = selector2;
    this->btn1Label = btn1Label;
    this->btn2Label = btn2Label;
}

MessageBox::~MessageBox()
{
    
}

bool MessageBox::init()
{
    if(!CCLayer::init()){
        return false;
    }
    initContent();
    return true;
}

void MessageBox::onEnter()
{
    ADD_TOUCH;
    CCLayer::onEnter();
}

void MessageBox::onExit()
{
    REMOVE_TOUCH;
    CCLayer::onExit();
    INSTANCE(MessageBoxFacade)->setIsShow(false);
}

bool MessageBox::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void MessageBox::initContent()
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
    
    CCControlButton *b2 = INSTANCE(ButtonUtils)->createButton("common_redBtn_1.png", "common_redBtn_2.png", "common_redBtn_1.png", CCSizeMake(140, 55), btn2Label.c_str());
    
    bg->addChild(b1);
    bg->addChild(b2);
    
    b1->setPosition(ccp(bg->getContentSize().width / 3.0f - 20, 60));
    b2->setPosition(ccp(bg->getContentSize().width * 2.0f / 3.0f + 20, 60));
    
    b1->addTargetWithActionForControlEvents(this, cccontrol_selector(MessageBox::comfirmHandler), CCControlEventTouchUpInside);
    b2->addTargetWithActionForControlEvents(this, cccontrol_selector(MessageBox::cancelHandler), CCControlEventTouchUpInside);
}

void MessageBox::comfirmHandler()
{
    removeFromParent();
    if(target && selector){
        (target->*selector)();
    }
}

void MessageBox::cancelHandler()
{
    removeFromParent();
    if(target && selector2){
        (target->*selector2)();
    }
}



bool MessageBoxFacade::init()
{
    isShow = false;
    return true;
}

void MessageBoxFacade::showMessageBox(string messageContent,CCObject *target,SEL_CallFunc selector,string btn1Label ,string btn2Label ,SEL_CallFunc selector2 )
{
    if(isShow){
        return;
    }
    INSTANCE(SceneManager)->addToCurrentScene(MessageBox::create(messageContent, target, selector, btn1Label, btn2Label, selector2), zOrder_notice);
    isShow = true;
}

void MessageBoxFacade::setIsShow(bool param)
{
    isShow = param;
}



