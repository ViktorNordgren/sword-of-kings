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
    
    //now lets read the stats from the file
	if (enemyFile.is_open())
	{
		while (!enemyFile.eof())
		{
            //get the current line
			getline(enemyFile, line);
            
            vector<string> tokens; // Create vector to hold our words
            tokenize(line, tokens);
            
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
                    enemy->setRemainingHitPoints(atoi(tokens[1].c_str()));
                }
                else if(name.compare("NAME") == 0)
                {
                    enemy->setName(tokens[1]);
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

bool Parser::getArea(Area* area, int areaID)
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

            vector<string> tokens; // Create vector to hold our words
            tokenize(line, tokens);
            
            string name = "";
            
            if(tokens.size() > 0)
                name = tokens[0];
            else
                inWantedObject = false;
                
            //if we haven't found the object we want
            if(!inWantedObject)
            {
                //if this is the object we want
                if(atoi(name.c_str()) == areaID)
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
                else if(name.compare("BATTLEBG") == 0)
                {
                    area->setBattleTexture(tokens[1]);
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
                    Point location;
                    location.x = atoi(tokens[2].c_str());
                    location.y = atoi(tokens[3].c_str());
                    npc->setLocation(location);
                    area->addNPC(npc);
                }
                else if(name.compare("MONSTERS") == 0)
                {
                    area->setMonsterFrequency(atoi(tokens[2].c_str()));
                    area->setMaxMonsterLevel(atoi(tokens[4].c_str()));
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
            vector<string> tokens; // Create vector to hold our words
            tokenize(line, tokens);
            
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
                else if(name.compare("DIALOG") == 0)
                {
                   Dialog newDialog;
                   newDialog.condition = tokens[1];
                   newDialog.text = tokens[2];
                   newDialog.event = tokens[3];
                   npc->addDialog(newDialog);
                }
                else if(name.compare("HEIGHT") == 0)
                {
                    npc->setHeight(atoi(tokens[1].c_str()));
                }
                else if(name.compare("WIDTH") == 0)
                {
                    npc->setWidth(atoi(tokens[1].c_str()));
                }
            }
		}
		npcFile.close();
	}
}

void Parser::tokenize(const string& str, vector<string>& tokens, const string& delimiters)
{
    if (str.length() < 1)
    {
        return;
    }
    
    // Delimiters cannot be found within quotation marks
    string quotationMark = "\"";
    // Find first quotation mark
    string::size_type lastQuot = str.find_first_of(quotationMark, 0);
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    
    string::size_type pos;
    
    if ( lastQuot <= lastPos )
    {
        lastPos = lastQuot + (string::size_type)(1);
        pos = str.find_first_of(quotationMark, lastPos);
    }
    else
    {
        // Find first "non-delimiter".
        pos = str.find_first_of(delimiters, lastPos);
    }

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        
        if (pos >= str.length() - 1)
        {
            break;
        }
        
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos + 1);
        // Find next quotation mark
        string::size_type lastQuot = str.find_first_of(quotationMark, pos + 1);
        
        if ( lastQuot <= lastPos )
        {
            lastPos = lastQuot + (string::size_type)(1);
            pos = str.find_first_of(quotationMark, lastPos);
        }
        else
        {
            // Find first "non-delimiter".
            pos = str.find_first_of(delimiters, lastPos);
        }
    }
}
