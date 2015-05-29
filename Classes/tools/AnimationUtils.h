//
//  AnimationUtils.h
//  threeKingdoms
//  Created by sma11case on 13-12-24.
//
//

#ifndef __threeKingdoms__AnimationUtils__
#define __threeKingdoms__AnimationUtils__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "RoleRule.h"

using namespace std;
USING_NS_CC;

class AnimationUtils:public CCObject
{
public:
    CLASS_INSTANCE(AnimationUtils);
    bool init();
    
    CCAnimation *getModelAnimation(int modelId,const char *fileName, const char *frameName, float duration = 0.10);
    CCAnimation *getModelAnimation(int modelId,const char *fileName, const char *frameName, float duration,int startIndex,int endIndex);
    
    CCAnimate *getModelAnimate(int modelId,RoleStatus status, float duration);
    
    CCAnimation *getCommonAnimation(const char*fileName,const char*frameName,float duration = 0.10);
private:
    CCAnimation *getAnimation(const char *frameName, float duration);
    CCAnimation *getAnimation(const char *frameName, float duration,int startIndex,int endIndex);
};
#endif /* defined(__threeKingdoms__AnimationUtils__) */
