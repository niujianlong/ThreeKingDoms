//
//  DebugInfoUI.cpp
//  threeKingdoms
//  Created by sma11case on 14-1-4.
//
//

#include "DebugInfoUI.h"
#include "GameUtils.h"
#include "FightManager.h"

bool DebugInfoUI::init()
{
    if(!CCLayer::init()){
        return false;
    }
//    setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
    
    info = CCLabelTTF::create();
    info->setFontSize(24);
    info->setColor(ccWHITE);
    addChild(info);
    info->setPosition(ccp(-INSTANCE(GameUtils)->getWindowsCenterPosition().x + 50, 290));
    info->setAnchorPoint(ccp(0,1));
    info->setString("攻击后显示数据");
//    scheduleUpdate();
    
    return true;
}

void DebugInfoUI::onEnter()
{
    success_num = 0;
    miss_num = 0;
    num_1 = 0;
    num_2 = 0;
    num_5 = 0;
    num_8 = 0;
    num_10 = 0;
    num_20 = 0;
    num_30 = 0;
    num_40 = 0;
    num_80 = 0;
    num_90 = 0;
    num_100 = 0;
    attack_num = 0;
    CCLayer::onEnter();
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(DebugInfoUI::updateInfo), NoticeDebugInfo, NULL);
}

void DebugInfoUI::onExit()
{
    CCLayer::onExit();
    removeAllChildren();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NoticeDebugInfo);
}

void DebugInfoUI::updateInfo()
{
    vector<int> infoVector = INSTANCE(FightManager)->getDebugInfo();
    if(infoVector[0]){
        success_num++;
    }else{
        miss_num++;
    }
    
    switch (infoVector[1]) {
        case 1:
            num_1++;
            break;
        case 2:
            num_2++;
            break;
        case 4:
            num_5++;
            break;
        case 5:
            num_8++;
            break;
        case 8:
            num_10++;
            break;
        case 10:
            num_20++;
            break;
        case 20:
            num_30++;
            break;
        case 40:
            num_40++;
            break;
        case 50:
            num_80++;
            break;
        case 80:
            num_90++;
            break;
        case 100:
            num_100++;
            break;
        default:
            break;
    }
    
    attack_num++;
    
    CCString *infoStr = CCString::createWithFormat(" 周期状态:%s\n 命中次数:%d\n 闪避次数:%d\n 攻击次数:%d\n 1分次数:%d\n 2分次数:%d\n 4分次数:%d\n 5分次数:%d\n 8分次数:%d\n 10分次数:%d\n 20分次数:%d\n 40分次数:%d\n 50分次数:%d\n 80分次数:%d\n 100分次数:%d\n 本次状态:%s\n 本次得分:%d",infoVector[2] == 1?"出分":"吃分",success_num,miss_num,attack_num,num_1,num_2,num_5,num_8,num_10,num_20,num_30,num_40,num_80,num_90,num_100,infoVector[0] == 1?"命中":"闪避",infoVector[1]);
    info->setString(infoStr->getCString());
}