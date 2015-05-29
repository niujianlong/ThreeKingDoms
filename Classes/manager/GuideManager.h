//
//  GuideManager.h
//  threeKingdoms
//
//  Created by .m on 14-2-23.
//
//

#ifndef __threeKingdoms__GuideManager__
#define __threeKingdoms__GuideManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "TipsManager.h"

using namespace std;
USING_NS_CC;

enum GuideStep
{
    GuideStep_10000,
    GuideStep_10001,
    GuideStep_10002,
    GuideStep_10003,
    GuideStep_10004,
    GuideStep_10005,
    GuideStep_10006,
    GuideStep_10007,
    GuideStep_10008,
    GuideStep_10009,
    GuideStep_10010,
    GuideStep_10011,
    GuideStep_10012,
    GuideStep_10013,
    GuideStep_10014,
    GuideStep_10015,
    GuideStep_10016,
    
};

class GuideManager:public CCObject
{
public:
    CLASS_INSTANCE(GuideManager);
    bool init();
    
    void setIsGuiding(bool isGuiding);
    bool getIsGuiding();
    
    void goToNext();
    GuideStep getCurrentStep();
    
    void registerPosition(GuideStep step,CCPoint p);
    CCPoint getStepPosition(GuideStep step);
    
    void addExitBtn();
private:
    bool isGuiding;
    GuideStep guideStep;
    CommonTips *tips;
    
    CCSprite *guideFinger;
    
    CCControlButton *exitBtn;
    
    map<GuideStep, CCPoint> positionMap;
    
    CCPoint getTipsPosition(GuideStep step);
    
    string getTipsContent(GuideStep step);
    
    void showStepEffect_10002();
    
    CCSprite *effect;
    
    void showGuideTips(GuideStep step);
    void showCurrentGuideTips();
    void hideGuideTips();
    
    void showGuideFinger(GuideStep step);
    void showCurrentGuideFinger();
    void hideGuideFinger();
    
    void hideEffect();
    
    void exitGuide();
    
    
};

#endif /* defined(__threeKingdoms__GuideManager__) */
