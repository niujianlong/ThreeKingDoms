//
//  VersionManager.h
//  threeKingdoms
//  Created by sma11case on 14-3-6.
//
//

#ifndef __threeKingdoms__VersionManager__
#define __threeKingdoms__VersionManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

#define Last_notice_update_time "lastNoticeUpdateTime"

class VersionManager:public CCObject
{
public:
    CLASS_INSTANCE(VersionManager);
    bool init();
    
    void checkVersion();
private:
    string getLocalVersion();
    string getServerVersion();
    
    bool hasNewVersion();
    void updateNewVersion();
    
    void downloadConfigFile();
    
    
    void updateNewVersionHandler();
    
    void downloadHandler(CCString *param);
    
    string localVersion;
    string serverVersion;
    
    bool noticeUpdateTime();
    
    bool firstLogin;
};

#endif /* defined(__threeKingdoms__VersionManager__) */
