/*
* Hero.cpp
*/

#include "hero.h"
#include "common_game.h"
#include <iostream>
using namespace std;

/*
* Class Hero
*/

Hero::Hero()
{
    hasSwordOfKings = false;
    height = DEFAULT_HERO_HEIGHT;
    width = DEFAULT_HERO_WIDTH;
    name = DEFAULT_HERO_NAME;
    totalHitPoints = DEFAULT_HERO_HITPOINTS;
    remainingHitPoints = totalHitPoints;
    attack = DEFAULT_HERO_ATTACK;
    defense = DEFAULT_HERO_DEFENSE;
    level = DEFAULT_HERO_LEVEL;
    expToNextLevel = DEFAULT_EXP_TO_NEXT_LEVEL;
    numPotions = DEFAULT_NUM_POTIONS;
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

string Hero::getFightNormalTexture()
{
    return HERO_FIGHT_NORMAL_TEXTURE;
}

int Hero::getNumPotions()
{
    return numPotions;   
}

/*
* Setters
*/
void Hero::setHasSwordOfKings(bool hasSword)
{
    hasSwordOfKings = hasSword;
    attack = 1000 * level;
}

void Hero::incrementNumPotions()
{
    numPotions++;   
}

bool Hero::usePotion()
{
    if(numPotions == 0)
    {
        return false;
    }
    if(remainingHitPoints == totalHitPoints)
    {
        return false;
    }
    
    remainingHitPoints += POTION_AMOUNT;
    if(remainingHitPoints > totalHitPoints)
    {
        remainingHitPoints = totalHitPoints;
    }
    numPotions--;
    return true;
    
}

void Hero::increaseExp(int exp)
{

    expToNextLevel -= exp;
    
    if(expToNextLevel <= 0)
    {
    
        incrementLevel();
        expToNextLevel += 20 + level * 15; 
    }  

}

void Hero::incrementLevel()
{
    level++;
    totalHitPoints += level * 5;
    remainingHitPoints = totalHitPoints;
    attack += 5 + (int)(level * 0.5);
    defense += (int)(level * 0.5);
}
