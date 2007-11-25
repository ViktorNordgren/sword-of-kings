/*
* Parser.h
*/

#ifndef _DEFINED_parser
#define _DEFINED_parser

#include "enemy.h"
#include "area.h"
#include "npc.h"
#include <string>
using namespace std;



class Parser
{
    public:
        static bool getEnemy(Enemy* enemy, string enemyName);
        static bool getArea(Area* area, int areaID);
        static bool getNPC(NPC* npc, string npcName);
        
        static void tokenize(const string&, vector<string>&, const string& = " ");
        
        
};

#endif
