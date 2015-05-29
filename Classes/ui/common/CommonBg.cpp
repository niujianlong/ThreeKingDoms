//
//  CommonBg.cpp
//  threeKingdoms
//  Created by sma11case on 14-2-7.
//
//

#include "CommonBg.h"
#include "GameUtils.h"

CommonBg* CommonBg::create(string title)
{
    CommonBg *commonBg = new CommonBg(title);
    if(commonBg && commonBg->init()){
        commonBg->autorelease();
        return commonBg;
    }else{
        delete commonBg;
        commonBg = NULL;
        return NULL;
    }
}

CommonBg::CommonBg(string title)
{
    this->title = title;
}

CommonBg::~CommonBg()
{
    
}

bool CommonBg::init()
{
    if(!CCNode::init()){
        return false;
    }
    initContent();
    return true;
}

void CommonBg::initContent()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    setContentSize(winSize);
    setAnchorPoint(ccp(0.5, 0.5));
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/chapter/chapter.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    
    CCScale9Sprite *topBar = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("chapter_texture.png"));
    topBar->setPreferredSize(CCSizeMake(winSize.width, 115));
    topBar->setAnchorPoint(ccp(0.5, 1));
    addChild(topBar);
    topBar->setPosition(ccp(0, winSize.height/2));
    
    CCScale9Sprite *bottomBar = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("chapter_texture.png"));
    bottomBar->setPreferredSize(CCSizeMake(winSize.width, 115));
    bottomBar->setAnchorPoint(ccp(0.5, 0));
    addChild(bottomBar);
    bottomBar->setPosition(ccp(0, -winSize.height/2));
    
    
    
    CCSprite *frame1 = CCSprite::createWithSpriteFrameName("chapter_frame_1.png");
    addChild(frame1);
    frame1->setAnchorPoint(ccp(0.5, 1));
    frame1->setPosition(ccp(0, winSize.height/2));
    
    CCSprite *frame2 = CCSprite::createWithSpriteFrameName("chapter_frame_1.png");
    addChild(frame2);
    frame2->setAnchorPoint(ccp(0.5, 0));
    frame2->setPosition(ccp(0, -winSize.height/2));
    frame2->setFlipY(true);
    
    CCSprite *frameLeft = CCSprite::createWithSpriteFrameName("chapter_frame_2.png");
    addChild(frameLeft);
    frameLeft->setAnchorPoint(ccp(1, 0.5));
    frameLeft->setPosition(ccp(-winSize.width/2, 0));
    frameLeft->setRotation(180);
    
    CCSprite *frameRight = CCSprite::createWithSpriteFrameName("chapter_frame_2.png");
    addChild(frameRight);
    frameRight->setAnchorPoint(ccp(1, 0.5));
    frameRight->setPosition(ccp(winSize.width/2, 0));
    
    CCLayerColor *colorLayer = CCLayerColor::create(ccc4(61, 34, 0, 255));
    addChild(colorLayer);
    colorLayer->setPosition(ccp(-winSize.width/2 + 7, -winSize.height/2 + 115));
    colorLayer->setContentSize(CCSizeMake(winSize.width-14, 410));
    
    CCSprite *line_1 = CCSprite::createWithSpriteFrameName("chapter_line.png");
    addChild(line_1);
    line_1->setPosition(ccp(-1, winSize.height/2 - 115));
    
    CCSprite *line_2 = CCSprite::createWithSpriteFrameName("chapter_line.png");
    addChild(line_2);
    line_2->setPosition(ccp(-1, -winSize.height/2 + 115));
    line_2->setFlipY(true);
    
    CCSprite *titleBg = CCSprite::createWithSpriteFrameName("common_titleBg.png");
    addChild(titleBg);
    titleBg->setPosition(ccp(40, 240));
    
    CCLabelBMFont* title = CCLabelBMFont::create(this->title.c_str(), "font/font_uiTitle.fnt");
    addChild(title);
    title->setPosition(ccp(0, 240));
//    setPosition(ccp(winSize.width/2, winSize.height/2));
}

