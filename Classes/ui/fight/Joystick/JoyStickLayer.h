//
//  JoyStickLayer.h
//  threeKingdoms
//  Created by sma11case on 13-12-24.
//
//

#ifndef __threeKingdoms__JoyStickLayer__
#define __threeKingdoms__JoyStickLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

#define JoyStick_status "JoyStick_status"
#define JoyStick_none "JoyStick_none"
#define JoyStick_right "JoyStick_right"
#define JoyStick_left "JoyStick_left"
#define JoyStick_up "JoyStick_up"
#define JoyStick_down "JoyStick_down"
#define JoyStick_right_down "JoyStick_right_down"
#define JoyStick_right_up "JoyStick_right_up"
#define JoyStick_left_down "JoyStick_left_down"
#define JoyStick_left_up "JoyStick_left_up"

#define JoyStick_attack "JoyStick_attack"
#define JoyStick_skill "JowStick_skill"


class JoyStickLayer:public CCLayer
{
public:
    CREATE_FUNC(JoyStickLayer);
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
private:
    void initJoyStickLayer();
    
    void update(float t);
    
    void attackHandler();
    
    SneakyJoystick *joystick;
    
    CCControlButton *attackBtn;
    
    CCControlButton *skillBtn;
//    
//    SneakyButtonSkinnedBase *skillSbsb;
    
    SneakyJoystickSkinnedBase *joystickSkin;
    
    CCPoint lastPoi;
    
    CCProgressTimer *skillPro;
    
    void skillTips();
};

#endif /* defined(__threeKingdoms__JoyStickLayer__) */
