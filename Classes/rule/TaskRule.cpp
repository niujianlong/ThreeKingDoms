//
//  TaskRule.cpp
//  threeKingdoms
//  Created by sma11case on 14-2-19.
//
//

#include "TaskRule.h"
#include "BaseDataManager.h"
#include "StringUtils.h"
#include "GameUtils.h"

bool TaskRule::init()
{
    return true;
}

int TaskRule::getTaskReward(int taskId)
{
    return INSTANCE(StringUtils)->getIntVectorFromString(getTaskAttribute(taskId, "reward"),"_")[1];
}

int TaskRule::getTaskSceneId(int taskId)
{
    return INSTANCE(StringUtils)->stringToInt(getTaskAttribute(taskId, "scenesId"));
}

int TaskRule::getTaskTime(int taskId)
{
    return INSTANCE(StringUtils)->stringToInt(getTaskAttribute(taskId, "time"));
}

string TaskRule::getTaskName(int taskId)
{
    return getTaskAttribute(taskId, "name");
}

vector<int> TaskRule::getTaskCondition(int taskId)
{
    return INSTANCE(StringUtils)->getIntVectorFromString(getTaskAttribute(taskId, "condition"), "_");
}

int TaskRule::getTaskType(int taskId)
{
    return INSTANCE(StringUtils)->stringToInt(getTaskAttribute(taskId, "type"));
}

int TaskRule::getRandomTaskId(int sceneId)
{
    return INSTANCE(GameUtils)->getRandomFromVector(getTaskVector(sceneId));
}

vector<int> TaskRule::getTaskVector(int sceneId)
{
    vector<int> result;
    CCDictionary* mainDic = INSTANCE(BaseDataManager)->getXml(TaskXml);
    CCArray *array = mainDic->allKeys();
    for(int i=0;i<array->count();i++){
        string key = ((CCString *)array->objectAtIndex(i))->getCString();
        int _sceneId = INSTANCE(StringUtils)->stringToInt(((CCString *) ((CCDictionary *) mainDic->objectForKey(key))->objectForKey("scenesId"))->getCString());
        if(_sceneId == sceneId){
            result.push_back(INSTANCE(StringUtils)->stringToInt(key));
        }
    }
    return result;
}

CCDictionary* TaskRule::getTaskDic(int taskId)
{
    CCDictionary* mainDic = INSTANCE(BaseDataManager)->getXml(TaskXml);
    
    CCDictionary *subDic = (CCDictionary *) mainDic->objectForKey(CCString::createWithFormat("%d",taskId)->getCString());
    
    return subDic;
}

string TaskRule::getTaskAttribute(int taskId, const char *attributeName)
{
    return ((CCString *) getTaskDic(taskId)->objectForKey(attributeName))->getCString();
}