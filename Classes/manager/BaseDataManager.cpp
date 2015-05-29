//
//  BaseDataManager.cpp
//  threeKingdoms
//  Created by sma11case 13-12-26.
//
//

#include "BaseDataManager.h"
#include "StringUtils.h"

bool BaseDataManager::init()
{
    xmlDic = CCDictionary::create();
    xmlDic->retain();
    
    lanDic = CCDictionary::create();
    lanDic->retain();
    
    return true;
}

void BaseDataManager::removeAllXml()
{
    xmlDic->removeAllObjects();
}

CCDictionary* BaseDataManager::getXml(const char *xmlPath)
{
    if(xmlDic->objectForKey(xmlPath)){
        return (CCDictionary*)xmlDic->objectForKey(xmlPath);
    }
    
    tinyxml2::XMLDocument doc;
    string path;
    path = "xml/";
    
    path.append(xmlPath);
    unsigned long size = 0;
    doc.Parse((const char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "r", &size));
    tinyxml2::XMLElement *rootElement = doc.RootElement();
    tinyxml2::XMLElement *pItemElement = rootElement->FirstChildElement();
    tinyxml2::XMLNode *pNextChild = pItemElement->ToElement();
    
    CCDictionary *dic = CCDictionary::create();
    
    while (pNextChild) {
        tinyxml2::XMLElement* element = pNextChild->ToElement();
        element = element->FirstChildElement();
        
        CCDictionary *subDic = CCDictionary::create();
        string id = element->FirstChild()->Value();
        while (element) {
            if (element!=NULL && element->FirstChild()!=NULL && element->FirstAttribute()!=NULL) {
                subDic->setObject(CCStringMake(element->FirstChild()->Value()), element->Value());
            }
            element = element->NextSiblingElement();
        }
        dic->setObject(subDic, id.c_str());
        pNextChild = pNextChild->NextSibling();
    }
    xmlDic->setObject(dic, xmlPath);
    return dic;
}

string BaseDataManager::getLan(string param)
{
    if(lanDic->count() == 0){
        loadLan();
    }
    CCString *result = (CCString*) lanDic->objectForKey(param.c_str());
    if(result){
        return result->getCString();
    }else{
        return "missLanguage";
    }
}

void BaseDataManager::loadLan()
{
    string path = "language/conf_lang.txt";
    unsigned long size = 0;
    string content =(const char*) CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "r", &size);
    
    vector<vector<string> > result = INSTANCE(StringUtils)->getStringVectorFromString(content, "\r\n", "=");
    
    for(int i=0;i<result.size();i++){
        if(result[i].size()<=1){
            break;
        }
        lanDic->setObject(CCStringMake(result[i][1]), result[i][0]);
    }
}