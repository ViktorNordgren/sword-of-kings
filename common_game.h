#ifndef _DEFINED_common_game
#define _DEFINED_common_game
using namespace std;

enum EnemyType
{
    RAT,
    ORC,
    SOLDIER,
    BOSS
};

struct Point 
{ 
    int x; 
    int y; 
};

/*
* Default Hero Stats
*/
static const int DEFAULT_HERO_HEIGHT = 5;
static const int DEFAULT_HERO_WIDTH = 3;
static const int DEFAULT_HERO_HITPOINTS = 50;
static const int DEFAULT_HERO_ATTACK = 5;
static const int DEFAULT_HERO_DEFENSE = 5;
static const int DEFAULT_HERO_LEVEL = 1;
static const string DEFAULT_HERO_TEXTURE = "path\\to\\hero\\texture.jpg";

/*
* Locations of File Names to read in
*/
static const string ENEMY_FILE_PATH = "enemies.txt";
static const string AREA_FILE_PATH = "areas.txt";
static const string NPC_FILE_PATH = "npc.txt";

#endif
