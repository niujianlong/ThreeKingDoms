//
//  ResourceManager.cpp
//  threeKingdoms
//  Created by sma11case on 14-1-13.
//
//

#include "ResourceManager.h"
#include "NPCRule.h"
#include "RoleRule.h"
#include "ModelRule.h"

bool ResourceManager::init()
{
    return true;
}

vector<string> ResourceManager::getNpcResourceImg(int npcId)
{
    vector<string> result;
    string path = INSTANCE(NPCRule)->getNpcImgPath(npcId);
    
    vector<RoleStatus> status;
    status.push_back(RoleStatusDie);
    status.push_back(RoleStatusWalk);
    status.push_back(RoleStatusHurt);
    
    for(int i=0;i<status.size();i++){
        string img = INSTANCE(NPCRule)->getNpcFrameNameByNpcId(npcId, status[i],true);
        result.push_back(path + img);
    }
    
    int skillId = INSTANCE(NPCRule)->getNpcSkillId(npcId);
    if(skillId != 0){
        string path = INSTANCE(ModelRule)->getModelPath(skillId);
        string img = INSTANCE(ModelRule)->getSkillHitFrameName(skillId,true);
        result.push_back(path + img);
    }
    
    return result;
}

vector<string> ResourceManager::getRoleResourceImg(int roleId)
{
    vector<string> result;
    string path = INSTANCE(RoleRule)->getRoleImgPath(roleId);
    
    vector<RoleStatus> status;
    status.push_back(RoleStatusAttack_1);
    status.push_back(RoleStatusAttack_2);
    status.push_back(RoleStatusAttack_3);
    status.push_back(RoleStatusAttack_4);
    status.push_back(RoleStatusAttack_5);
//    status.push_back(RoleStatusAttackEffect);
    status.push_back(RoleStatusRun);
    status.push_back(RoleStatusSkill);
    status.push_back(RoleStatusSkillEffect);
    status.push_back(RoleStatusStand);
    
    for(int i=0;i<status.size();i++){
        string img = INSTANCE(RoleRule)->getRoleFrameNameByRoleId(roleId, status[i],true);
        result.push_back(path + img);
    }
    
    int skillId = INSTANCE(RoleRule)->getRoleSkillId(roleId);
    path = INSTANCE(ModelRule)->getModelPath(skillId);
    string img = INSTANCE(ModelRule)->getSkillHitFrameName(skillId,true);
    result.push_back(path + img);
    
    return result;
}