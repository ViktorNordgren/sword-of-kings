/*
* Parser.cpp
*/

#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

/*
* Class Parser
*/

bool Parser::getEnemy(Enemy* enemy, string enemyName)
{
    string line;
	ifstream enemyFile(ENEMY_FILE_PATH.c_str());
    bool inWantedObject = false;
    
    //first let's set the type of enemy, and return failure if this isn't a valid enemy
    if(enemyName.compare("RAT") == 0)
    {
        enemy->setEnemyType(RAT);
    }
    else if(enemyName.compare("ORC") == 0)
    {
        enemy->setEnemyType(ORC);
    }
    else if(enemyName.compare("SOLDIER") == 0)
    {
        enemy->setEnemyType(SOLDIER);
    }
    else if(enemyName.compare("BOSS") == 0)
    {
        enemy->setEnemyType(BOSS);
    }
    else
    {
        //the specified enemy was not found
        return false;
    }
    
    //now lets read the stats from the file
	if (enemyFile.is_open())
	{
		while (!enemyFile.eof())
		{
            //get the current line
			getline(enemyFile, line);
			
			//tokenize the string
            string buf; // Have a buffer string
            stringstream ss(line); // Insert the string into a stream
            vector<string> tokens; // Create vector to hold our words
            
            
            while (ss >> buf)
                tokens.push_back(buf);
            string name = "";
            
            if(tokens.size() > 0)
                name = tokens[0];
            else
                inWantedObject = false;
                
            //if we haven't found the object we want
            if(!inWantedObject)
            {
                //if this is the object we want
                if(name.compare(enemyName) == 0)
                {
                    inWantedObject = true;
                }
            }
            else
            if(inWantedObject)
            {
                if(name.compare("TOTALHITPOINTS") == 0)
                {
                    enemy->setTotalHitPoints(atoi(tokens[1].c_str()));
                }
                else if(name.compare("ATTACK") == 0)
                {
                    enemy->setAttack(atof(tokens[1].c_str()));
                }
                else if(name.compare("DEFENSE") == 0)
                {
                    enemy->setDefense(atof(tokens[1].c_str()));
                }
                else if(name.compare("LEVEL") == 0)
                {
                    enemy->setLevel(atoi(tokens[1].c_str()));
                }
                else if(name.compare("TEXTURE") == 0)
                {
                    enemy->setTexture(tokens[1].c_str());
                }
                else if(name.compare("HEIGHT") == 0)
                {
                    enemy->setHeight(atoi(tokens[1].c_str()));
                }
                else if(name.compare("WIDTH") == 0)
                {
                    enemy->setWidth(atoi(tokens[1].c_str()));
                }
            }
			
			
		}
		enemyFile.close();
	}
}

bool Parser::getArea(Area* area, string areaName)
{
    string line;
	ifstream areaFile(AREA_FILE_PATH.c_str());
    bool inWantedObject = false;
    
    //now lets read the stats from the file
	if (areaFile.is_open())
	{
		while (!areaFile.eof())
		{
            //get the current line
			getline(areaFile, line);
			
			//tokenize the string
            string buf; // Have a buffer string
            stringstream ss(line); // Insert the string into a stream
            vector<string> tokens; // Create vector to hold our words
            
            
            while (ss >> buf)
                tokens.push_back(buf);
            string name = "";
            
            if(tokens.size() > 0)
                name = tokens[0];
            else
                inWantedObject = false;
                
            //if we haven't found the object we want
            if(!inWantedObject)
            {
                //if this is the object we want
                if(name.compare(areaName) == 0)
                {
                    inWantedObject = true;
                }
            }
            else
            if(inWantedObject)
            {
                if(name.compare("ID") == 0)
                {
                    area->setID(atoi(tokens[1].c_str()));
                }
                else if(name.compare("BG") == 0)
                {
                    area->setMainTexture(tokens[1]);
                }
                else if(name.compare("MASK") == 0)
                {
                    area->setImageMask(tokens[1]);
                }
                else if(name.compare("NORTH") == 0)
                {
                    area->setNorth(atoi(tokens[1].c_str()));
                }
                else if(name.compare("SOUTH") == 0)
                {
                    area->setSouth(atoi(tokens[1].c_str()));
                }
                else if(name.compare("EAST") == 0)
                {
                    area->setEast(atoi(tokens[1].c_str()));
                }
                else if(name.compare("WEST") == 0)
                {
                    area->setWest(atoi(tokens[1].c_str()));
                }
                else if(name.compare("NORTHENTRY") == 0)
                {
                    Point entry;
                    entry.x = atoi(tokens[1].c_str());
                    entry.y = atoi(tokens[2].c_str());
                    area->setEntryNorth(entry);
                }
                else if(name.compare("SOUTHENTRY") == 0)
                {
                    Point entry;
                    entry.x = atoi(tokens[1].c_str());
                    entry.y = atoi(tokens[2].c_str());
                    area->setEntrySouth(entry);
                }
                else if(name.compare("EASTENTRY") == 0)
                {
                    Point entry;
                    entry.x = atoi(tokens[1].c_str());
                    entry.y = atoi(tokens[2].c_str());
                    area->setEntryEast(entry);
                }
                else if(name.compare("WESTENTRY") == 0)
                {
                    Point entry;
                    entry.x = atoi(tokens[1].c_str());
                    entry.y = atoi(tokens[2].c_str());
                    area->setEntryWest(entry);
                }
                else if(name.compare("NPC") == 0)
                {
                    NPC* npc = new NPC();
                    getNPC(npc, tokens[1].c_str());
                    area->addNPC(npc);
                }
            }
			
			
		}
		areaFile.close();
	}
}

bool Parser::getNPC(NPC* npc, string npcName)
{
    string line;
	ifstream npcFile(NPC_FILE_PATH.c_str());
    bool inWantedObject = false;
    
    //now lets read the stats from the file
	if (npcFile.is_open())
	{
		while (!npcFile.eof())
		{
            //get the current line
			getline(npcFile, line);
			
			//tokenize the string
            string buf; // Have a buffer string
            stringstream ss(line); // Insert the string into a stream
            vector<string> tokens; // Create vector to hold our words
            
            
            while (ss >> buf)
                tokens.push_back(buf);
            string name = "";
            
            if(tokens.size() > 0)
                name = tokens[0];
            else
                inWantedObject = false;
                
            //if we haven't found the object we want
            if(!inWantedObject)
            {
                //if this is the object we want
                if(name.compare(npcName) == 0)
                {
                    inWantedObject = true;
                }
            }
            else
            if(inWantedObject)
            {
                if(name.compare("NAME") == 0)
                {
                    npc->setName(tokens[1].c_str());
                }
                else if(name.compare("TEXTURE") == 0)
                {
                    npc->setTexture(tokens[1].c_str());
                }
                else if(name.compare("LOCATION") == 0)
                {
                    Point location;
                    location.x = atoi(tokens[1].c_str());
                    location.y = atoi(tokens[2].c_str());
                    npc->setLocation(location);
                }
            }
			
			
		}
		npcFile.close();
	}
}
