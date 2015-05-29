//
//  SoundManager.h
//  threeKingdoms
//  Created by sma11case on 13-12-25.
//
//

#ifndef __threeKingdoms__SoundManager__
#define __threeKingdoms__SoundManager__

#include <iostream>
#include "cocos2d.h"
#include "GameCommon.h"

using namespace std;
USING_NS_CC;

enum GameSound{
    
};

enum GameFightSound{
    Sound_attack,
    Sound_hurt,
    Sound_dead,
    Sound_skill,
    Sound_gainMoney,
};

enum GameMusic{
    Music_fightting,
    Music_chapter,
    Music_createCharacter,
    Music_troops,
    Music_boss,
};

class SoundManager:public CCObject
{
public:
    CLASS_INSTANCE(SoundManager);
    bool init();
    
    void playFightAttack();
    void playFightHurt();
    void playFightDead();
    void playFightSkill(int skillId);
    
    void playFightMusic(int type);
    
    void playChapterMusic();
    
    void stopMusic();
    
    void playGainMoney();
    
    void playBossMusic(int type);
    
    void playTroopsMusic(int type);
    
    void playCreateCharacter();
    
private:
    void playSound(GameSound sound);
    void playFightSound(GameFightSound sound,int param = 0);
    
    void playMusic(GameMusic music,int param = 0);
};

#endif /* defined(__threeKingdoms__SoundManager__) */
