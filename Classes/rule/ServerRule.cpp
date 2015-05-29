//
//  ServerRule.cpp
//  threeKingdoms
//  Created by sma11case on 14-3-6.
//
//

#include "ServerRule.h"
#include "spine/Json.h"

bool ServerRule::init()
{
    return true;
}

string ServerRule::getVersion()
{
    return getServerAttribute("version");
}

string ServerRule::getNewVersionUrl()
{
    return getServerAttribute("clientUpdateVersionUrl");
}

string ServerRule::getRechargeUrl()
{
    return getServerAttribute("requestChargeOrderIdUrl");
}

string ServerRule::getServerAttribute(const char *attributeName)
{
    unsigned long size = 0;
    string fileName;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    fileName = "server_ios.txt";
#else
    fileName = "server_android.txt";
#endif
    string path = CCFileUtils::sharedFileUtils()->getWritablePath() + fileName;
    string info = (const char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "r", &size);
    
    Json *json = Json_create(info.c_str());
    return Json_getString(json, attributeName, 0);
}