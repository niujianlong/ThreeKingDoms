//
//  GuideManager.cpp
//  threeKingdoms
//
//  Created by .m on 14-2-23.
//
//

#include "GuideManager.h"
#include "TipsManager.h"
#include "SceneManager.h"
#include "AnimationUtils.h"
#include "NPCManager.h"
#include "ButtonUtils.h"
#include "FightManager.h"

bool GuideManager::init()
{
    tips = NULL;
    guideFinger = NULL;
    effect = NULL;
    exitBtn = NULL;
    return true;
}

void GuideManager::setIsGuiding(bool isGuiding)
{
    this->isGuiding = isGuiding;
    if(isGuiding){
        guideStep = GuideStep_10000;
        if(INSTANCE(FightManager)->getIsFighting()){
            addExitBtn();
        }
        
    }else{
        tips = NULL;
        guideFinger = NULL;
        effect = NULL;
        if(exitBtn){
            exitBtn->removeFromParent();
        }
        exitBtn = NULL;
        
    }
    
}

bool GuideManager::getIsGuiding()
{
    return isGuiding;
}

void GuideManager::goToNext()
{
    guideStep = GuideStep(guideStep + 1);
    
    hideGuideFinger();
    hideGuideTips();

    showCurrentGuideFinger();
    showCurrentGuideTips();
    
    if(guideStep == GuideStep_10004){
        INSTANCE(NPCManager)->allNpcStopComplete();
    }
}

GuideStep GuideManager::getCurrentStep()
{
    return guideStep;
}

void GuideManager::registerPosition(GuideStep step, cocos2d::CCPoint p)
{
    positionMap[step] = p;
}

CCPoint GuideManager::getStepPosition(GuideStep step)
{
    if(positionMap.find(step) != positionMap.end()){
        return positionMap[step];
    }
    return ccp(0, 0);
}

void GuideManager::showGuideTips(GuideStep step)
{
    if(getTipsContent(step) == ""){
        return;
    }
    if(tips == NULL){
        tips = CommonTips::create("");
    }
    tips->setString(getTipsContent(step).c_str());
    tips->setVisible(true);
    tips->setPosition(getTipsPosition(step));
    if(!tips->getParent()){
        INSTANCE(SceneManager)->addToCurrentScene(tips,zOrder_guide);
    }
}

void GuideManager::showCurrentGuideTips()
{
    showGuideTips(guideStep);
}

void GuideManager::hideGuideTips()
{
    if(tips){
        tips->setVisible(false);
    }
}

void GuideManager::showGuideFinger(GuideStep step)
{
    CCPoint p = getStepPosition(step);
    if(p.x ==0 && p.y ==0){
        return;
    }
    if(guideFinger == NULL){
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("guide/guide.plist");
        guideFinger = CCSprite::createWithSpriteFrameName("guide_finger.png");
        guideFinger->setAnchorPoint(ccp(0.17, 0.9));
    }
    guideFinger->setVisible(true);
    guideFinger->setPosition(getStepPosition(step));
    if(!guideFinger->getParent()){
        INSTANCE(SceneManager)->addToCurrentScene(guideFinger,zOrder_guide);
    }
    
    hideEffect();
    if(step == GuideStep_10002){
        showStepEffect_10002();
    }
}

void GuideManager::showCurrentGuideFinger()
{
    showGuideFinger(guideStep);
}

void GuideManager::hideGuideFinger()
{
    if(guideFinger){
        guideFinger->setVisible(false);
    }
}

CCPoint GuideManager::getTipsPosition(GuideStep step)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint resultP = ccpAdd(ccp(tips->getContentSize().width/2 + 90, 0), getStepPosition(step));
    if(resultP.x + tips->getContentSize().width/2 > winSize.width){
        resultP = ccpSub(getStepPosition(step), ccp(tips->getContentSize().width/2 + 90, 0));
    }
    return resultP;
}

string GuideManager::getTipsContent(GuideStep step)
{
    switch (step) {
        case GuideStep_10002:
            return "通过摇杆控制角色，使角色移动到指定位置并面对敌人";
        case GuideStep_10003:
            return "点击攻击按钮攻击敌人";
        case GuideStep_10004:
            return "攻击会消耗元宝，成功击杀士兵可以得到元宝";
        case GuideStep_10006:
            return "这是技能兵，击杀能触发特殊技能和得到怒气哦！";
        case GuideStep_10007:
            return "怒气存满的时候，点击这里就可以释放技能啦！";
        case GuideStep_10008:
            return "每隔一段时间久可以领取定额金币。";
        case GuideStep_10009:
            return "若想随时查看帮助，可以点击这里。";
        case GuideStep_10010:
            return "这里有各种帮助信息。";
        case GuideStep_10011:
            return "点击这里。";
        default:
            break;
    }
    return "";
}

void GuideManager::showStepEffect_10002()
{
    if(effect == NULL){
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCAnimation *animation = INSTANCE(AnimationUtils)->getCommonAnimation("guide/guide_effect.plist", "guide_effect");
        CCRepeatForever *action = CCRepeatForever::create(CCAnimate::create(animation));
        effect = CCSprite::createWithSpriteFrameName("guide_effect_0000.png");
        effect->runAction(action);
        INSTANCE(SceneManager)->addToCurrentScene(effect, zOrder_guide);
        effect->setPosition(ccp(winSize.width/2 - 100, 200));
        effect->setAnchorPoint(ccp(0.5, 0));
    }
    effect->setVisible(true);
}

void GuideManager::hideEffect()
{
    if(effect){
        effect->setVisible(false);
    }
}

void GuideManager::exitGuide()
{
    if(effect){
        effect->removeFromParent();
    }
    if(guideFinger){
        guideFinger->removeFromParent();
    }
    
    if(tips){
        tips->removeFromParent();
    }
    setIsGuiding(false);
    INSTANCE(FightManager)->endGuide();
    INSTANCE(NPCManager)->setStop(false);
}

void GuideManager::addExitBtn()
{
    if(exitBtn == NULL){
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
        exitBtn = INSTANCE(ButtonUtils)->createButton("common_redBtn_1.png", CCSizeMake(140, 50), "退出引导");
        INSTANCE(SceneManager)->addToCurrentScene(exitBtn, zOrder_ui);
        exitBtn->setPosition(ccp(winSize.width - 200, 600));
        exitBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GuideManager::exitGuide), CCControlEventTouchUpInside);
    }
}
