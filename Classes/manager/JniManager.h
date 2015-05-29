//
//  JniManager.h
//  threeKingdoms
//
//  Created by .m on 14-2-28.
//
//

#ifndef __threeKingdoms__JniManager__
#define __threeKingdoms__JniManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

#include <cstring>
#include <string>

using namespace std;
USING_NS_CC;


class JniManager:public CCObject
{
public:
    CLASS_INSTANCE(JniManager);
    bool init();
    
    void jniRecharge(string takonId);
    
    string jniGetMac();
    
    void jniUpdateNewVersion();
    
    int jniGetNetState();
    
    string jniGetVersion();
private:
};



#endif /* defined(__threeKingdoms__JniManager__) */
