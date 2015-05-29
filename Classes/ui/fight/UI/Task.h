//
//  Task.h
//  threeKingdoms
//  Created by sma11case 14-2-19.
//
//

#ifndef __threeKingdoms__Task__
#define __threeKingdoms__Task__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

USING_NS_CC;
using namespace std;

#define NoticeUpdateTask "noticeUpdateTask"

enum TaskStatus
{
    TaskStatus_running,
    TaskStatus_finished,
    TaskStatus_end
};
class Task:public CCNode
{
public:
    static Task* create(int taskId);
    Task(int taskId);
    ~Task();
    
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    void initContent();
    
    CCSprite *bg;
    CCSprite *npc;
    CCSprite *goldIcon;
    CCLabelBMFont *name;
    CCLabelBMFont *numLabel;
    CCLabelBMFont *gold;
    CCLabelBMFont *timeLabel;
    
    
    int taskId;
    int npcId;
    int totleNum;
    int time;
    int type;
    int goldCount;
    
    void hideHandler();
    void btnHandler();
    
    bool isShow;
    
    string getTypeDesc();
    
    void updateInfo();
    void updateTime();
    
    TaskStatus taskStatus;
    void showReward();
    void showTimes();
    
    void removeHandler();
};

class TaskFacade:public CCObject
{
public:
    CLASS_INSTANCE(TaskFacade);
    bool init();
    
    void taskHandler();
    
    void startTask();
    void endTask();
    void addFinishNum(int npcId);
    
    int getCurrentFinishNum();
    
    Task* getTask();
    
    void closeTask();
private:
    int currentTaskId;
    int totleFinishNum;
    int currentFinishNum;
    int npcId;
    
    bool taskRunning;
    
    Task *task;
};
#endif /* defined(__threeKingdoms__Task__) */
