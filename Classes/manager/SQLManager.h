//
//  SQLManager.h
//  threeKingdoms
//  Created by sma11case 14-1-3.
//
//

#ifndef __threeKingdoms__SQLManager__
#define __threeKingdoms__SQLManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "sqlite3.h"

using namespace std;
USING_NS_CC;

#define DB_NAME "threeKingdomsDb.db"
#define TABLE_NAME "roleTable"

#define FieldName_Gold "gold"
#define FieldName_Integral "integral"
#define FieldName_KillBossNum "killBossNum"
#define FieldName_TotleCost "totleCost"
#define FieldName_TotleGain "totleGain"
#define FieldName_TitleLevel "titleLevel"
#define FieldName_UpgradeIntegral "upgradeIntegral"
#define FieldName_LastReceiveLoginRewardTime "lastReceiveLoginRewardTime"

#define FieldName_ContinuousLoginDay "continuousLoginDay"
#define FieldName_SkillNum "skillNum"
#define FieldName_vip "vip"
#define FieldName_Roles "roles"

#define FieldName_FinishChapterTimes "finishChapterTimes"
#define FieldName_ChapterStatus "chapterStatus"
#define FieldName_WheelTimes "wheelTimes"

#define FieldName_PotGold "potGold"

#define FieldName_LastReceiveOnlineRewardTime "lastReceiveOnlineRewardTime"
#define FieldName_ReceiveOnlineRewardTimes "receiveOnlineRewardTimes"

#define FieldName_taskCount "taskCount"
#define FieldName_receiveTaskTime "receiveTaskTime"
#define FieldName_anger "anger"

#define FieldName_loginCount "loginCount"

class SQLManager:public CCObject
{
public:
    SQLManager();
    ~SQLManager();
    CLASS_INSTANCE(SQLManager);
    bool init();
    
    void setSelectResult(const char* result);
    
    void save(const char* name,int value);
    void save(const char* name,int64_t value);
    void save(const char* name,const char* value);
    
    const char* getValue(const char* name);
    int getValueInt(const char* name);
private:
    sqlite3 *pDB;
    
    void createDB();
    
    void createRoleTable();
    
    char* selectRestul;
    
    void createField(const char* name);
    
    void initFieldInfo();
    //字段的初始值
    CCDictionary *fieldNameDic;
    //字段是否存在
    bool fieldExisted(string fieldName);
    
};

int isExisted( void * para, int n_column, char ** column_value, char ** column_name);
int loadRecord( void * para, int n_column, char ** column_value, char ** column_name );

#endif /* defined(__threeKingdoms__SQLManager__) */
