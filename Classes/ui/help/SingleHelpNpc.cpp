//
//  SingleHelpNpc.cpp
//  threeKingdoms
//
//  Created by .m on 14-2-13.
//
//

#include "SingleHelpNpc.h"
#include "NPCRule.h"
#include "ModelRule.h"
#include "RoleRule.h"
#include "SkillRule.h"

SingleHelpNpc* SingleHelpNpc::create(int npcId,bool isRole)
{
    SingleHelpNpc *npc = new SingleHelpNpc(npcId,isRole);
    if(npc && npc->init()){
        npc->autorelease();
        return npc;
    }else{
        delete npc;
        npc = NULL;
        return NULL;
    }
}

SingleHelpNpc::SingleHelpNpc(int npcId,bool isRole)
{
    this->npcId = npcId;
    this->isRole = isRole;
}

SingleHelpNpc::~SingleHelpNpc()
{
    if(isRole){
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile((INSTANCE(RoleRule)->getRoleImgPath(npcId) +  INSTANCE(RoleRule)->getRoleFrameNameByRoleId(npcId, RoleStatusStand) + ".plist").c_str());
    }else{
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile((INSTANCE(NPCRule)->getNpcImgPath(npcId) +  INSTANCE(NPCRule)->getNpcFrameNameByNpcId(npcId, RoleStatusWalk) + ".plist").c_str());
    }
    
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

bool SingleHelpNpc::init()
{
    if(!CCNode::init()){
        return false;
    }
    
    initContent();
    return true;
}

void SingleHelpNpc::initContent()
{
    CCSprite *npc;
    if(isRole){
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile((INSTANCE(RoleRule)->getRoleImgPath(npcId) +  INSTANCE(RoleRule)->getRoleFrameNameByRoleId(npcId, RoleStatusStand) + ".plist").c_str());
        npc = CCSprite::createWithSpriteFrameName(INSTANCE(RoleRule)->getRoleFirstFrameNameByRoleId(npcId, RoleStatusStand).c_str());
        npc->setAnchorPoint(INSTANCE(RoleRule)->getRoleAnchorPoint(npcId));
    }else{
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile((INSTANCE(NPCRule)->getNpcImgPath(npcId) +  INSTANCE(NPCRule)->getNpcFrameNameByNpcId(npcId, RoleStatusWalk) + ".plist").c_str());
        npc = CCSprite::createWithSpriteFrameName(INSTANCE(NPCRule)->getNpcFirstFrameNameByNpcId(npcId, RoleStatusWalk).c_str());
        npc->setAnchorPoint(INSTANCE(NPCRule)->getNpcAnchorPoint(npcId));
    }
    
    addChild(npc);
    npc->setPosition(ccp(0, 10));
    
    CCScale9Sprite *infoBg = CCScale9Sprite::create("common/common_scale_1.png");
    infoBg->setPreferredSize(CCSizeMake(210, 140));
    infoBg->setAnchorPoint(ccp(0.5, 1));
    addChild(infoBg);
    
    CCLabelTTF* name = CCLabelTTF::create();
    name->setDimensions(CCSizeMake(200, 24));
    name->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    name->setHorizontalAlignment(kCCTextAlignmentLeft);
    infoBg->addChild(name);
    name->setPosition(ccp(105, 120));
    
    name->setColor(ccRED);
    name->setFontSize(16);
    
    CCLabelTTF* integral = CCLabelTTF::create();
    integral->setDimensions(CCSizeMake(200, 24));
    integral->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    integral->setHorizontalAlignment(kCCTextAlignmentLeft);
    infoBg->addChild(integral);
    integral->setPosition(ccp(105, 100));
    
    integral->setColor(ccBLACK);
    integral->setFontSize(16);
    
    CCLabelTTF *desc = CCLabelTTF::create();
    desc->setDimensions(CCSizeMake(200, 100));
    desc->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    desc->setHorizontalAlignment(kCCTextAlignmentLeft);
    infoBg->addChild(desc);
    desc->setPosition(ccp(105, 40));
    
    desc->setColor(ccBLACK);
    desc->setFontSize(16);
    
    if(isRole){
        name->setString(INSTANCE(RoleRule)->getRoleName(npcId).c_str());
        integral->setString(CCString::createWithFormat("技能：%s",INSTANCE(SkillRule)->getSkillName(INSTANCE(RoleRule)->getRoleSkillId(npcId)).c_str())->getCString());
        desc->setString(("特征：" + INSTANCE(RoleRule)->getRoleDesc(npcId)).c_str());
        
    }else{
        name->setString(INSTANCE(NPCRule)->getNpcName(npcId).c_str());
        integral->setString(CCString::createWithFormat("分值：%d",INSTANCE(NPCRule)->getNpcIntegral(npcId))->getCString());
        desc->setString(("特征：" + INSTANCE(NPCRule)->getNpcDesc(npcId)).c_str());
    }
}