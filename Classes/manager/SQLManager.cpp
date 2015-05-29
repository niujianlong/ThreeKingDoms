//
//  SQLManager.cpp
//  threeKingdoms
//  Created by sma11case 14-1-3.
//
//

#include "SQLManager.h"
#include "StringUtils.h"
#include "SystemConfigRule.h"
#include "TimeManager.h"
#include "RoleRule.h"

SQLManager::SQLManager()
{
    
}

SQLManager::~SQLManager()
{
    sqlite3_close(pDB);
    fieldNameDic->release();
}

bool SQLManager::init()
{
    initFieldInfo();
    pDB = NULL;
    createDB();
    return true;
}

void SQLManager::initFieldInfo()
{
    fieldNameDic = CCDictionary::create();
    fieldNameDic->retain();
    
    fieldNameDic->setObject(CCString::createWithFormat("%d",INSTANCE(SystemConfigRule)->getInitGold()), FieldName_Gold);
    fieldNameDic->setObject(CCString::createWithFormat("%d",0), FieldName_Integral);
    fieldNameDic->setObject(CCString::createWithFormat("%d",0), FieldName_KillBossNum);
    fieldNameDic->setObject(CCString::createWithFormat("%d",0), FieldName_TotleCost);
    fieldNameDic->setObject(CCString::createWithFormat("%d",0), FieldName_TotleGain);
    fieldNameDic->setObject(CCString::createWithFormat("%d",1), FieldName_TitleLevel);
    fieldNameDic->setObject(CCString::createWithFormat("%d",0), FieldName_UpgradeIntegral);
    fieldNameDic->setObject(CCString::createWithFormat("%lld",INSTANCE(TimeManager)->getSystemTimeM()), FieldName_LastReceiveLoginRewardTime);
    
    fieldNameDic->setObject(CCString::createWithFormat("%d",0), FieldName_ContinuousLoginDay);
    fieldNameDic->setObject(CCString::createWithFormat("%d",0), FieldName_SkillNum);
    fieldNameDic->setObject(CCString::createWithFormat("%d",0), FieldName_vip);
    fieldNameDic->setObject(CCString::createWithFormat(INSTANCE(RoleRule)->getFreeRoles().c_str()), FieldName_Roles);
    fieldNameDic->setObject(CCString::createWithFormat("%d",1), FieldName_FinishChapterTimes);
    fieldNameDic->setObject(CCString::createWithFormat(""), FieldName_ChapterStatus);
    fieldNameDic->setObject(CCString::createWithFormat("%d",0), FieldName_WheelTimes);
    fieldNameDic->setObject(CCString::createWithFormat("%d",0), FieldName_PotGold);
    
    fieldNameDic->setObject(CCString::createWithFormat("%lld",int64_t(0)), FieldName_LastReceiveOnlineRewardTime);
    fieldNameDic->setObject(CCString::createWithFormat("d",0), FieldName_ReceiveOnlineRewardTimes);
    
    fieldNameDic->setObject(CCString::createWithFormat("d",0), FieldName_taskCount);
    fieldNameDic->setObject(CCString::createWithFormat("%lld",int64_t(0)), FieldName_receiveTaskTime);
    
    fieldNameDic->setObject(CCString::createWithFormat("d",0), FieldName_anger);
    fieldNameDic->setObject(CCString::createWithFormat("d",0), FieldName_loginCount);
}

void SQLManager::createDB()
{
    int result;//sqlite3_exec返回值
    
    string path = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
    result = sqlite3_open(path.c_str(), &pDB);
    
    if( result != SQLITE_OK )
    {
        CCLog( "打开数据库失败，错误码:%d" , result );
    }else{
        createRoleTable();
    }
    
    CCArray *fieldNameArray = fieldNameDic->allKeys();
    
    for(int i=0;i<fieldNameArray->count();i++){
        string fieldName = ((CCString *)fieldNameArray->objectAtIndex(i))->getCString();
        if(!fieldExisted(fieldName)){
            char * errMsg = NULL;//错误信息
            string sqlstr;
            if(fieldName == FieldName_LastReceiveLoginRewardTime){
                sqlstr = string("ALTER TABLE ")+TABLE_NAME+" ADD "+fieldName+" bigint";
                sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
                save(fieldName.c_str(), INSTANCE(StringUtils)->stringToInt64(((CCString *) fieldNameDic->objectForKey(fieldName))->getCString()));
            }else if(fieldName == FieldName_Roles){
                sqlstr = string("ALTER TABLE ")+TABLE_NAME+" ADD "+fieldName+" char(255)";
                sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
                save(fieldName.c_str(), ((CCString *) fieldNameDic->objectForKey(fieldName))->getCString());
            }else{
                sqlstr = string("ALTER TABLE ")+TABLE_NAME+" ADD "+fieldName+" int";
                sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
                save(fieldName.c_str(), INSTANCE(StringUtils)->stringToInt(((CCString *) fieldNameDic->objectForKey(fieldName))->getCString()));
            }
        }
    }
}

void SQLManager::createRoleTable()
{
    bool isExisted_;
    char * errMsg = NULL;//错误信息
    int result;//sqlite3_exec返回值
    
    std::string sqlstr = string("select count(type) from sqlite_master where type='table' and name='")+ TABLE_NAME +"'";
    sqlite3_exec( pDB, sqlstr.c_str() , isExisted, &isExisted_, &errMsg );
    
    if(!isExisted_){
        
//        CCString *temp = CCString::createWithFormat("create table %s ( ID integer primary key autoincrement, %s int,%s int,%s int,%s int,%s int,%s int,%s int,%s bigint,%s int,%s int)",TABLE_NAME,FieldName_Gold,FieldName_Integral,FieldName_KillBossNum,FieldName_TotleCost,FieldName_TotleGain,FieldName_TitleLevel,FieldName_UpgradeIntegral,FieldName_LastReceiveLoginRewardTime,FieldName_ContinuousLoginDay,FieldName_SkillNum);
        
        CCString *temp = CCString::createWithFormat("create table %s ( ID integer primary key autoincrement)",TABLE_NAME);
        
        sqlstr = temp->getCString();
        result=sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
        if( result != SQLITE_OK ){
            CCLog( "创建表失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
        }
    }
    
    sqlstr=string("select count(*) from ") + TABLE_NAME + " where ID = 1";
    sqlite3_exec( pDB, sqlstr.c_str() , isExisted, &isExisted_, &errMsg );
    if(!isExisted_){
        
//        CCString *temp = CCString::createWithFormat(" insert into %s (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s) values (%d,%d,%d,%d,%d,%d,%d,%lld,%d,%d)",TABLE_NAME,FieldName_Gold,FieldName_Integral,FieldName_KillBossNum,FieldName_TotleCost,FieldName_TotleGain,FieldName_TitleLevel,FieldName_UpgradeIntegral,FieldName_LastReceiveLoginRewardTime,FieldName_ContinuousLoginDay,FieldName_SkillNum,INSTANCE(SystemConfigRule)->getInitGold(),0,0,0,0,1,0,INSTANCE(TimeManager)->getSystemTimeM(),0,0);
        CCString *temp = CCString::createWithFormat(" insert into %s (id) values (1)",TABLE_NAME);
        sqlstr = temp->getCString();
        result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
        if(result != SQLITE_OK )
            CCLog( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
    }
}

int isExisted( void * para, int n_column, char ** column_value, char ** column_name )
{
    bool *isExisted_=(bool*)para;
    *isExisted_=(**column_value)!='0';
    return 0;
}

void SQLManager::save(const char* name, int value)
{
//    createField(name);
    char * errMsg = NULL;//错误信息
    CCString *string = CCString::createWithFormat("update %s set %s=%d where ID = 1",TABLE_NAME,name,value);
    sqlite3_exec( pDB, string->getCString() , NULL, NULL, &errMsg );
}

void SQLManager::save(const char* name, int64_t value)
{
    char * errMsg = NULL;//错误信息
    CCString *string = CCString::createWithFormat("update %s set %s=%lld where ID = 1",TABLE_NAME,name,value);
    sqlite3_exec( pDB, string->getCString() , NULL, NULL, &errMsg );
}

void SQLManager::save(const char* name, const char* value)
{
//    createField(name);
    char * errMsg = NULL;//错误信息
    CCString *string = CCString::createWithFormat("update %s set %s='%s' where ID = 1",TABLE_NAME,name,value);
    sqlite3_exec( pDB, string->getCString() , NULL, NULL, &errMsg );
}

const char* SQLManager::getValue(const char *name)
{
    char * errMsg = NULL;//错误信息
    string sqlstr=string("select ") + name +" from " + TABLE_NAME + " where ID=1";
    sqlite3_exec( pDB, sqlstr.c_str() ,loadRecord,NULL, &errMsg );
    return selectRestul;
}

int SQLManager::getValueInt(const char *name)
{
    char * errMsg = NULL;//错误信息
    string sqlstr=string("select ") + name +" from " + TABLE_NAME + " where ID=1";
    sqlite3_exec( pDB, sqlstr.c_str() ,loadRecord,NULL, &errMsg );
    return atoi(selectRestul);
}

void SQLManager::setSelectResult(const char *result)
{
    char temp[1024];
    strcpy(temp, result);
    selectRestul = temp;
}

int loadRecord( void * para, int n_column, char ** column_value, char ** column_name )
{
    CCLog("name = %s,value = %s",column_name[0],column_value[0]);
    INSTANCE(SQLManager)->setSelectResult(column_value[0]);
    return 0;
}

bool SQLManager::fieldExisted(string fieldName)
{
    char * errMsg = NULL;//错误信息
    std::string sqlstr = string("select ") + fieldName + " from "+TABLE_NAME;
    int result = sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
    if(result == SQLITE_ERROR){
        return false;
    }
    return true;
}

//void SQLManager::createField(const char *name)
//{
//    char * errMsg = NULL;//错误信息
//    bool isExisted_;
//    string sqlstr=string("select "+string(name)+" from ") + TABLE_NAME;
//    sqlite3_exec( pDB, sqlstr.c_str() , isExisted, &isExisted_, &errMsg );
//    if(!isExisted_){
//        sqlstr = string("ALTER TABLE ")+TABLE_NAME+" ADD "+string(name)+" bigint";
//        sqlite3_exec( pDB, sqlstr.c_str() , NULL, NULL, &errMsg );
//    }
//}

