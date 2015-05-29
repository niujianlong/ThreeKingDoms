//
//  NetStateManager.cpp
//  threeKingdoms
//  Created by sma11case on 14-3-6.
//
//

#include "NetStateManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "IosNetState.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JniManager.h"
#endif

bool NetStateManager::init()
{
    return true;
}

bool NetStateManager::getNetState()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if(INSTANCE(JniManager)->jniGetNetState() == 1){
        return true;
    }else{
        return false;
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(IosNetState::getIosNetState() == NetState_noNetWork){
        return false;
    }else{
        return true;
    }
#endif
}