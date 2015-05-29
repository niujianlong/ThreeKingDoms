//
//  ButtonUtils.h
//  threeKingdoms
//
//  Created by .m on 13-12-24.
//
//

#ifndef __threeKingdoms__ButtonUtils__
#define __threeKingdoms__ButtonUtils__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class ButtonUtils:public CCObject
{
public:
    CLASS_INSTANCE(ButtonUtils);
    bool init();
    
    void setButtonTitle(CCControlButton* button, const char* titleName);
    
    CCControlButton* createButton(const char* frameName,CCSize size,const char* label,float labelSize = 22,ccColor3B labelColor = ccWHITE);
    
    CCControlButton* createButton(const char* normalFrame, const char* highLightFrame, const char* disableFrame, CCSize size, const char* label,float labelSize = 22,ccColor3B labelColor = ccWHITE);
private:
    
};

#endif /* defined(__threeKingdoms__ButtonUtils__) */
