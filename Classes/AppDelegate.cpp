//
//  threeKingdomsAppDelegate.cpp
//  threeKingdoms
//
//  Created by .m on 13-12-24.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "FightSceneFacade.h"
#include "CreateCharacterFacade.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
#if COCOS2D_DEBUG > 0
    pDirector->setDisplayStats(true);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    if (screenSize.height != 640)
    {
        float temp = screenSize.width/screenSize.height;
        float temp1 = 960.0/640.0;
        float temp2 = 1136.0/640.0;
        
        int t1 = abs(int((temp - temp1) * 100));
        int t2 = abs(int((temp - temp2) * 100));
        CCLOG("test:%f,%f,%f,%d,%d",temp,temp1,temp2,t1,t2);
        CCSize designSize;
        CCSize resourceSize;
        if(t1 < t2){
            designSize = CCSizeMake(960, 640);
            resourceSize = CCSizeMake(960, 640);
        }else{
            designSize = CCSizeMake(1136, 640);
            resourceSize = CCSizeMake(1136, 640);
        }
        
        pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionExactFit);
    }

    
    
//    INSTANCE(FightSceneFacade)->openFightScene();
    INSTANCE(CreateCharacterFacade)->openCreateCharacterScene();
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
