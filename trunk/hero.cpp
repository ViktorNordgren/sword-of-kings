/*
* Hero.cpp
*/

#include "hero.h"
#include "common_game.h"

/*
* Class Hero
*/

Hero::Hero()
{
    hasSwordOfKings = false;
    height = DEFAULT_HERO_HEIGHT;
    width = DEFAULT_HERO_WIDTH;
    name = "";
    totalHitPoints = DEFAULT_HERO_HITPOINTS;
    attack = DEFAULT_HERO_ATTACK;
    defense = DEFAULT_HERO_DEFENSE;
    level = DEFAULT_HERO_LEVEL;
    texture = DEFAULT_HERO_TEXTURE;
}

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
