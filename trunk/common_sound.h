#ifndef _DEFINED_common_sound
#define _DEFINED_common_sound
#include <string>

using namespace std;

enum SoundEffect
{
    STEP,
    MAX_SOUND_EFFECTS 
};

static const string MUSIC_SOUND_FILE = "sounds/mainMusic.ogg";
static const string STEP_SOUND_FILE = "sounds/step.wav";

#endif
