//
//  IosNetState.cpp
//  threeKingdoms
//  Created by sma11case on 14-3-6.
//
//

#include "IosNetState.h"
#import <Foundation/Foundation.h>
#import "Reachability.h"

NetState IosNetState::getIosNetState()
{
    Reachability *r = [Reachability reachabilityWithHostName:@"www.apple.com"];
    switch ([r currentReachabilityStatus]) {
        case NotReachable:
            // 没有网络连接
            return NetState_noNetWork;
            break;
        case ReachableViaWWAN:
            // 使用3G网络
            return NetState_other;
            break;
        case ReachableViaWiFi:
            // 使用WiFi网络
            return NetState_wifi;
            break;
    }
}

string IosNetState::getIosVersion()
{
    NSString *versionStr = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
    string result = versionStr.UTF8String;
    return result;
}

void IosNetState::goToAppStore(const char *url)
{
    NSString *itunesLink = [NSString stringWithUTF8String:url];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:itunesLink]];
}

