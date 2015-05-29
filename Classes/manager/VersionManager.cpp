//
//  VersionManager.cpp
//  threeKingdoms
//
//  Created by .m on 14-3-6.
//
//

#include "VersionManager.h"
#include "MessageBox.h"
#include "JniManager.h"
#include "HttpDown.h"
#include "NetStateManager.h"
#include "CommonLoading.h"
#include "BaseDataManager.h"
#include "ServerRule.h"
#include "IosNetState.h"
#include "StringUtils.h"
#include "TimeManager.h"

bool VersionManager::init()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    localVersion = INSTANCE(JniManager)->jniGetVersion();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    localVersion = IosNetState::getIosVersion();
#endif
    firstLogin = true;
    serverVersion = "";
    CCFileUtils::sharedFileUtils()->addSearchPath(CCFileUtils::sharedFileUtils()->getWritablePath().c_str());
    return true;
}

void VersionManager::checkVersion()
{
    bool openNet = INSTANCE(NetStateManager)->getNetState();
    if(openNet){
        //有网，下载配置文件
        downloadConfigFile();
    }else{
        //断网
    }
    
}

bool VersionManager::hasNewVersion()
{
    //一天检测一次
    if(getLocalVersion() == getServerVersion()){
        return false;
    }
    return true;
}

void VersionManager::updateNewVersion()
{
//#if (defined VERSION_PP) || (defined VERSION_PPJB)
//    
//#else
    INSTANCE(MessageBoxFacade)->showMessageBox("检测到新版本，是否更新？", this, callfunc_selector(VersionManager::updateNewVersionHandler));
//#endif
}

string VersionManager::getLocalVersion()
{
    return localVersion;
}

string VersionManager::getServerVersion()
{
    if(serverVersion == ""){
        serverVersion = INSTANCE(ServerRule)->getVersion();
        CCLog(serverVersion.c_str());
    }
    return serverVersion;
}

void VersionManager::updateNewVersionHandler()
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    INSTANCE(JniManager)->jniUpdateNewVersion();
//#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    IosNetState::goToAppStore(INSTANCE(ServerRule)->getNewVersionUrl().c_str());
//#endif
}



void VersionManager::downloadConfigFile()
{
    if(firstLogin){
        firstLogin = false;
        INSTANCE(CommonLoadingFacade)->showLoading();
        
        string fileName;
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        fileName = "server_ios.txt";
#else
        fileName = "server_android.txt";
#endif
        
        INSTANCE(HttpDown)->downloadFile(fileName, "http://s1.sj.37pp.cn/" + fileName, this, callfuncO_selector(VersionManager::downloadHandler));
    }
}

void VersionManager::downloadHandler(cocos2d::CCString *param)
{
    CCLog("下载配置文件成功");
    INSTANCE(CommonLoadingFacade)->hideLoading();
    if(noticeUpdateTime()){
        if(INSTANCE(VersionManager)->hasNewVersion()){
            INSTANCE(VersionManager)->updateNewVersion();
        }
        CCLog("提示更新");
    }else{
        CCLog("不提示更新");
    }
    CCUserDefault::sharedUserDefault()->setStringForKey(Last_notice_update_time, INSTANCE(StringUtils)->int64ToString(INSTANCE(TimeManager)->getSystemTimeM()));
    CCUserDefault::sharedUserDefault()->flush();
    CCLOG("当前版本%s,服务器版本%s",localVersion.c_str(),getServerVersion().c_str());
}

bool VersionManager::noticeUpdateTime()
{
    string _t = CCUserDefault::sharedUserDefault()->getStringForKey(Last_notice_update_time,"0");
    int64_t lastTime = INSTANCE(StringUtils)->stringToInt64(_t);
    if(lastTime == 0){
        return true;
    }
    if(INSTANCE(TimeManager)->isSameDay(lastTime, INSTANCE(TimeManager)->getSystemTimeM())){
        return false;
    }
    return true;
}
