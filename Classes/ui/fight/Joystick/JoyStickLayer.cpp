//
//  JoyStickLayer.cpp
//  threeKingdoms
//  Created by sma11case 13-12-24.
//
//

#include "JoyStickLayer.h"
#include "FightSceneFacade.h"

#include "FightManager.h"
#include "ButtonUtils.h"
#include "GuideManager.h"
#include "EventManager.h"
#include "TipsManager.h"

bool JoyStickLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("joyStick/joyStickImg.plist");
    lastPoi = ccp(0, 0);
    initJoyStickLayer();
    return true;
}

void JoyStickLayer::initJoyStickLayer()
{
    joystick=new SneakyJoystick();
    joystick->autorelease();
    joystick->initWithRect(CCRectZero);
    //是否自动回到中心
    joystick->setAutoCenter(true);
    //是否支持死亡区域，该区域不会触发
    joystick->setHasDeadzone(true);
    //死亡区域半径
    joystick->setDeadRadius(10);
    joystick->setJoystickRadius(200);
    
    joystickSkin=new SneakyJoystickSkinnedBase();
    joystickSkin->autorelease();
    joystickSkin->init();
    //背景
    joystickSkin->setBackgroundSprite(CCSprite::createWithSpriteFrameName("joyStick.png"));
    //中心点
    joystickSkin->setThumbSprite(CCSprite::createWithSpriteFrameName("joyStickCenter.png"));
    joystickSkin->getThumbSprite()->setScale(1.0f);
    
    int winWidth = CCDirector::sharedDirector()->getWinSize().width;
    
    
    joystickSkin->setJoystick(joystick);
    
    this->addChild(joystickSkin,100);
    
    this->scheduleUpdate();
    
    attackBtn = INSTANCE(ButtonUtils)->createButton("joyStickButton.png", "joyStickButtonHighLight.png", "joyStickButton.png", CCSizeMake(221, 177), "");
    this->addChild(attackBtn);
    attackBtn->setZoomOnTouchDown(false);
    skillBtn = INSTANCE(ButtonUtils)->createButton("joyStickskillButton.png", "joyStickskillButtonHighLight.png", "joyStickskillButtonGray.png", CCSizeMake(106, 111), "");
    this->addChild(skillBtn);
    skillBtn->setZoomOnTouchDown(false);
    
    if(winWidth == 960){
        joystickSkin->setPosition(CCPointMake(-350,-200));
        attackBtn->setPosition(ccp(380, -230));
        skillBtn->setPosition(ccp(240, -200));
    }else{
        joystickSkin->setPosition(CCPointMake(-438,-200));
        attackBtn->setPosition(ccp(468, -230));
        skillBtn->setPosition(ccp(328, -200));
    }
    
    skillBtn->setEnabled(false);
    
    skillPro = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("joyStickskillButton.png"));
    skillBtn->addChild(skillPro);
    skillPro->setPosition(ccp(skillBtn->getContentSize().width/2,skillBtn->getContentSize().height/2));
    skillPro->setType(kCCProgressTimerTypeBar);
    skillPro->setBarChangeRate(ccp(0, 1));
    skillPro->setMidpoint(ccp(0, 0));
    skillPro->setPercentage(0);
    
    INSTANCE(EventManager)->addEventListener(skillPro, this, callfuncO_selector(JoyStickLayer::skillTips));
}

void JoyStickLayer::update(float t)
{

    if(INSTANCE(FightManager)->enoughAnger()){
        skillBtn->setEnabled(true);
        skillPro->setPercentage(100);
    }else{
        skillBtn->setEnabled(false);
        skillPro->setPercentage(INSTANCE(FightManager)->getAnger() * 100);
    }
    
    if(INSTANCE(GuideManager)->getIsGuiding()){
        GuideStep step = INSTANCE(GuideManager)->getCurrentStep();
        if(step == GuideStep_10007){
            skillBtn->setEnabled(true);
        }
        
        if(step == GuideStep_10003 || step == GuideStep_10004 ||step == GuideStep_10006 || step == GuideStep_10007 || step == GuideStep_10003){
            if(!attackBtn->isEnabled()){
                attackBtn->setEnabled(true);
            }
        }else{
            if(attackBtn->isEnabled()){
                attackBtn->setEnabled(false);
            }
        }
    }else{
        if(!attackBtn->isEnabled()){
            attackBtn->setEnabled(true);
        }
        
    }
    
    
    if(attackBtn->isHighlighted()) {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(JoyStick_status,CCStringMake(JoyStick_attack));
        return;
    }
    
    if(skillBtn->isHighlighted()){
        CCNotificationCenter::sharedNotificationCenter()->postNotification(JoyStick_status,CCStringMake(JoyStick_skill));
        return;
    }
    
    
    CCPoint poi = ccpMult(joystick->getVelocity(), 50);
    
    if(poi.x == 0 && poi.y == 0){
        if(lastPoi.x !=0 || lastPoi.y != 0){
            CCNotificationCenter::sharedNotificationCenter()->postNotification(JoyStick_status,CCStringMake(JoyStick_none));
            lastPoi = poi;
        }
        return;
    }
    
    lastPoi = poi;
    
    float degree = atan2(poi.y, poi.x)*180/atan2(0.0, -1.0);
    
    if(degree <0){
        degree += 360;
    }
    if(degree >= 22.5 && degree < 67.5){
        //右上
        CCNotificationCenter::sharedNotificationCenter()->postNotification(JoyStick_status,CCStringMake(JoyStick_right_up));
    }else if(degree >= 67.5 && degree < 112.5){
        //上
        CCNotificationCenter::sharedNotificationCenter()->postNotification(JoyStick_status,CCStringMake(JoyStick_up));
    }else if(degree >= 112.5 && degree < 157.5){
        //左上
        CCNotificationCenter::sharedNotificationCenter()->postNotification(JoyStick_status,CCStringMake(JoyStick_left_up));
    }else if(degree >= 157.5 && degree < 202.5){
        //左
        CCNotificationCenter::sharedNotificationCenter()->postNotification(JoyStick_status,CCStringMake(JoyStick_left));
    }else if(degree >= 202.5 && degree < 247.5){
        //左下
        CCNotificationCenter::sharedNotificationCenter()->postNotification(JoyStick_status,CCStringMake(JoyStick_left_down));
    }else if(degree >= 247.5 && degree < 292.5){
        //下
        CCNotificationCenter::sharedNotificationCenter()->postNotification(JoyStick_status,CCStringMake(JoyStick_down));
    }else if(degree >= 292.5 && degree < 337.5){
        //右下
        CCNotificationCenter::sharedNotificationCenter()->postNotification(JoyStick_status,CCStringMake(JoyStick_right_down));
    }else{
        //右
        CCNotificationCenter::sharedNotificationCenter()->postNotification(JoyStick_status,CCStringMake(JoyStick_right));
    }
}

void JoyStickLayer::attackHandler()
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(JoyStick_status,CCStringMake(JoyStick_attack));
}

void JoyStickLayer::onEnter()
{
    CCLayer::onEnter();
    INSTANCE(GuideManager)->registerPosition(GuideStep_10002,joystickSkin->getParent()->convertToWorldSpace(joystickSkin->getPosition()));
    INSTANCE(GuideManager)->registerPosition(GuideStep_10003,attackBtn->getParent()->convertToWorldSpace(attackBtn->getPosition()));
    INSTANCE(GuideManager)->registerPosition(GuideStep_10007,skillBtn->getParent()->convertToWorldSpace(skillBtn->getPosition()));
}

void JoyStickLayer::onExit()
{
    CCLayer::onExit();
    
}

void JoyStickLayer::skillTips()
{
    if(!skillBtn->isEnabled()){
        INSTANCE(TipsManager)->showTips("击杀技能兵能获得怒气，怒气存满时，点击这里就可以释放技能", skillBtn->getParent()->convertToWorldSpace(skillBtn->getPosition()));
    }
}
