//
//  ChargeRequest.h
//  legendofheros
//  Created by sma11case song on 13-11-8.
//
//

#ifndef __legendofheros__ChargeRequest__
#define __legendofheros__ChargeRequest__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

USING_NS_CC;

class ChargeRequest : public CCObject
{
public:
    CLASS_INSTANCE(ChargeRequest);
    
    bool init();
    
    ChargeRequest();
    ~ChargeRequest();
    
    void onSendRequest(CCString* data);
    void onGetFinished(CCObject* pSender, void* data);
    void processOrders();
};
#endif /* defined(__legendofheros__ChargeRequest__) */
