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
    HIT,
    DRAW_SWORD,
    SWORD_HIT,
    VICTORY,
    ROAR,
    MAX_SOUND_EFFECTS 
};

static const string MUSIC_SOUND_FILE = "sounds/mainMusic.ogg";
static const string BATTLE_MUSIC_SOUND_FILE = "sounds/battleMusic.xm";
static const string STEP_SOUND_FILE = "sounds/step.wav";
static const string MENU_BEEP_SOUND_FILE = "sounds/menuBeep.wav";
static const string HEAL_SOUND_FILE = "sounds/heal.wav";
static const string RUN_SOUND_FILE = "sounds/run.wav";
static const string NO_POTION_SOUND_FILE = "sounds/nopotion.wav";
static const string HIT_SOUND_FILE = "sounds/hit.wav";
static const string DRAW_SWORD_SOUND_FILE = "sounds/swordraw.wav";
static const string SWORD_HIT_SOUND_FILE = "sounds/steelsword.wav";
static const string VICTORY_SOUND_FILE = "sounds/victory.wav";
static const string ROAR_SOUND_FILE = "sounds/roar.wav";
static const string BOSS_MUSIC_SOUND_FILE = "sounds/bossMusic.ogg";

#endif
