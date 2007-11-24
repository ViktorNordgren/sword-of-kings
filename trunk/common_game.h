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
static const string HERO_NORTH_NORMAL_TEXTURE = "textures/characters/hero/north_normal.tga";
static const string HERO_NORTH_RIGHT_TEXTURE = "textures/characters/hero/north_right.tga";
static const string HERO_NORTH_LEFT_TEXTURE = "textures/characters/hero/north_left.tga";
static const string HERO_SOUTH_NORMAL_TEXTURE = "textures/characters/hero/south_normal.tga";
static const string HERO_SOUTH_RIGHT_TEXTURE = "textures/characters/hero/south_right.tga";
static const string HERO_SOUTH_LEFT_TEXTURE = "textures/characters/hero/south_left.tga";
static const string HERO_EAST_NORMAL_TEXTURE = "textures/characters/hero/east_normal.tga";
static const string HERO_EAST_RIGHT_TEXTURE = "textures/characters/hero/east_right.tga";
static const string HERO_EAST_LEFT_TEXTURE = "textures/characters/hero/east_left.tga";
static const string HERO_WEST_NORMAL_TEXTURE = "textures/characters/hero/west_normal.tga";
static const string HERO_WEST_RIGHT_TEXTURE = "textures/characters/hero/west_right.tga";
static const string HERO_WEST_LEFT_TEXTURE = "textures/characters/hero/west_left.tga";


/*
* Locations of File Names to read in
*/
static const string ENEMY_FILE_PATH = "enemies.txt";
static const string AREA_FILE_PATH = "areas.txt";
static const string NPC_FILE_PATH = "npc.txt";

/*
* Hero movement
*/
static const int HERO_MOVEMENT_DELAY = 15;
static const double HERO_MOVEMENT_DISTANCE = 0.2;

#endif
