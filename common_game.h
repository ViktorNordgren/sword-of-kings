#ifndef _DEFINED_common_game
#define _DEFINED_common_game
using namespace std;

enum BattleMenuChoice
{
    ATTACK = 0,
    HEAL = 1,
    RUN = 2
};

struct Point 
{ 
    int x; 
    int y; 
};

struct Dialog
{
    string text;
    string condition;
    string event;
};

/*
* Default Hero Stats
*/
static const int DEFAULT_HERO_HEIGHT = 5;
static const int DEFAULT_HERO_WIDTH = 3;
static const int DEFAULT_HERO_HITPOINTS = 50;
static const int DEFAULT_HERO_ATTACK = 40;
static const int DEFAULT_HERO_DEFENSE = 3;
static const int DEFAULT_HERO_LEVEL = 1;
static const int DEFAULT_EXP_TO_NEXT_LEVEL = 40;
static const int DEFAULT_NUM_POTIONS = 4;
static const string DEFAULT_HERO_NAME = "Joe Blow";
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
static const string HERO_FIGHT_NORMAL_TEXTURE = "textures/characters/hero/fight_normal.tga";

static const int POTION_AMOUNT = 20;

static const int BATTLE_ANIMATION_DELAY = 20;

/*
* Locations of File Names to read in
*/
static const string ENEMY_FILE_PATH = "enemies.txt";
static const string AREA_FILE_PATH = "areas.txt";
static const string NPC_FILE_PATH = "npc.txt";

/*
* Hero movement
*/
static const int HERO_MOVEMENT_DELAY = 10;
static const double HERO_MOVEMENT_DISTANCE = 0.1;
static const int HERO_MOVEMENT_AMOUNT = 1;

/*
* Conditions
*/
static const string DEFAULT = "DEFAULT";
static const string SWORD_FOUND = "SWORD_FOUND";
static const string TALKED_TO_GEOFFERY = "TALKED_TO_GEOFFERY";

/*
* Actions
*/
static const string GET_SWORD = "GET_SWORD";
static const string NOTHING = "NOTHING";

/*
* List of valid monster IDs
*/
static const string MONSTER_IDS [] = {"ORC"};

/*
* Settings for the speech box
*/
static const int LINE_LENGTH = 90; //length of line in chars
static const int LINE_HEIGHT = 25; //height of a line in pixels
static const int NUM_LINES = 5; //number of lines


#endif
