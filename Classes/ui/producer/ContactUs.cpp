//
//  ContactUs.cpp
//  threeKingdoms
//  Created by sma11case 14-3-1.
//
//

#include "ContactUs.h"
#include "ButtonUtils.h"
#include "SceneManager.h"
#include "GameUtils.h"

bool ContactUs::init()
{
    if(!CCLayer::init()){
        return false;
    }
    initContent();
    return true;
}

void ContactUs::initContent()
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
    
    CCLabelBMFont *title = CCLabelBMFont::create("联系我们", "font/font_uiTitle.fnt");
    titleBg->addChild(title);
    title->setPosition(ccp(titleBg->getContentSize().width/2 - 50, titleBg->getContentSize().height/2));
    
    CCLabelTTF *content = CCLabelTTF::create();
    content->setFontSize(20);
    content->setDimensions(CCSizeMake(340, 160));
    content->setHorizontalAlignment(kCCTextAlignmentCenter);
    content->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    bg->addChild(content);
    content->setPosition(ccp(bg->getContentSize().width/2, bg->getContentSize().height/2));
    
    content->setColor(ccBLACK);
    
    string contentStr = "您的每一个意见，我们都会认真去对待！谢谢您的支持！\n客服qq群：127494184\n客服邮箱：kefu@llwan.com";
    content->setString(contentStr.c_str());
    
    CCControlButton *closeBtn = INSTANCE(ButtonUtils)->createButton("common_backBtn.png", CCSizeMake(75, 81), "");
    bg->addChild(closeBtn);
    closeBtn->setPosition(ccp(bg->getContentSize().width - 20, bg->getContentSize().height - 20));
    closeBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(CCNode::removeFromParent), CCControlEventTouchUpInside);
}

void ContactUs::onEnter()
{
    ADD_TOUCH;
    CCLayer::onEnter();
    setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
}

void ContactUs::onExit()
{
    REMOVE_TOUCH;
    CCLayer::onExit();
    removeAllChildren();
    CCUserDefault::sharedUserDefault()->flush();
}

bool ContactUs::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

bool ContactUsFacade::init()
{
    return true;
}

void ContactUsFacade::open()
{
    INSTANCE(SceneManager)->addToCurrentScene(ContactUs::create(), zOrder_ui);
}

