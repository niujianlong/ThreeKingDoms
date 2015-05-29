//
//  RechargeManager.h
//  threeKingdoms
//  Created by sma11case 14-2-28.
//
//

#ifndef __threeKingdoms__RechargeManager__
#define __threeKingdoms__RechargeManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "md5.h"

using namespace std;
USING_NS_CC;

#define Recharge_serverId "330001"
#define Recharge_get_url "http://charge.wgzx.37pp.cn/index.php?m=Charge&a=fl_sj_action_get_token&"
#define Recharge_appId "12617"

//#define Recharge_check_url "http://charge.wgzx.37pp.cn/index.php?m=Charge&a=fl_sj_check_order&"

#define Recharge_mode 1

class RechargeManager:public CCObject
{
public:
    CLASS_INSTANCE(RechargeManager);
    bool init();
    
    void recharge(int rechargeId);
    void rechargeVerification();
private:
    
    void completeHandler(CCString *resultString);
    void verificationHandler(CCString *resultString);
    
    int code;
    string order_id;
    string taken_id;
    
    int rechargeId;
};

#endif /* defined(__threeKingdoms__RechargeManager__) */
