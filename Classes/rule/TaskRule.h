//
//  TaskRule.h
//  threeKingdoms
//  Created by sma11case on 14-2-19.
//
//

#ifndef __threeKingdoms__TaskRule__
#define __threeKingdoms__TaskRule__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

class TaskRule:public CCObject
{
public:
    CLASS_INSTANCE(TaskRule);
    bool init();
    
    //获取任务名
    string getTaskName(int taskId);
    //获取任务时间
    int getTaskTime(int taskId);
    //获取任务条件
    vector<int> getTaskCondition(int taskId);
    //获取任务场景
    int getTaskSceneId(int taskId);
    //获取任务奖励
    int getTaskReward(int taskId);
    //获取任务类型
    int getTaskType(int taskId);
    
    //通过场景随机获取任务
    int getRandomTaskId(int sceneId);
    
    //通过场景获取任务数组
    vector<int> getTaskVector(int sceneId);
private:
    CCDictionary *getTaskDic(int taskId);
    string getTaskAttribute(int taskId, const char *attributeName);
};

#endif /* defined(__threeKingdoms__TaskRule__) */
