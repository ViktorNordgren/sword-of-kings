/*
* Character.cpp
*/

#include "character.h"

/*
* Class Character
*/

/*
* Default constructor
*/
Character::Character()
{
}

/*
* This constuctor can be used to specify all values of a character
*/
Character::Character(string n, int hitpoints, double att, double def, int lev, string text)
{
    name = n;
    totalHitPoints = hitpoints;
    remainingHitPoints = hitpoints;
    attack = att;
    defense = def;
    level = lev;
    texture = text;
}

/*
* This constructor will set some values based on the level specified
*/
Character::Character(string n, int lev, string text)
{
    name = n;
    level = lev;
    totalHitPoints = 20 * lev;
    remainingHitPoints = totalHitPoints;
    attack = 3 * lev;
    defense = 3 * lev;
    texture = text;
}

/*
* Default destructor
*/
Character::~Character()
{
}

/*
* Getters
*/
string Character::getName()
{
    return name;
}

int Character::getTotalHitPoints()
{
    return totalHitPoints;
}

int Character::getRemainingHitPoints()
{
    return remainingHitPoints;
}

double Character::getAttack()
{
    return attack;
}

double Character::getDefense()
{
    return defense;
}

int Character::getLevel()
{
    return level;
}

string Character::getTexture()
{
    return texture;   
}

int  Character::getHeight()
{
    return height;   
}

int  Character::getWidth()
{
    return width;
}

/* 
* Setters
*/
void Character::setName(string n)
{
    name = n;    
}

void Character::setTotalHitPoints(int total)
{
    totalHitPoints = total;
}

void Character::setRemainingHitPoints(int remaining)
{
    remainingHitPoints = remaining;    
}

void Character::setAttack(double a)
{
    attack = a;   
}

void Character::setDefense(double d)
{
    defense = d;
}

void Character::setLevel(int l)
{
    level = l;    
}

void Character::incrementLevel()
{
    level++;   
}

void Character::setTexture(string text)
{
    texture = text;
}

void Character::setHeight(int h)
{
    height = h;   
}

void Character::setWidth(int w)
{
    width = w;
}

