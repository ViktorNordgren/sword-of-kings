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
* Texture Getters
*/
string Hero::getNorthNormalTexture()
{
    return HERO_NORTH_NORMAL_TEXTURE;
}

string Hero::getNorthRightTexture()
{
    return HERO_NORTH_RIGHT_TEXTURE;
}

string Hero::getNorthLeftTexture()
{
    return HERO_NORTH_LEFT_TEXTURE;
}

string Hero::getSouthNormalTexture()
{
    return HERO_SOUTH_NORMAL_TEXTURE;
}

string Hero::getSouthRightTexture()
{
    return HERO_SOUTH_RIGHT_TEXTURE;
}

string Hero::getSouthLeftTexture()
{
    return HERO_SOUTH_LEFT_TEXTURE;
}

string Hero::getEastNormalTexture()
{
    return HERO_EAST_NORMAL_TEXTURE;
}

string Hero::getEastRightTexture()
{
    return HERO_EAST_RIGHT_TEXTURE;
}

string Hero::getEastLeftTexture()
{
    return HERO_EAST_LEFT_TEXTURE;
}

string Hero::getWestNormalTexture()
{
    return HERO_WEST_NORMAL_TEXTURE;
}

string Hero::getWestRightTexture()
{
    return HERO_WEST_RIGHT_TEXTURE;
}

string Hero::getWestLeftTexture()
{
    return HERO_WEST_LEFT_TEXTURE;
}


/*
* Setters
*/
void Hero::setHasSwordOfKings(bool hasSword)
{
    hasSwordOfKings = hasSword;
    attack = 1000 * level;
}
