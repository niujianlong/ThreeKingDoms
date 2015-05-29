//
//  DebugInfoUI.h
//  threeKingdoms
//  Created by sma11case on 14-1-4.
//
//

#ifndef __threeKingdoms__DebugInfoUI__
#define __threeKingdoms__DebugInfoUI__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class DebugInfoUI:public CCLayer
{
public:
    CREATE_FUNC(DebugInfoUI);
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    CCLabelTTF *info;
    void updateInfo();
    //命中次数
    int success_num;
    //闪避次数
    int miss_num;
    
    //1分次数
    int num_1;
    //2分次数
    int num_2;
    //5分次数
    int num_5;
    //8分次数
    int num_8;
    //10分次数
    int num_10;
    //20分次数
    int num_20;
    //30分次数
    int num_30;
    //40分次数
    int num_40;
    //80分次数
    int num_80;
    //90分次数
    int num_90;
    //100分次数
    int num_100;
    
    //攻击总次数
    int attack_num;
};

#endif /* defined(__threeKingdoms__DebugInfoUI__) */
