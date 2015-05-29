//
//  NoticeBox.h
//  threeKingdoms
//
//  Created by .m on 14-2-8.
//
//

#ifndef __threeKingdoms__NoticeBox__
#define __threeKingdoms__NoticeBox__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class NoticeBox:public CCLayer
{
public:
    static NoticeBox *create(string messageContent,CCObject *target ,SEL_CallFunc selector ,string btn1Label);
    
    NoticeBox(string messageContent,CCObject *target ,SEL_CallFunc selector ,string btn1Label);
    
    ~NoticeBox();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    string messageContent;
    string btn1Label;
    
    CCObject *target;
    SEL_CallFunc selector;
    
    void initContent();
    
    void comfirmHandler();
    
    
};

class NoticeBoxFacade:public CCObject
{
public:
    CLASS_INSTANCE(NoticeBoxFacade);
    bool init();
    
    void showNoticeBox(string messageContent,CCObject *target = NULL,SEL_CallFunc selector = NULL,string btn1Label = "确定");
    
    void exitGame();
    
    void setIsShow(bool param);
private:
    bool isShow;
};

#endif /* defined(__threeKingdoms__NoticeBox__) */
