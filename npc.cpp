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
    height = 5;
    width = 3;
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

int NPC::getHeight()
{
    return height;
}

int NPC::getWidth()
{
    return width;
}

vector<Dialog> NPC::getDialogs()
{
    return dialogs;
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

void NPC::setHeight(int h)
{
    height = h;
}

void NPC::setWidth(int w)
{
    width = w;
}

void NPC::addDialog(Dialog dialog)
{
    dialogs.push_back(dialog);
}

