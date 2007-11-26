/*
* Area.cpp
*/

#include "area.h"


/*
* Class Area
*/

Area::Area()
{
    north = -1;
    south = -1;
    east = -1;
    west = -1;
    maxMonsterLevel = -1;
    monsterFrequency = -1;
}

Area::Area(string mainText, string imMask, int n, int s, int e, int w)
{
    mainTexture = mainText;
    imageMask = imMask;
    north = n;
    south = s;
    east = e;
    west = w;
    maxMonsterLevel = -1;
    monsterFrequency = -1;
}
// Default destructor
Area::~Area()
{
}

//getters
int Area::getID()
{
    return id;
}

string Area::getMainTexture()
{
    return mainTexture;
}

string Area::getBattleTexture()
{
    return battleTexture;
}

string Area::getImageMask()
{
    return imageMask;
}

int Area::getNorth()
{
    return north;
}

int Area::getWest()
{
    return west;
}

int Area::getSouth()
{
    return south;    
}

int Area::getEast()
{
    return east;
}

Point Area::getEntryNorth()
{
    return entryNorth;
}

Point Area::getEntrySouth()
{
    return entrySouth;
}

Point Area::getEntryEast()
{
    return entryEast;
}

Point Area::getEntryWest()
{
    return entryWest;
}

vector<NPC*> Area::getNPCs()
{
    return npcs;   
}

int Area::getMaxMonsterLevel()
{
    return maxMonsterLevel;
}

int Area::getMonsterFrequency()
{
    return monsterFrequency;
}

bool Area::hasMonsters()
{
    return (monsterFrequency != -1);
}

//setters
void Area::setID(int i)
{
    id = i;
}

void Area::setNorth(int n)
{
    north = n;   
}

void Area::setWest(int w)
{
    west = w;
}

void Area::setSouth(int s)
{
    south = s;
}

void Area::setEast(int e)
{
    east = e;
}
void Area::setEntryNorth(Point entryN)
{
    entryNorth = entryN;
}

void Area::setEntrySouth(Point entryS)
{
    entrySouth = entryS;
}

void Area::setEntryEast(Point entryE)
{
    entryEast = entryE;
}

void Area::setEntryWest(Point entryW)
{
    entryWest = entryW;
}

void Area::setMainTexture(string texture)
{
    mainTexture = texture;
}

void Area::setBattleTexture(string texture)
{
    battleTexture = texture;
}

void Area::setImageMask(string mask)
{
    imageMask = mask;
}

void Area::setMonsterFrequency(int freq)
{
    monsterFrequency = freq;
}

void Area::setMaxMonsterLevel(int level)
{
    maxMonsterLevel = level;
}

//add an npc
void Area::addNPC(NPC* npc)
{
    npcs.push_back(npc);   
}

//test if areas exist around here
bool Area::canMoveNorth()
{
    return north != -1;   
}

bool Area::canMoveSouth()
{
    return south != -1;   
}

bool Area::canMoveEast()
{
    return east != -1;   
}

bool Area::canMoveWest()
{
    return west != -1;   
}

