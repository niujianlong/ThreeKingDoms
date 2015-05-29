//
//  HttpDown.cpp
//  threeKingdoms
//
//  Created by .m on 14-2-28.
//
//

#include "HttpDown.h"

bool HttpDown::init()
{
    return true;
}

void HttpDown::sendHttpRequest(string url,CCObject *target,SEL_CallFuncO selector)
{
    CCHttpRequest * request = new CCHttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, callfuncND_selector(HttpDown::completeHandler));
    request->setTag("none");
    CCHttpClient::getInstance()->setTimeoutForConnect(20);
    CCHttpClient::getInstance()->send(request);
    request->release();
    
    this->target = target;
    this->selector = selector;
}

void HttpDown::completeHandler(cocos2d::CCNode *sender, void *data)
{
    CCHttpResponse *response = (CCHttpResponse*)data;
    if(!response) {
        return;
    }
    vector<char> * buffer = response->getResponseData();
    string result(buffer->begin(),buffer->end());
    if(response->isSucceed()) {
        (target->*selector)(CCString::create(result));
    }
}


void HttpDown::downloadFile(string fileName,string url,CCObject *target,SEL_CallFuncO selector)
{
    CCHttpRequest * request = new CCHttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, callfuncND_selector(HttpDown::downloadCompleteHandler));
    request->setTag(fileName.c_str());
    CCHttpClient::getInstance()->setTimeoutForConnect(20);
    CCHttpClient::getInstance()->send(request);
    request->release();
    
    this->downloadTarget = target;
    this->downloadSelector = selector;
}

void HttpDown::downloadCompleteHandler(cocos2d::CCNode *sender, void *data)
{
    CCHttpResponse *response = (CCHttpResponse*)data;
    if(!response) {
        return;
    }
    std::vector<char> * buffer = response->getResponseData();
    std::string bufffff(buffer->begin(),buffer->end());
    
    //保存到本地文件
    string tag = response->getHttpRequest()->getTag();
    ;
    string path = CCFileUtils::sharedFileUtils()->getWritablePath() + tag;
    CCLOG("Save file: %s", path.c_str());
    FILE * fp = fopen(path.c_str(), "wb+");
    fwrite(bufffff.c_str(), 1, buffer->size(), fp);
    fclose(fp);
    if(response->isSucceed()) {
        (downloadTarget->*downloadSelector)(CCString::create("success"));
    }
}