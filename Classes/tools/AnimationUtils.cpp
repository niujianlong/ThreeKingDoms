//
//  AnimationUtils.cpp
//  threeKingdoms
//  Created by sma11case 13-12-24.
//
//

#include "AnimationUtils.h"
#include "ModelRule.h"

bool AnimationUtils::init()
{
    return true;
}

CCAnimation *AnimationUtils::getModelAnimation(int modelId,const char *fileName, const char *frameName,float duration){
    string imgPath = INSTANCE(ModelRule)->getModelPath(modelId);
    imgPath.append(fileName);
    imgPath.append(".plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(imgPath.c_str());
    return getAnimation(frameName,duration);
}

CCAnimation *AnimationUtils::getModelAnimation(int modelId,const char *fileName, const char *frameName,float duration,int startIndex,int endIndex){
    string imgPath = INSTANCE(ModelRule)->getModelPath(modelId);
    imgPath.append(fileName);
    imgPath.append(".plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(imgPath.c_str());
    return getAnimation(frameName,duration,startIndex,endIndex);
}


CCAnimation *AnimationUtils::getCommonAnimation(const char *fileName, const char *frameName,float duration)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(fileName);
    return getAnimation(frameName,duration);
}

CCAnimate *AnimationUtils::getModelAnimate(int modelId, RoleStatus status, float duration)
{
    string img = INSTANCE(RoleRule)->getRoleFrameNameByRoleId(modelId, status);
    
    CCAnimation *animation = getModelAnimation(INSTANCE(RoleRule)->getRoleModelId(modelId),img.c_str(), img.c_str(),duration);
    CCAnimate *animate = CCAnimate::create(animation);
    return animate;
}

CCAnimation *AnimationUtils::getAnimation(const char *frameName,float duration){
    CCArray *animFrames = CCArray::create();
    string name_str = frameName;
    name_str.append("_000");
    int i = name_str.length();
    char str[80];
    for(int k = 0; k <= 30; k++)
    {
        if (k <= 9) {
            sprintf(str, "%s%d.png", name_str.c_str(), (k));
        }
        else {
            sprintf(str, "%s%d.png", name_str.substr(0, i - 1).c_str(), (k));
        }
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        if(frame){
            animFrames->addObject(frame);
        }else{
            break;
        }
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, duration);
    return animation;
}

CCAnimation *AnimationUtils::getAnimation(const char *frameName,float duration,int startIndex,int endIndex){
    CCArray *animFrames = CCArray::create();
    string name_str = frameName;
    name_str.append("_000");
    int i = name_str.length();
    char str[80];
    for(int k = startIndex; k <= endIndex; k++)
    {
        if (k <= 9) {
            sprintf(str, "%s%d.png", name_str.c_str(), (k));
        }
        else {
            sprintf(str, "%s%d.png", name_str.substr(0, i - 1).c_str(), (k));
        }
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        if(frame){
            animFrames->addObject(frame);
        }else{
            break;
        }
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, duration);
    return animation;
}