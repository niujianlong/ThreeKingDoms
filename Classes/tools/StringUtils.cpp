//
//  StringUtils.cpp
//  threeKingdoms
//  Created by sma11case on 13-12-27.
//
//

#include "StringUtils.h"

bool StringUtils::init()
{
    return true;
}

string StringUtils::intToString(int param)
{
    CCString *temp = CCString::createWithFormat("%d",param);
    return temp->getCString();
}

string StringUtils::int64ToString(int64_t param)
{
    CCString *temp = CCString::createWithFormat("%lld",param);
    return temp->getCString();
}

int StringUtils::stringToInt(CCString *param)
{
    return atoi(param->getCString());
}

int StringUtils::stringToInt(string param)
{
    return atoi(param.c_str());
}

int StringUtils::stringToInt(const char *param)
{
    return atoi(param);
}

float StringUtils::stringToFloat(string param)
{
    return atof(param.c_str());
}

float StringUtils::stringToFloat(const char *param)
{
    return atof(param);
}

int64_t StringUtils::stringToInt64(const char *param)
{
    return atoll(param);
}

int64_t StringUtils::stringToInt64(string param)
{
    return atoll(param.c_str());
}

vector<int> StringUtils::getIntVectorFromString(string content,const char *p1)
{
    vector<int> result;
    vector<string> temp = getVector(content, p1);
    for(int i=0;i<temp.size();i++){
        result.push_back(atoi(temp[i].c_str()));
    }
    return result;
}

vector<vector<int> > StringUtils::getIntVectorFromString(string content, const char* p1, const char* p2)
{
    vector< vector<int> > result;
    vector< vector<string> > temp = getStringVectorFromString(content, p1, p2);
    for(int i=0;i<temp.size();i++){
        vector<int> t;
        for(int j=0;j<temp[i].size();j++){
            t.push_back(atoi(temp[i][j].c_str()));
        }
        result.push_back(t);
    }
    return result;
}

vector<float> StringUtils::getFloatVectorFromString(string content,const char *p1)
{
    vector<float> result;
    vector<string> temp = getVector(content, p1);
    for(int i=0;i<temp.size();i++){
        result.push_back(atof(temp[i].c_str()));
    }
    return result;
}

vector<vector<float> > StringUtils::getFloatVectorFromString(string content, const char* p1, const char* p2)
{
    vector< vector<float> > result;
    vector< vector<string> > temp = getStringVectorFromString(content, p1, p2);
    for(int i=0;i<temp.size();i++){
        vector<float> t;
        for(int j=0;j<temp[i].size();j++){
            t.push_back(atof(temp[i][j].c_str()));
        }
        result.push_back(t);
    }
    return result;
}

vector<string> StringUtils::getStringVectorFromString(string content,const char *p1)
{
    return getVector(content, p1);
}

vector<vector<string> > StringUtils::getStringVectorFromString(string content,const char *p1,const char* p2)
{
    vector<vector<string> > result;
    vector<string> temp = getVector(content, p1);
    for(int i=0;i<temp.size();i++)
    {
        vector<string> t = getVector(temp[i], p2);
        result.push_back(t);
    }
    return result;
}

vector<string> StringUtils::getVector(string content, const char *p1)
{
    vector<string> result;
    if(content == ""){
        return result;
    }
    char c[20480];
    char *resource = const_cast<char*>(content.data());
    strcpy(c, resource);
    
    char *p;
    strtok(c, p1);
    result.push_back(c);
    while((p = strtok(NULL, p1)))
        result.push_back(p);
    
    return result;
}

string StringUtils::addEnter(string content)
{
    string result = "";

    for(string::size_type i = 0;i<content.size();i+=3){
        result.append(content.substr(i,3) + "\n");
    }
    return result;
}

string StringUtils::dountDownToString(int64_t time)
{
    time_t temp = time / 1000;
    tm *timeStruct = gmtime(&temp);
    char str[64] = {"00"};
    if(timeStruct->tm_hour > 0){
        sprintf(str, "%02d:%02d:%02d",
                timeStruct->tm_hour,
                timeStruct->tm_min,
                timeStruct->tm_sec);
    }else{
        sprintf(str, "%02d:%02d",
                timeStruct->tm_min,
                timeStruct->tm_sec);
    }
    std::string timeTemp = str;
    return timeTemp;
}

string StringUtils::numToString(int param)
{
    if(param < 10000){
        CCString *temp = CCString::createWithFormat("%d",param);
        return temp->getCString();
    }else{
        float tempF = float(param)/10000.0f;
        
        CCString *temp;
        if(param % 10000 == 0){
            temp = CCString::createWithFormat("%.0f万",tempF);
        }else if(param % 1000 == 0){
            temp = CCString::createWithFormat("%.1f万",tempF);
        }else{
            temp = CCString::createWithFormat("%.2f万",tempF);
        }
        return temp->getCString();
    }
    
}

map<int, vector<int> > StringUtils::getIntMapFromString(string content, const char *p1, const char *p2)
{
    map<int, vector<int> > resultMap;
    vector< vector<string> > temp = getStringVectorFromString(content, p1, p2);
    for(int i=0;i<temp.size();i++){
        vector<int> t;
        for(int j=1;j<temp[i].size();j++){
            t.push_back(atoi(temp[i][j].c_str()));
        }
        resultMap[atoi(temp[i][0].c_str())] = t;
    }
    return resultMap;
}

string StringUtils::intVectorToString(vector<int> param)
{
    string result = "";
    for(int i=0;i<param.size();i++){
        if(i == 0){
            result.append(INSTANCE(StringUtils)->intToString(param[i]));
        }else{
            result.append("_" + INSTANCE(StringUtils)->intToString(param[i]));
        }
    }
    return result;
}

string StringUtils::intMapToString(map<int, vector<int> > param)
{
    string result = "";
    
    for(map<int, vector<int> >::iterator it = param.begin();it != param.end();it++){
        string resultT = "";
        vector<int> t = it->second;
        resultT.append(intToString(it->first));
        for(int i=0;i<t.size();i++){
            resultT.append("_" + intToString(t[i]));
        }
        if(it == param.begin()){
            result.append(resultT);
        }else{
            result.append("|"+resultT);
        }
    }
    return result;
}

string StringUtils::replace(string content, string target, string source)
{
    string result;
    string::size_type start = content.find(target.c_str());
    if(start == string::npos){
        return content;
    }
    string::size_type length = target.length();
    content.replace(start, length, source.c_str());
    result = content;
    return result;
}

string StringUtils::deleteString(string content, string target)
{
    string result;
    string::size_type start = content.find(target.c_str());
    if(start == string::npos){
        return content;
    }
    string::size_type length = target.length();
    content.erase(start, length);
    result = content;
    
    result = deleteString(result, target);
    
    return result;
}
