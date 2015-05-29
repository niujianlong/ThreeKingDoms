//
//  RechargeManager.cpp
//  threeKingdoms
//
//  Created by .m on 14-2-28.
//
//

#include "RechargeManager.h"
#include "HttpDown.h"
#include "StringUtils.h"
#include "JniManager.h"
#include "UserData.h"
#include "SingleRecharge.h"
#include "CommonLoading.h"
#include "GameUtils.h"
#include "FightManager.h"
#include "RechargeRule.h"
#include "NoticeBox.h"

#include "spine/Json.h"

#include "ServerRule.h"

//#ifdef VERSION_PP
//#include "PPLoginFacade.h"
//#elif VERSION_APP
#include "IAPFacade.h"
//#endif

bool RechargeManager::init()
{
    return true;
}

void RechargeManager::recharge(int rechargeId)
{
    this->rechargeId = rechargeId;
    int moneyCount = INSTANCE(RechargeRule)->getRechargePrice(rechargeId);
    int goldCount = INSTANCE(RechargeRule)->getRechargeGoldCount(rechargeId);
    
//#ifdef VERSION_PP
//    PPLoginFacade login;
//    login.exchangeGoods(moneyCount, "test", 30001, "元宝");
//    INSTANCE(UserData)->setChargeAmount(goldCount);
//#elif VERSION_APP
//    int temp = (rechargeId - 1) % 6;
//    buy(temp);
//    
//    INSTANCE(CommonLoadingFacade)->showLoading();
//#else
    
    CCString *gold = CCString::createWithFormat("%d元宝",goldCount);
    CCString *url = CCString::createWithFormat("%sserver_id=%s&user_id=%s&action=create_order&mode=%d&app_id=%s&subject=%s&price=%d&quantity=1&total_fee=%d",INSTANCE(ServerRule)->getRechargeUrl().c_str(),Recharge_serverId,INSTANCE(GameUtils)->getUniqueIdentifier(),Recharge_mode,Recharge_appId,gold->getCString(),moneyCount * 100, moneyCount * 100);
    INSTANCE(CommonLoadingFacade)->showLoading();
    CCLog(url->getCString());
    INSTANCE(HttpDown)->sendHttpRequest(url->getCString(),this,callfuncO_selector(RechargeManager::completeHandler));
//#endif
}

void RechargeManager::completeHandler(cocos2d::CCString *resultString)
{
    INSTANCE(CommonLoadingFacade)->hideLoading();
    string result = resultString->getCString();
    CCLOG("回调:%s",result.c_str());
    result.erase(0, 3);
    Json *json = Json_create(result.c_str());
    
    code = Json_getInt(json, "code", 0);
    order_id = Json_getString(json, "order_id", 0);
    taken_id = Json_getString(json, "token_id", 0);
    
    CCLOG("code:%d,order_id:%s,taken_id:%s",code,this->order_id.c_str(),this->taken_id.c_str());
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if(code == 1){
        INSTANCE(JniManager)->jniRecharge(taken_id);
    }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    INSTANCE(UserData)->addCurrentMoney(999999);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(Recharge_Notice);
    INSTANCE(UserData)->setVipLevel(1);
#endif
}

void RechargeManager::rechargeVerification()
{
    //跳过验证，直接充值
    CCLog("充值成功");
    int goldCount = INSTANCE(RechargeRule)->getRechargeGoldCount(rechargeId);
    INSTANCE(NoticeBoxFacade)->showNoticeBox(CCString::createWithFormat("恭喜你充值成功，获得%d元宝",goldCount)->getCString());
    INSTANCE(UserData)->addCurrentMoney(goldCount);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(Recharge_Notice);
    
    
    
//    INSTANCE(CommonLoadingFacade)->showLoading();
//    //充值返回成功，请求服务器验证充值结果
//    CCString *url = CCString::createWithFormat("%saction=get_result&mode=%d&order_id=%s&token_id=%s",Recharge_check_url,0,order_id.c_str(),taken_id.c_str());
//    CCLog(url->getCString());
//    INSTANCE(HttpDown)->sendHttpRequest(url->getCString(),this,callfuncO_selector(RechargeManager::verificationHandler));
}

void RechargeManager::verificationHandler(cocos2d::CCString *resultString)
{
    INSTANCE(CommonLoadingFacade)->hideLoading();
    //验证结果返回
    string result = resultString->getCString();
    CCLOG("充值验证结果:%s",result.c_str());
    
    result.erase(0, 3);
    Json *json = Json_create(result.c_str());
    int code = Json_getInt(json, "code", 0);
    
    if(code == 1){
        //充值验证 确认充值成功
        CCLog("充值成功");
        int goldCount = INSTANCE(RechargeRule)->getRechargeGoldCount(rechargeId);
        INSTANCE(NoticeBoxFacade)->showNoticeBox(CCString::createWithFormat("恭喜你充值成功，获得%d元宝",goldCount)->getCString());
        INSTANCE(UserData)->addCurrentMoney(goldCount);
        CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
    }
    
}