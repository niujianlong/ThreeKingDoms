//
//  FormationRule.cpp
//  threeKingdoms
//  Created by sma11case 13-12-27.
//
//

#include "FormationRule.h"
#include "StringUtils.h"
#include "BaseDataManager.h"

bool FormationRule::init()
{
    mainDic = NULL;
    lastId = -1;
    return true;
}

string FormationRule::getFormationName(int formationId)
{
    return getFormationAttribute(formationId, "name");
}

string FormationRule::getFormation(int formationId)
{
    return getFormationAttribute(formationId, "formation");
}

vector<int> FormationRule::getFormationNpcVector(int formationId)
{
    string temp = getFormation(formationId);
    vector<int> result = INSTANCE(StringUtils)->getIntVectorFromString(temp, "_");
    return result;
}

int FormationRule::getFormationSpeed(int formationId)
{
    return INSTANCE(StringUtils)->stringToInt(getFormationAttribute(formationId, "speed"));
}

int FormationRule::getFormationType(int formationId)
{
    return INSTANCE(StringUtils)->stringToInt(getFormationAttribute(formationId, "type"));
}

CCDictionary* FormationRule::getFormationDic(int formationId)
{
    if(mainDic == NULL){
        mainDic = INSTANCE(BaseDataManager)->getXml(BaseFormationXml);
    }
    if(lastId != formationId){
        lastId = formationId;
        lastSubDic = (CCDictionary *) mainDic->objectForKey(INSTANCE(StringUtils)->intToString(formationId));
    }
    return lastSubDic;
}

string FormationRule::getFormationAttribute(int formationId, const char *attributeName)
{
    return ((CCString *) getFormationDic(formationId)->objectForKey(attributeName))->getCString();
}

vector<int> FormationRule::getFormationIdVectorByType(int formationType)
{
    vector<int> result;
    if(mainDic == NULL){
        mainDic = INSTANCE(BaseDataManager)->getXml(BaseFormationXml);
    }
    for(int i=0;i<mainDic->count();i++){
        int formationId = atoi(((CCString*) mainDic->allKeys()->objectAtIndex(i))->getCString());
        if(getFormationType(formationId) == formationType){
            result.push_back(formationId);
        }
    }
    return result;
}

