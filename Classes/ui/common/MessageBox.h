//
//  MessageBox.h
//  threeKingdoms
//  Created by sma11case on 14-2-8.
//
//

#ifndef __threeKingdoms__MessageBox__
#define __threeKingdoms__MessageBox__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class MessageBox:public CCLayer
{
public:
    static MessageBox *create(string messageContent,CCObject *target,SEL_CallFunc selector,string btn1Label,string btn2Label,SEL_CallFunc selector2);
    
    MessageBox(string messageContent,CCObject *target,SEL_CallFunc selector,string btn1Label,string btn2Label,SEL_CallFunc selector2);
    
    ~MessageBox();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    string messageContent;
    string btn1Label;
    string btn2Label;
    CCObject *target;
    SEL_CallFunc selector;
    SEL_CallFunc selector2;
    
    void initContent();
    
    void comfirmHandler();
    void cancelHandler();
};

class MessageBoxFacade:public CCObject
{
public:
    CLASS_INSTANCE(MessageBoxFacade);
    bool init();
    
    void showMessageBox(string messageContent,CCObject *target,SEL_CallFunc selector,string btn1Label = "确定",string btn2Label = "取消",SEL_CallFunc selector2 = NULL);
    
    void setIsShow(bool param);
private:
    bool isShow;
    
};

#endif /* defined(__threeKingdoms__MessageBox__) */
