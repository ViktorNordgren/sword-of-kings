/*
* Character.cpp
*/

#include "npc.h"

/*
* Class Character
*/

/*
* Default constructor
*/


// Default constructor
NPC::NPC()
{
    name = "";
}

NPC::NPC(string n)
{
    name = n;
}

NPC::NPC(string n, string text)
{
    name = n;
    texture = text;
}

// Default destructor
NPC::~NPC()
{
}

 // getters
string NPC::getName()
{
    return name;
}

string NPC::getTexture()
{
    return texture;
}

Point NPC::getLocation()
{
    return location;    
}

// setters
void NPC::setName(string n)
{
    name = n;
}

void NPC::setTexture(string text)
{
    texture = text;   
}

void NPC::setLocation(Point loc)
{
    location = loc;
}
