/*
* SoundManager.h
*/
#ifndef _DEFINED_soundmanager
#define _DEFINED_soundmanager
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include "SDL/SDL_mixer.h"
#include "common_sound.h"
#include <vector>



class SoundManager
{
    public:
        
        SoundManager();
        // Default destructor
        ~SoundManager();
        void playMusic();
        void playBattleMusic();
        void stopMusic();
        void playSound(SoundEffect s);
        
    private:
        Mix_Music* music;
        Mix_Music* battleMusic;
        vector<Mix_Chunk*> soundEffects;
};

#endif
    
    
