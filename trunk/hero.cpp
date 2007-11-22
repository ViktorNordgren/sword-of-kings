/*
* Hero.cpp
*/

#include "hero.h"


/*
* Class Hero
*/


/*
* This constuctor can be used to specify all values of a character
*/
Hero::Hero(string n, int hitpoints, double att, double def, int lev, string text) : Character(n, hitpoints, att, def, lev, text)
{
    hasSwordOfKings = false;
    height = DEFAULT_HERO_HEIGHT;
    width = DEFAULT_HERO_WIDTH;
}

/*
* This constructor will set some values based on the level specified
*/
Hero::Hero(string n, int lev, string text) : Character(n, lev, text)
{
    hasSwordOfKings = false;
    height = DEFAULT_HERO_HEIGHT;
    width = DEFAULT_HERO_WIDTH;
}

/*
* Getters
*/
bool Hero::getHasSwordOfKings()
{
    return hasSwordOfKings;
}

/*
* Setters
*/
void Hero::setHasSwordOfKings(bool hasSword)
{
    hasSwordOfKings = hasSword;
    attack = 1000 * level;
}
