//
//  ParticleManager.cpp
//  threeKingdoms
//
//  Created by .m on 14-1-2.
//
//

#include "ParticleManager.h"

bool ParticleManager::init()
{
    return true;
}

//CCParticleSystem * ParticleManager::getMovingParticle()
//{
//    CCParticleSystem* particle = CCParticleGalaxy::create();
//    particle->setStartSize(50);
//    particle->setEndSize(10);
//    particle->setLife(0.7);
//    particle->setStartColor(ccc4f(76, 155, 255, 10));
//    particle->setStartColorVar(ccc4f(255, 255, 255, 10));
//    particle->setEndColor(ccc4f(76, 155, 255, 10));
//    particle->setEndColorVar(ccc4f(76, 155, 255, 10));
//    particle->setStartSpin(0);
//    particle->setEndSpin(0);
//    return particle;
//}

CCParticleSystem *ParticleManager::getParticleByName(const char *name)
{
    string path = "particleFile/";
    path.append(name);
    CCParticleSystem* particle = CCParticleSystemQuad::create(path.c_str());
    return particle;
}