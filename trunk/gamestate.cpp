/*
* GameState.cpp
*/

#include "engine.h"
#include "gamestate.h"

/*
* Class GameState
*/

GameState::GameState(void* eng)
{
    sword_found = false;
    talked_to_geoffery = false;
    engine = eng;
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
    if(cond.compare(HAS_SWORD_OF_KINGS) == 0)
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
    if(action.compare(START_GAME) == 0)
    {
        ((Engine*)engine)->displayDialog(GEOFFREY_DIALOG_1, CORNELIUS_DIALOG_1);
    }
    if(action.compare(CORNELIUS_DIALOG_1) == 0)
    {
        ((Engine*)engine)->displayDialog(CORNELIUS_DIALOG_1, GEOFFREY_DIALOG_2);
    }
    if(action.compare(GEOFFREY_DIALOG_2) == 0)
    {
        ((Engine*)engine)->displayDialog(GEOFFREY_DIALOG_2, LANCE_DIALOG_1);
    }
    if(action.compare(LANCE_DIALOG_1) == 0)
    {
        ((Engine*)engine)->displayDialog(LANCE_DIALOG_1, NOTHING);
    }
    if(action.compare(PICKED_UP_SWORD_OF_KINGS) == 0)
    {
        sword_found = true;
        ((Engine*)engine)->removeNPC(0);
        ((Engine*)engine)->addNPC("GEOFFREY", 19, 10);
    }
}
