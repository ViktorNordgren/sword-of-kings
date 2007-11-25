#ifndef _DEFINED_common_sound
#define _DEFINED_common_sound
#include <string>

using namespace std;

enum SoundEffect
{
    STEP,
    MENUBEEP,
    HEAL_SOUND,
    RUN_SOUND,
    NO_POTION,
    MAX_SOUND_EFFECTS 
};

static const string MUSIC_SOUND_FILE = "sounds/mainMusic.ogg";
static const string BATTLE_MUSIC_SOUND_FILE = "sounds/battleMusic.xm";
static const string STEP_SOUND_FILE = "sounds/step.wav";
static const string MENU_BEEP_SOUND_FILE = "sounds/menuBeep.wav";
static const string HEAL_SOUND_FILE = "sounds/heal.wav";
static const string RUN_SOUND_FILE = "sounds/run.wav";
static const string NO_POTION_SOUND_FILE = "sounds/nopotion.wav";

#endif
