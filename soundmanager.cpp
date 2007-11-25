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
    soundEffects.push_back(Mix_LoadWAV(STEP_SOUND_FILE.c_str()));
    
    
}

SoundManager::~SoundManager()
{
    Mix_FreeMusic(music);
    for(int i = 0; i < MAX_SOUND_EFFECTS; i++)
    {
        Mix_FreeChunk(soundEffects[i]);
    }
}

void SoundManager::playMusic()
{
    Mix_PlayMusic(music, 0);
}

void SoundManager::stopMusic()
{
    Mix_HaltMusic();
}

void SoundManager::playSound(SoundEffect s)
{
    Mix_PlayChannel(-1, soundEffects[s], 0);
}