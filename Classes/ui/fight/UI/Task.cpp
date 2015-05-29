//
//  Task.cpp
//  threeKingdoms
//
//  Created by .m on 14-2-19.
//
//

#include "Task.h"
#include "ModelRule.h"
#include "NPCRule.h"
#include "TaskRule.h"
#include "EventManager.h"
#include "ButtonUtils.h"
#include "StringUtils.h"
#include "SceneManager.h"
#include "UserData.h"
#include "MoneyLayer.h"
#include "GameUtils.h"
#include "FightManager.h"
#include "SystemConfigRule.h"
#include "TimeManager.h"
#include "AnimateManager.h"
Task* Task::create(int taskId)
{
    Task *task = new Task(taskId);
    if(task && task->init()){
        task->autorelease();
        return task;
    }else{
        delete task;
        task = NULL;
        return task;
    }
}

Task::Task(int taskId)
{
    this->taskId = taskId;
}

Task::~Task()
{
    bg->release();
}

bool Task::init()
{
    if(!CCNode::init()){
        return false;
    }
    initContent();
    taskStatus = TaskStatus_running;
    return true;
}

void Task::initContent()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/fightUI/task.plist");
    bg = CCSprite::createWithSpriteFrameName("task_bg.png");
//    bg->setAnchorPoint(ccp(0, 1));
    bg->retain();
    addChild(bg);
    bg->setPosition(ccp(bg->getContentSize().width/2, -bg->getContentSize().height/2));
    INSTANCE(EventManager)->addEventListener(bg, this, callfuncO_selector(Task::hideHandler));
    
    type = INSTANCE(TaskRule)->getTaskType(taskId);
    vector<int> condition = INSTANCE(TaskRule)->getTaskCondition(taskId);
    npcId = condition[0];
    totleNum = condition[1];
    time = INSTANCE(TaskRule)->getTaskTime(taskId);
    goldCount = INSTANCE(TaskRule)->getTaskReward(taskId);
    
    name = CCLabelBMFont::create(getTypeDesc().c_str(), "font/font_uiTitle.fnt");
    bg->addChild(name);
    name->setAnchorPoint(ccp(1, 0.5));
    name->setPosition(ccp(160, 160));
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile((INSTANCE(ModelRule)->getModelPath(npcId) +  INSTANCE(NPCRule)->getNpcFrameNameByNpcId(npcId, RoleStatusWalk) + ".plist").c_str());
    npc = CCSprite::createWithSpriteFrameName(INSTANCE(NPCRule)->getNpcFirstFrameNameByNpcId(npcId, RoleStatusWalk).c_str());
    npc->setAnchorPoint(INSTANCE(NPCRule)->getNpcAnchorPoint(npcId));
    bg->addChild(npc);
    npc->setScale(0.4);
    npc->setPosition(ccp(85, 85));
    
    
    
    CCControlButton *hideBtn = INSTANCE(ButtonUtils)->createButton("task_btn.png", CCSizeMake(65, 65), "");
    addChild(hideBtn,10);
    hideBtn->setPosition(ccp(10, -10));
    isShow = true;
    hideBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(Task::btnHandler), CCControlEventTouchUpInside);
    
    
    
    numLabel = CCLabelBMFont::create("0/0", "font/font_task.fnt");
    numLabel->setPosition(ccp(bg->getContentSize().width/2, 64));
    numLabel->setString(CCString::createWithFormat("0/%d",totleNum)->getCString());
    bg->addChild(numLabel);
    
    gold = CCLabelBMFont::create(INSTANCE(StringUtils)->intToString(INSTANCE(TaskRule)->getTaskReward(taskId)).c_str(), "font/font_task.fnt");
    gold->setPosition(ccp(bg->getContentSize().width/2, 40));
    bg->addChild(gold);
    gold->setAnchorPoint(ccp(1, 0.5));
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    goldIcon = CCSprite::createWithSpriteFrameName("common_money_1.png");
    goldIcon->setAnchorPoint(ccp(0, 0.5));
    bg->addChild(goldIcon);
    goldIcon->setPosition(ccp(bg->getContentSize().width/2 + 10, 40));
    goldIcon->setScale(0.6);
    
    timeLabel = CCLabelBMFont::create("00:00", "font/font_task.fnt");
    timeLabel->setPosition(ccp(bg->getContentSize().width/2, 16));
    bg->addChild(timeLabel);
    timeLabel->setString(INSTANCE(StringUtils)->dountDownToString(time * 1000).c_str());
    timeLabel->setColor(ccRED);
    
    getScheduler()->scheduleSelector(schedule_selector(Task::updateTime), this, 1.0f, false);
}

void Task::updateTime()
{
    time--;
    if(timeLabel){
        timeLabel->setString(INSTANCE(StringUtils)->dountDownToString(time * 1000).c_str());
    }
    
    if(time <= 0){
        INSTANCE(TaskFacade)->endTask();
        getScheduler()->unscheduleAllForTarget(this);
        taskStatus = TaskStatus_end;
        showTimes();
    }
    
}

void Task::hideHandler()
{
    if(taskStatus == TaskStatus_running){
        bg->removeFromParent();
        isShow = false;
    }
    
}

void Task::btnHandler()
{
    if(taskStatus == TaskStatus_running){
        if(isShow){
            hideHandler();
        }else{
            addChild(bg);
            isShow = true;
        }
    }
}

string Task::getTypeDesc()
{
    string result = "";
    switch (type) {
        case 1:
            result = "杀";
            break;
            
        default:
            break;
    }
    return result;
}

void Task::onEnter()
{
    CCNode::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Task::updateInfo), NoticeUpdateTask, NULL);
}

void Task::onExit()
{
    CCNode::onExit();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NoticeUpdateTask);
}

void Task::updateInfo()
{
    int current = INSTANCE(TaskFacade)->getCurrentFinishNum();
    numLabel->setString(CCString::createWithFormat("%d/%d",current,totleNum)->getCString());
    if(current == totleNum){
        getScheduler()->unscheduleAllForTarget(this);
        taskStatus = TaskStatus_finished;
        showReward();
        INSTANCE(TaskFacade)->endTask();
    }
}

void Task::showReward()
{
    if(!isShow){
        addChild(bg);
        isShow = true;
    }
    //播放动画
    numLabel->setColor(ccGREEN);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common/common.plist");
    npc->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("common_money_5.png"));
    npc->setScale(1);
    npc->setAnchorPoint(ccp(0.5, 0));
    CCOrbitCamera *orbit_1 = CCOrbitCamera::create(1, 1, 0, 0, 360, 0, 0);
    CCSequence *action = CCSequence::create(orbit_1,CCDelayTime::create(3.0),CCCallFunc::create(this, callfunc_selector(Task::showTimes)),NULL);
    bg->runAction(action);
    
    INSTANCE(UserData)->addTaskCount(1);
    INSTANCE(UserData)->setReceiveTaskTime(INSTANCE(TimeManager)->getSystemTimeM());
}

void Task::showTimes()
{
    if(!isShow){
        addChild(bg);
        isShow = true;
    }
    //播放动画
    numLabel->removeFromParent();
    goldIcon->removeFromParent();
    gold->removeFromParent();
    
    CCLabelTTF *label = CCLabelTTF::create();
    label->setFontSize(24);
    label->setColor(ccBLUE);
    label->setPosition(ccpAdd(timeLabel->getPosition(), ccp(0, 26)));
    timeLabel->removeFromParent();
    timeLabel = NULL;
    int taskCount = INSTANCE(SystemConfigRule)->getTaskCount()- INSTANCE(UserData)->getTaskCount();
    label->setString(CCString::createWithFormat("今日剩余%d次",taskCount)->getCString());
    bg->addChild(label);
    if(taskStatus == TaskStatus_finished){
        INSTANCE(MoneyLayerManager)->createMoney(goldCount, ccpSub(convertToWorldSpace(bg->getPosition()), INSTANCE(GameUtils)->getWindowsCenterPosition()));
        INSTANCE(UserData)->addCurrentMoney(goldCount);
        CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateMoney);
    }
    CCOrbitCamera *orbit_1 = CCOrbitCamera::create(1, 0.2, 0, 0, 360, 0, 0);
    CCSequence *action = CCSequence::create(orbit_1,CCDelayTime::create(3.0),CCCallFunc::create(this, callfunc_selector(Task::removeHandler)),NULL);
    bg->runAction(action);
}

void Task::removeHandler()
{
    INSTANCE(AnimateManager)->hideAnimate(this);
}

bool TaskFacade::init()
{
    taskRunning = false;
    return true;
}



void TaskFacade::startTask()
{
    if(INSTANCE(TimeManager)->isLaterDay(INSTANCE(UserData)->getReceiveTaskTime(), INSTANCE(TimeManager)->getSystemTimeM())){
        INSTANCE(UserData)->setTaskCount(0);
        CCLog("任务第二天，次数置0");
    }
    int taskCount = INSTANCE(UserData)->getTaskCount();
    CCLOG("次数:%d",taskCount);
    if(taskCount < INSTANCE(SystemConfigRule)->getTaskCount()){
        if(taskCount == 0){
            CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(TaskFacade::taskHandler), this, INSTANCE(SystemConfigRule)->getTaskTime(true), false);
        }else{
            CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(TaskFacade::taskHandler), this, INSTANCE(SystemConfigRule)->getTaskTime(false), false);
        }
    }else{
        CCLog("次数不够");
    }
}

void TaskFacade::taskHandler()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(TaskFacade::taskHandler),this);
    currentTaskId = INSTANCE(TaskRule)->getRandomTaskId(INSTANCE(UserData)->getCurrentSceneId());
    currentFinishNum = 0;
    vector<int> v = INSTANCE(TaskRule)->getTaskCondition(currentTaskId);
    npcId =v[0];
    totleFinishNum =v[1];
    
    taskRunning = true;
    
    task = Task::create(currentTaskId);
    INSTANCE(SceneManager)->addToCurrentScene(task, zOrder_ui);
    INSTANCE(AnimateManager)->showAnimate(task);
    task->setPosition(ccp(30, 490));
}

void TaskFacade::endTask()
{
    if(taskRunning == false){
        return;
    }
    taskRunning = false;
    task = NULL;
    startTask();
}

int TaskFacade::getCurrentFinishNum()
{
    return currentFinishNum;
}

void TaskFacade::addFinishNum(int npcId)
{
    if(taskRunning && this->npcId == npcId){
        currentFinishNum++;
        CCNotificationCenter::sharedNotificationCenter()->postNotification(NoticeUpdateTask);
    }
}

Task* TaskFacade::getTask()
{
    return task;
}

void TaskFacade::closeTask()
{
    if(task){
        task->removeFromParent();
    }
}