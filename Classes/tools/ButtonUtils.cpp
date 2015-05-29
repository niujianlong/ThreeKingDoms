//
//  ButtonUtils.cpp
//  threeKingdoms
//  Created by sma11case 13-12-24.
//
//

#include "ButtonUtils.h"

bool ButtonUtils::init()
{
    return true;
}

void ButtonUtils::setButtonTitle(CCControlButton* button, const char *titleName)
{
    button->setTitleForState(CCStringMake(titleName), CCControlStateNormal);
    button->setTitleForState(CCStringMake(titleName), CCControlStateHighlighted);
    button->setTitleForState(CCStringMake(titleName), CCControlStateDisabled);
    button->setTitleForState(CCStringMake(titleName), CCControlStateSelected);
}

CCControlButton* ButtonUtils::createButton(const char *frameName, cocos2d::CCSize size, const char *label,float labelSize ,ccColor3B labelColor)
{
    return createButton(frameName, frameName, frameName, size, label,labelSize,labelColor);
}

CCControlButton* ButtonUtils::createButton(const char *normalFrame, const char *highLightFrame, const char *disableFrame, cocos2d::CCSize size, const char *label,float labelSize ,ccColor3B labelColor)
{
    CCScale9Sprite *normal = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalFrame));
    CCScale9Sprite *highLight = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(highLightFrame));
    CCScale9Sprite *disable = CCScale9Sprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(disableFrame));
    CCControlButton *btn = CCControlButton::create(label, "Arial", labelSize);
    btn->setPreferredSize(size);
    btn->setBackgroundSpriteForState(normal, CCControlStateNormal);
    btn->setBackgroundSpriteForState(highLight, CCControlStateHighlighted);
    btn->setBackgroundSpriteForState(disable, CCControlStateDisabled);
    btn->setTitleColorForState(labelColor, CCControlStateNormal);
    btn->setTitleColorForState(labelColor, CCControlStateHighlighted);
    btn->setTitleColorForState(labelColor, CCControlStateDisabled);
    btn->setTouchPriority(0);
    
    return btn;
}

