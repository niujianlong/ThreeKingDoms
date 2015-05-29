//
//  GameUtils.h
//  threeKingdoms
//  Created by sma11case on 13-12-24.
//
//

#ifndef __threeKingdoms__GameUtils__
#define __threeKingdoms__GameUtils__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

#define getCenterPosition(node) INSTANCE(GameUtils)->getNodeCenterPosition(node)

using namespace std;
USING_NS_CC;

class GameUtils:public CCObject
{
public:
    CLASS_INSTANCE(GameUtils);
    bool init();
    
    CCPoint getWindowsCenterPosition();
    
    CCPoint getNodeCenterPosition(CCNode *node);
    
    int getRandom(int size);
    
    //param格式: 类型1_概率|类型2_概率|类型3_概率
    int getRandomFromVector(vector<vector<float> > param);
    //平均概率
    int getRandomFromVector(vector<int> param);
    //param 概率 返回值 true 抽到该概率
    bool getRandomFromFloat(float param);
    
    bool vectorContainInt(vector<int> v,int _p);
    
    
    const char* getUniqueIdentifier();
};

#endif /* defined(__threeKingdoms__GameUtils__) */
