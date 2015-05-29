//
//  JniManager.cpp
//  threeKingdoms
//  Created by sma11case 14-2-28.
//
//

#include "JniManager.h"
#include "RechargeManager.h"
#include "MessageBox.h"
#include "NoticeBox.h"


bool JniManager::init()
{
    
    return true;
}

string JniManager::jniGetMac()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;//定义Jni函数信息结构体
    jstring result;
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/duomai/threekingdoms/RechargeManager","getMacAddress", "()Ljava/lang/String;");
    
    if (!isHave) {
        CCLog("jni:此函数不存在");
    }else{
        CCLog("jni:此函数存在");
        //调用此函数
        result = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    CCLog("jni-java函数执行完毕");
    return JniHelper::jstring2string(result);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCLog("ios平台无需调用jni");
    return "";
#endif
}

void JniManager::jniRecharge(string takonId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;//定义Jni函数信息结构体
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/duomai/threekingdoms/RechargeManager","Recharge", "(Ljava/lang/String;)V");
    
    if (!isHave) {
        CCLog("jni:此函数不存在");
    }else{
        CCLog("jni:此函数存在");
        //调用此函数
        jstring jURL =minfo.env->NewStringUTF(takonId.c_str());
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jURL);
    }
    CCLog("jni-java函数执行完毕");
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCLog("ios平台无需调用jni");
#endif
}


void JniManager::jniUpdateNewVersion()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;//定义Jni函数信息结构体
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/duomai/threekingdoms/VersionManager","StartUpdateNewVersion", "()V");
    
    if (!isHave) {
        CCLog("jni:此函数不存在");
    }else{
        CCLog("jni:此函数存在");
        //调用此函数
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
    CCLog("jni-java函数执行完毕");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCLog("ios平台无需调用jni");
#endif
}

int JniManager::jniGetNetState()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;//定义Jni函数信息结构体

    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/duomai/threekingdoms/NetStateManager","isOpenNetwork", "()I");
    jint _int;
    if (!isHave) {
        CCLog("jni:此函数不存在");
    }else{
        CCLog("jni:此函数存在");
        _int = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);
    }
    return int(_int);
#endif
    return 0;
}

string JniManager::jniGetVersion()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;//定义Jni函数信息结构体
    jstring result;
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/duomai/threekingdoms/VersionManager","getVersion", "()Ljava/lang/String;");
    
    if (!isHave) {
        CCLog("jni:此函数不存在");
    }else{
        CCLog("jni:此函数存在");
        //调用此函数
        result = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    CCLog("jni-java函数执行完毕");
    return JniHelper::jstring2string(result);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCLog("ios平台无需调用jni");
    return "";
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
    void Java_com_duomai_threekingdoms_JniManager_JniCallC
    (JNIEnv *env, jobject obj, jstring jstr)
    {
        string result = JniHelper::jstring2string(jstr);
        CCLOG("jni-c++函数执行完毕:%s",result.c_str());
        if(result == "rechargeVerification"){
            INSTANCE(RechargeManager)->rechargeVerification();
        }else if(result == "noticeExitGame"){
            INSTANCE(MessageBoxFacade)->showMessageBox("是否退出游戏", INSTANCE(NoticeBoxFacade),callfunc_selector(NoticeBoxFacade::exitGame));
        }
        return;
    }
}
#endif
