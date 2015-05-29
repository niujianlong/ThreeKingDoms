//
//  OnlineReward.h
//  threeKingdoms
//
//  Created by .m on 14-2-14.
//
//

#ifndef __threeKingdoms__OnlineReward__
#define __threeKingdoms__OnlineReward__

#include <iostream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class OnlineReward:public CCNode
{
public:
    CREATE_FUNC(OnlineReward);
    OnlineReward();
    ~OnlineReward();
    
    virtual bool init();
    
    void updateTime();
    
    virtual void onEnter();
    virtual void onExit();
private:
    void initContent();
    CCProgressTimer *bar;
    CCLabelTTF *label;
    
    void receiveHandler();
    bool receivable;
    
    int times;
    int money;
    int time;
};

#endif /* defined(__threeKingdoms__OnlineReward__) */
