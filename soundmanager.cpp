/*
* SoundManager.cpp
*/

#include "soundmanager.h"

/*
* Class SoundManager
*/

/*
* Default constructor
*/

SoundManager::SoundManager()
{
    
    if(SDL_Init(SDL_INIT_AUDIO)==-1)
	{
	    printf("Error initializing audio\n");
	}
	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0)
    {
         printf("Warning: Couldn't set 44100 Hz 16-bit audio\n- Reason: %s\n", SDL_GetError());
    }
    
    music = Mix_LoadMUS(MUSIC_SOUND_FILE.c_str());
    battleMusic = Mix_LoadMUS(BATTLE_MUSIC_SOUND_FILE.c_str());
    soundEffects.push_back(Mix_LoadWAV(STEP_SOUND_FILE.c_str()));
    soundEffects.push_back(Mix_LoadWAV(MENU_BEEP_SOUND_FILE.c_str()));
    soundEffects.push_back(Mix_LoadWAV(HEAL_SOUND_FILE.c_str()));
    soundEffects.push_back(Mix_LoadWAV(RUN_SOUND_FILE.c_str()));
     soundEffects.push_back(Mix_LoadWAV(NO_POTION_SOUND_FILE.c_str()));
    
    
}

SoundManager::~SoundManager()
{
    Mix_FreeMusic(music);
    Mix_FreeMusic(battleMusic);
    for(int i = 0; i < MAX_SOUND_EFFECTS; i++)
    {
        Mix_FreeChunk(soundEffects[i]);
    }
}

void SoundManager::playMusic()
{
    Mix_HaltMusic();
    Mix_PlayMusic(music, -1);
}

void SoundManager::playBattleMusic()
{
    Mix_HaltMusic();
    Mix_PlayMusic(battleMusic, -1);
}

void SoundManager::stopMusic()
{
    Mix_HaltMusic();
}

void SoundManager::playSound(SoundEffect s)
{
    Mix_PlayChannel(-1, soundEffects[s], 0);
}
