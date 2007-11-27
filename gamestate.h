#ifndef _DEFINED_game_state
#define _DEFINED_game_state
#include <string>

/*
* GameState.h
*/

#include "character.h"
#include "common_game.h"

class GameState
{
    public:
        GameState(void*);
        
        bool isConditionTrue(string cond);
        void performAction(string action);

    protected:
        bool sword_found;
        bool talked_to_geoffery;  
        void * engine;
        
};

#endif
