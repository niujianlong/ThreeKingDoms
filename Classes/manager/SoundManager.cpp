//
//  SoundManager.cpp
//  threeKingdoms
//
//  Created by .m on 13-12-25.
//
//

#include "SoundManager.h"
#include "SimpleAudioEngine.h"
#include "GameSet.h"
#include "GameUtils.h"

bool SoundManager::init()
{
    float musicVolume = CCUserDefault::sharedUserDefault()->getFloatForKey(GameSet_musicVolume, 0.5);
    float soundVolume = CCUserDefault::sharedUserDefault()->getFloatForKey(GameSet_soundVolume, 0.5);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(musicVolume);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(soundVolume);
    return true;
}

void SoundManager::stopMusic()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void SoundManager::playFightAttack()
{
    playFightSound(Sound_attack);
}

void SoundManager::playFightHurt()
{
    playFightSound(Sound_hurt);
}

void SoundManager::playFightDead()
{
    playFightSound(Sound_dead);
}

void SoundManager::playFightSkill(int skillId)
{
    playFightSound(Sound_skill,skillId);
}

void SoundManager::playGainMoney()
{
    playFightSound(Sound_gainMoney);
}

void SoundManager::playFightMusic(int type)
{
    playMusic(Music_fightting,type);
}

void SoundManager::playChapterMusic()
{
    playMusic(Music_chapter);
}

void SoundManager::playBossMusic(int type)
{
    playMusic(Music_boss,type);
}

void SoundManager::playTroopsMusic(int type)
{
    playMusic(Music_troops,type);
}

void SoundManager::playCreateCharacter()
{
    playMusic(Music_createCharacter);
}

void SoundManager::playSound(GameSound sound)
{
    string path;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(path.c_str(), true);
}

void SoundManager::playFightSound(GameFightSound sound,int param)
{
    string path;
    switch (sound) {
        case Sound_attack:
            path = "sound/sound_fight_attack.mp3";
            break;
        case Sound_hurt:
            path = "sound/sound_fight_hurt.mp3";
            break;
        case Sound_dead:
            path = "sound/sound_fight_male_dead.wav";
            break;
        case Sound_skill:
            path = CCString::createWithFormat("sound/sound_skill_%d.mp3",param)->getCString();
            break;
        case Sound_gainMoney:
            path = "sound/sound_money.mp3";
            break;
        default:
            break;
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(path.c_str());
}

void SoundManager::playMusic(GameMusic music,int param)
{
    string path;
    switch (music) {
        case Music_fightting:
            path = CCString::createWithFormat("sound/music_fight%d.mp3",param)->getCString();
            break;
        case Music_chapter:
            path = "sound/music_chapter.mp3";
            break;
        case Music_createCharacter:
            path = "sound/music_createCharacter.mp3";
            break;
        case Music_boss:
            path = CCString::createWithFormat("sound/music_boss%d.mp3",param)->getCString();
            break;
        case Music_troops:
            path = CCString::createWithFormat("sound/music_troops%d.mp3",param)->getCString();
            break;
        default:
            break;
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(path.c_str(), true);
}

