//
//  SingleSceneFrame.cpp
//  threeKingdoms
//  Created by sma11case on 14-1-4.
//
//

#include "SingleSceneFrame.h"
#include "GameUtils.h"
#include "UserData.h"
#include "TitleRule.h"
#include "SceneRule.h"
#include "StringUtils.h"
#include "ButtonUtils.h"
#include "Help.h"

SingleSceneFrame* SingleSceneFrame::create(int sceneId)
{
    SingleSceneFrame* singleSceneFrame = new SingleSceneFrame(sceneId);
    if(singleSceneFrame && singleSceneFrame->init()){
        singleSceneFrame->autorelease();
        return singleSceneFrame;
    }else{
        delete singleSceneFrame;
        singleSceneFrame = NULL;
        return NULL;
    }
}

SingleSceneFrame::SingleSceneFrame(int sceneId)
{
    
    this->sceneId = sceneId;
}

SingleSceneFrame::~SingleSceneFrame()
{
    
}

bool SingleSceneFrame::init()
{
    if(!CCNode::init()){
        return false;
    }
    initContent();
    return true;
}

void SingleSceneFrame::initContent()
{
    CCSprite *frame = CCSprite::createWithSpriteFrameName("chapter_frame.png");
    addChild(frame);
    
    CCString *mapName = CCString::createWithFormat("ui/chapter/miniMaps/mini_%d.png",sceneId);
    CCSprite *map = CCSprite::create(mapName->getCString());
    map->setPosition(ccp(12, 5));
    addChild(map);
    int needLevel = INSTANCE(SceneRule)->getSceneNeedLevel(sceneId);
    int needVip = INSTANCE(SceneRule)->getSceneNeedVip(sceneId);
    if(INSTANCE(UserData)->getTitleLevel() < needLevel || INSTANCE(UserData)->getVipLevel() < needVip){
        map->setColor(ccc3(100, 100, 100));
        CCSprite *needLevelBg = CCSprite::createWithSpriteFrameName("chapter_needLevelBg.png");
        addChild(needLevelBg);
        needLevelBg->setPosition(ccp(-120, 0));
        
        
        CCLabelBMFont *label;
        
        
        
        CCLabelTTF *level = CCLabelTTF::create();
        level->setFontSize(18);
        
        if(needVip == 0){
            label = CCLabelBMFont::create(INSTANCE(StringUtils)->addEnter(INSTANCE(TitleRule)->getTitleNameByLevel(needLevel)+ "开启").c_str(), "font/font_title_2.fnt");
            level->setString(CCString::createWithFormat("Lv%d",needLevel)->getCString());
        }else{
            label = CCLabelBMFont::create(INSTANCE(StringUtils)->addEnter(CCString::createWithFormat(" V  I  P 开启")->getCString()).c_str(), "font/font_title_2.fnt");
            level->setString(CCString::createWithFormat("Vip%d",needVip)->getCString());
        }
        
        needLevelBg->addChild(level);
        level->setColor(ccYELLOW);
        level->setPosition(ccp(55, 30));
        
        needLevelBg->addChild(label);
        label->setPosition(ccp(21, 110));
    }else{
        CCControlButton *help = INSTANCE(ButtonUtils)->createButton("common_helpBtn.png",CCSizeMake(75, 81), "");
        addChild(help);
        help->setPosition(ccp(180, -108));
        help->addTargetWithActionForControlEvents(this, cccontrol_selector(SingleSceneFrame::helpHandler), CCControlEventTouchUpInside);
        
        
    }
    
    CCString *mS = CCString::createWithFormat("%d倍",INSTANCE(SceneRule)->getSceneMagnification(sceneId));
    CCLabelBMFont *multiple = CCLabelBMFont::create(mS->getCString(), "font/font_title.fnt");
    addChild(multiple);
    multiple->setPosition(ccp(150, 108));
}

void SingleSceneFrame::helpHandler()
{
    INSTANCE(HelpFacade)->open(sceneId);
}
