/*
* GameState.cpp
*/

#include "gamestate.h"


/*
* Class GameState
*/

GameState::GameState()
{
    sword_found = false;
    talked_to_geoffery = false;
    
}

/*
* Will return true if the passed in condition has been met.
*/
bool GameState::isConditionTrue(string cond)
{
    if(cond.compare(DEFAULT) == 0)
    {
        return true;
    }
    if(cond.compare(SWORD_FOUND) == 0)
    {
        return sword_found;
    }
    if(cond.compare(TALKED_TO_GEOFFERY) == 0)
    {
        return talked_to_geoffery;
    }
}

/*
* This will perform the action specified.
*/
void GameState::performAction(string action)
{
    if(action.compare(NOTHING) == 0)
    {
        return;
    }
    if(action.compare(GET_SWORD) == 0)
    {
        sword_found = true;
    }
}
