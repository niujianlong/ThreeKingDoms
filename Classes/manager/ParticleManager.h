//
//  ParticleManager.h
//  threeKingdoms
//  Created by sma11case on 14-1-2.
//
//

#ifndef __threeKingdoms__ParticleManager__
#define __threeKingdoms__ParticleManager__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class ParticleManager
{
public:
    CLASS_INSTANCE(ParticleManager);
    bool init();
    
//    CCParticleSystem *getMovingParticle();
    CCParticleSystem *getParticleByName(const char *name);
};

#endif /* defined(__threeKingdoms__ParticleManager__) */
