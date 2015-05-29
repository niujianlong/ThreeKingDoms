//
//  HttpDown.h
//  threeKingdoms
//  Created by sma11case 14-2-28.
//
//

#ifndef __threeKingdoms__HttpDown__
#define __threeKingdoms__HttpDown__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class HttpDown:public CCObject
{
public:
    CLASS_INSTANCE(HttpDown);
    bool init();
    
    void sendHttpRequest(string url,CCObject *target,SEL_CallFuncO selector);
    
    void downloadFile(string fileName,string url,CCObject *target,SEL_CallFuncO selector);
private:
    void completeHandler(cocos2d::CCNode *sender, void *data);
    CCObject *target;
    SEL_CallFuncO selector;
    
    void downloadCompleteHandler(cocos2d::CCNode *sender, void *data);
    CCObject *downloadTarget;
    SEL_CallFuncO downloadSelector;
};

#endif /* defined(__threeKingdoms__HttpDown__) */
