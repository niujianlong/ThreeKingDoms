//
//  FormationRule.h
//  threeKingdoms
//  Created by sma11case on 13-12-27.
//
//

#ifndef __threeKingdoms__FormationRule__
#define __threeKingdoms__FormationRule__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class FormationRule:public CCObject
{
public:
    CLASS_INSTANCE(FormationRule);
    bool init();
    
    //获取阵型名
    string getFormationName(int formationId);
    //获取阵型
    string getFormation(int formationId);
    //获取阵型数组
    vector<int> getFormationNpcVector(int formationId);
    //获取阵型移动速度
    int getFormationSpeed(int formationId);
    //获取阵型类型
    int getFormationType(int formationId);
    
    vector<int> getFormationIdVectorByType(int formationType);
private:
    CCDictionary *getFormationDic(int formationId);
    string getFormationAttribute(int formationId,const char *attributeName);
    
    CCDictionary *mainDic;
    int lastId;
    CCDictionary *lastSubDic;
};

#endif /* defined(__threeKingdoms__FormationRule__) */
