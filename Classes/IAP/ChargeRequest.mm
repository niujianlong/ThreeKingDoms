//
//  ChargeRequest.cpp
//  legendofheros
//
//  Created by lee song on 13-11-8.
//
//

#include "ChargeRequest.h"
#include <string>
#include "json.h"
#include "IAPHelper.h"
#include "Recharge.h"
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

using std::string;

bool ChargeRequest::init()
{
    return true;
}

ChargeRequest::ChargeRequest()
{
    
}

ChargeRequest::~ChargeRequest()
{
    
}

void ChargeRequest::onSendRequest(cocos2d::CCString* receipt)
{
//    CCHttpRequest* request = new CCHttpRequest();//创建对象
//    string serverId = INSTANCE(LoginInfo)->serverId;
//    string account = INSTANCE(User)->account;
//    string url = INSTANCE(BaseDataManager)->getXmlMap(INSTANCE(BaseDataManager)->SERVER)[serverId]["chargeUrl"];
//    
//    string postData;
//    postData.append("account=");
//    postData.append(account);
//    postData.append("&serverId=");
//    postData.append(serverId);
//    postData.append("&receipt=");
//    
//    postData.append(receipt->getCString());
//    CCLog("receip:%s", receipt->getCString());
//    request->setUrl(url.c_str());//设置请求地址
//    request->setRequestType(CCHttpRequest::kHttpPost);
//    /*请求的类型
//     kHttpGet,get请求
//     kHttpPost,post请求
//     kHttpUnkown 呵呵
//     */
//    request->setResponseCallback(this, callfuncND_selector(ChargeRequest::onGetFinished));//请求完的回调函数
//    request->setRequestData(postData.c_str(), postData.size());//请求的数据
//    request->setTag("get qing  qiu baidu ");//tag
//    CCHttpClient::getInstance()->send(request);//发送请求
//    request->release();//释放内存，前面使用了new
}

void ChargeRequest::onGetFinished(cocos2d::CCObject *pSender, void *data)
{
//    CCHttpResponse* response = (CCHttpResponse*)data;
//    
//    vector<char>* responseData = response->getResponseData();
//    string value = "";
//    for (int i = 0; i < responseData->size(); i++) {
//        value.append(1, (*responseData)[i]);
//    }
//    
//    Json::Reader reader;
//    Json::Value root;
//    
//    reader.parse(value, root);
//    
//    if (root.size() == 0) {
//        INSTANCE(LHNoticeBox)->showMessage("操作超时。");
//        INSTANCE(ConnectLoading)->hideConnectLoading();
//        return;
//    }
//    
//    string code = root["code"].asString();
//    
//    if (code == "100") {
//        int vip = INSTANCE(User)->vipLevel;
//        
//        Charge* charge = (Charge*)INSTANCE(UIManager)->getUI(INSTANCE(UIManager)->charge);
//        
//        if (charge != NULL) {
//            charge->setVIPLevel(vip);
//        }
//        
//        NSString* orderId = [[IAPHelper sharedInstance] storedOrderId];
//        
//        [[IAPHelper sharedInstance] removeOrder:orderId];
//        
//        
//        INSTANCE(LHNoticeBox)->showMessage(INSTANCE(LanguageManager)->getLan(885));
//    }
//    else
//    {
//        string message = INSTANCE(LanguageManager)->getLan(886);
//        message.append(code);
//        INSTANCE(LHNoticeBox)->showMessage(message.c_str());
//    }
}

void ChargeRequest::processOrders()
{
    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("AppOrders.plist");
    
    NSMutableDictionary* orders = [NSMutableDictionary dictionaryWithContentsOfFile:[[NSString alloc] initWithUTF8String:path.c_str()]];
    
    if ([orders count] > 0) {
        
        for (id key in [orders allKeys]) {
            NSString* receipt = [orders objectForKey:key];
            
            onSendRequest(CCString::create([receipt UTF8String]));
            
            [IAPHelper sharedInstance].storedOrderId = key;
        }
    }
}