//
//  NewChapterOpen.cpp
//  threeKingdoms
//  Created by sma11case on 14-1-8.
//
//

#include "NewChapterOpen.h"
#include "SceneManager.h"
#include "GameUtils.h"

NewChapterOpen *NewChapterOpen::create(int sceneId)
{
    NewChapterOpen *newChapterOpen = new NewChapterOpen(sceneId);
    if(newChapterOpen && newChapterOpen->init()){
        newChapterOpen->autorelease();
        return newChapterOpen;
    }else{
        delete newChapterOpen;
        newChapterOpen = NULL;
        return NULL;
    }
}

NewChapterOpen::NewChapterOpen(int sceneId)
{
    this->sceneId = sceneId;
}

NewChapterOpen::~NewChapterOpen()
{
    
}

bool NewChapterOpen::init()
{
    if(!CCNode::init()){
        return false;
    }
    setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    initContent();
    return true;
}

void NewChapterOpen::initContent()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/fightUI/newChapter.plist");
    
    CCSprite *sp_bg = CCSprite::createWithSpriteFrameName("newChapter_bg.png");
    CCString *miniMapStr = CCString::createWithFormat("ui/chapter/miniMaps/mini_%d.png",sceneId);
    CCSprite *miniMap = CCSprite::create(miniMapStr->getCString());
    sp_bg->addChild(miniMap);
    miniMap->setPosition(getCenterPosition(sp_bg));
    
    CCSprite* sp_2 = CCSprite::createWithSpriteFrameName("newChapter_other.png");
    sp_bg->addChild(sp_2);
    sp_2->setPosition(ccp(sp_bg->getContentSize().width,sp_bg->getContentSize().height/2));

    CCLabelBMFont *label = CCLabelBMFont::create("恭喜开启新关卡", "font/font_ui.fnt");
    sp_bg->addChild(label);
    label->setPosition(ccp(sp_bg->getContentSize().width/2, sp_bg->getContentSize().height));
    
    CCScrollView* view = CCScrollView::create();
    view->setContainer(sp_bg);
    view->setTouchEnabled(false);
    view->setContentOffset(ccp(-425, 20));
    view->setViewSize(CCSizeMake(537, 370));
    view->setContentSize(view->getViewSize());
    view->setPosition(ccp(-view->getContentSize().width/2 + 40, -view->getContentSize().height/2));
    addChild(view);
    
    CCSprite *sp_1 = CCSprite::createWithSpriteFrameName("newChapter_other.png");
    addChild(sp_1);
    sp_1->setPosition(ccp(-225, 2));
    
    view->setContentOffsetInDuration(ccp(0, 20), 0.2);
}

void NewChapterOpen::onEnter()
{
    CCNode::onEnter();
    CCSequence *action = CCSequence::create(CCDelayTime::create(2),CCCallFunc::create(this, callfunc_selector(CCNode::removeFromParent)),NULL);
    runAction(action);
}

void NewChapterOpen::onExit()
{
    CCNode::onExit();
}

bool NewChapterOpenManager::init()
{
    return true;
}

void NewChapterOpenManager::showNewChapterOpen(int sceneId)
{
    NewChapterOpen *newChapterOpen = NewChapterOpen::create(sceneId);
    INSTANCE(SceneManager)->addToCurrentScene(newChapterOpen, zOrder_notice);
}
