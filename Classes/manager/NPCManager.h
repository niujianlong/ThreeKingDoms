//
//  NPCManager.h
//  threeKingdoms
//
//  Created by .m on 13-12-25.
//
//

#ifndef __threeKingdoms__NPCManager__
#define __threeKingdoms__NPCManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"
#include "NPC.h"

using namespace std;
USING_NS_CC;

class NPCManager:public CCObject
{
public:
    CLASS_INSTANCE(NPCManager);
    bool init();
    
    void createTroopsNPC(int npcId,int formationIndex,RoleDirection direction,int speed,TroopsType troopsType);
    
    void createRandomNpc(int npcId,bool isBoss = false);
    
    void removeNPC(NPC *npc);
    
    void keepAllNpcStop(int second);
    void allNpcStopComplete();
    
    CCArray *getAllNpc();
    
    void removeAllNpc();
    
    void startUpdate();
    void stopUpdate();
    
    void createGuideNpc_1();
    void createGuideNpc_2();
    
    void setStop(bool param);
private:
    CCArray *npcArray;
    
    CCPoint getNPCPosition(int index,RoleDirection direction);
    
    void updateNpcInfo();
    
    void stopHandler();
    
    bool isStop;
    
    void removeNpcHandler();
    CCArray *tempNpcArray;
};

#endif /* defined(__threeKingdoms__NPCManager__) */
