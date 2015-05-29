//
//  Help.cpp
//  threeKingdoms
//  Created by sma11case 14-2-13.
//
//

#include "Help.h"
#include "CommonBg.h"
#include "GameUtils.h"
#include "ButtonUtils.h"
#include "SceneManager.h"
#include "SingleHelpNpc.h"
#include "SceneRule.h"
#include <algorithm>
#include "NPCRule.h"
#include "UserData.h"
#include "GuideManager.h"
#include "NoticeBox.h"
#include "FightManager.h"

Help* Help::create(int sceneId)
{
    Help *help = new Help(sceneId);
    if(help && help->init()){
        help->autorelease();
        return help;
    }else{
        delete help;
        help = NULL;
        return NULL;
    }
}

Help::Help(int sceneId)
{
    this->sceneId = sceneId;
}

Help::~Help()
{
    
}

bool Help::init()
{
    if(!CCLayer::init()){
        return false;
    }
    
    initContent();
    return true;
}

void Help::initContent()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    addChild(CommonBg::create("三国百科"));
    
    CCLabelTTF *sceneName = CCLabelTTF::create();
    sceneName->setString(INSTANCE(SceneRule)->getSceneName(sceneId).c_str());
    sceneName->setPosition(ccp(0, 180));
    addChild(sceneName,10);
    sceneName->setFontSize(24);
    sceneName->setColor(ccYELLOW);
    
    CCControlButton *backBtn = INSTANCE(ButtonUtils)->createButton("common_backBtn.png", CCSizeMake(75, 81), "");
    backBtn->setPosition(ccp(winSize.width/2 - 60, 260));
    
    backBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(Help::removeFromParent), CCControlEventTouchUpInside);
    addChild(backBtn);
    
    CCScrollView *scrollView = CCScrollView::create();
    CCLayer* layer = CCLayer::create();
    scrollView = CCScrollView::create();
    scrollView->setContainer(layer);
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);
    addChild(scrollView);
//    scrollView->setAnchorPoint(ccp(0.5, 0.5));
    scrollView->setPosition(ccp(-440, -260));
    
    vector<int> npcIdVector = INSTANCE(SceneRule)->getAllNpcId(sceneId);
    sort(npcIdVector.begin(), npcIdVector.end(),compareNpc);
    
    npcIdVector.insert(npcIdVector.begin(), INSTANCE(UserData)->getCurrentRoleId());
    
    for(int i=npcIdVector.size()-1;i>=0;i--){
        SingleHelpNpc *singleNpc;
        if(i == 0){
            singleNpc = SingleHelpNpc::create(npcIdVector[i],true);
        }else{
            singleNpc = SingleHelpNpc::create(npcIdVector[i]);
        }
        layer->addChild(singleNpc);
        singleNpc->setPosition(ccp(220 * i + 105, 200));
    }
    
    scrollView->setViewSize(CCSizeMake(880, 460));
    scrollView->setContentSize(CCSizeMake(220*npcIdVector.size(), scrollView->getViewSize().height));
}

void Help::onEnter()
{
    ADD_TOUCH;
    CCLayer::onEnter();
}

void Help::onExit()
{
    REMOVE_TOUCH;
    CCLayer::onExit();
    
    if(INSTANCE(GuideManager)->getIsGuiding() && INSTANCE(GuideManager)->getCurrentStep() == GuideStep_10012){
        INSTANCE(NoticeBoxFacade)->showNoticeBox("新手教程结束了，相信你已经初步了解了杀将技巧，现在就去征战沙场吧！");
        INSTANCE(FightManager)->endGuide();
    }
}

bool Help::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

bool HelpFacade::init()
{
    return true;
}

void HelpFacade::open(int sceneId)
{
    INSTANCE(SceneManager)->addToCurrentScene(Help::create(sceneId), zOrder_scene);
}


bool compareNpc(int npcId_1,int npcId_2)
{
    return INSTANCE(NPCRule)->getNpcIntegral(npcId_1) <  INSTANCE(NPCRule)->getNpcIntegral(npcId_2);
}


