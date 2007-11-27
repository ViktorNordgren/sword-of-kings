#ifndef _DEFINED_game_engine
#define _DEFINED_game_engine
#include <string>

/*
* GameState.h
*/

#include "character.h"
#include "common_game.h"

class GameState
{
    public:
        GameState();
        
        bool isConditionTrue(string cond);
        void performAction(string action);

    protected:
        bool sword_found;
        bool talked_to_geoffery;   
        
};

#endif
