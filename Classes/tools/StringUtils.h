//
//  StringUtils.h
//  threeKingdoms
//  Created by sma11case 13-12-27.
//
//

#ifndef __threeKingdoms__StringUtils__
#define __threeKingdoms__StringUtils__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class StringUtils:public CCObject
{
public:
    CLASS_INSTANCE(StringUtils);
    bool init();
    
    string intToString(int param);
    
    string int64ToString(int64_t param);
    
    int stringToInt(CCString *param);
    
    int stringToInt(string param);
    
    int stringToInt(const char* param);
    
    float stringToFloat(string param);
    
    float stringToFloat(const char* param);
    
    int64_t stringToInt64(const char* param);
    
    int64_t stringToInt64(string param);
    
    vector<int> getIntVectorFromString(string content,const char *p1);
    
    vector<vector<int> > getIntVectorFromString(string content, const char* p1, const char* p2);
    
    vector<float> getFloatVectorFromString(string content,const char *p1);
    
    vector<vector<float> > getFloatVectorFromString(string content, const char* p1, const char* p2);
    
    vector<string> getStringVectorFromString(string content,const char *p1);
    
    vector<vector<string> > getStringVectorFromString(string content,const char *p1,const char* p2);
    
    map<int, vector<int> > getIntMapFromString(string content, const char* p1, const char* p2);
    
    string addEnter(string content);
    
    string dountDownToString(int64_t time);
    
    string numToString(int param);
    
    string intVectorToString(vector<int> param);
    
    string intMapToString(map<int, vector<int> > param);
    
    string replace(string content,string target,string source);
    
    string deleteString(string content,string target);

private:
    
    vector<string> getVector(string content, const char* p1);
};

#endif /* defined(__threeKingdoms__StringUtils__) */
