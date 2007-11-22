/*
* Area.cpp
*/

#include "area.h"


/*
* Class Area
*/

Area::Area()
{
}

Area::Area(string mainText, string imMask, int n, int s, int e, int w)
{
    mainTexture = mainText;
    imageMask = imMask;
    north = n;
    south = s;
    east = e;
    west = w;
}
// Default destructor
Area::~Area()
{
}

//getters
string Area::getMainTexture()
{
    return mainTexture;
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


//setters
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
