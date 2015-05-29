//
//  SingleRecharge.h
//  threeKingdoms
//  Created by sma11case 14-2-8.
//
//

#ifndef __threeKingdoms__SingleRecharge__
#define __threeKingdoms__SingleRecharge__

#include <iostream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

#define Recharge_Notice "rechargeNotice"

class SingleRecharge:public CCNode
{
public:
    static SingleRecharge* create(int rechargeId);
    SingleRecharge(int rechargeId);
    ~SingleRecharge();
    
    virtual bool init();
private:
    int rechargeId;
    void initContent();
    
    int getMoneyNum();
    int getGoldNum();
    
    string getMoneyIconImgName();
    
    void rechargeHandler();
};

#endif /* defined(__threeKingdoms__SingleRecharge__) */
