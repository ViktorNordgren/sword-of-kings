/*
* Engine.h
*/

#include <GL/glut.h>

#define cimg_use_png
#include "CImg.h"
using namespace cimg_library;

#include <map>
#include "hero.h"
#include "parser.h"
#include "soundmanager.h"
#include "common_sound.h"
#include "textdialog.h"
#include "gamestate.h"

typedef struct
{
    GLubyte *imageData;
    GLuint bpp;
    GLuint width;
    GLuint height;
    GLuint texID;
} TextureImage;

class Engine
{
    // ID for referencing Engine object from static callback functions
    static const int ENGINE_ID = 0;
    
    // Allows static callback function to call non-static Engine functions.
    static std::map<int, Engine*> engine_id_to_engine;
    
    // Static display callback dispacher
    static void displayDispach() { engine_id_to_engine[ENGINE_ID]->display(); };
    // Main engine display function
    void display();
    
    // Static Special keyboard callback dispacher
    static void processSpecialKeysDispach (int key, int x, int y) { engine_id_to_engine[ENGINE_ID]->processSpecialKeys(key, x, y); };
    // Speical keyboard input callback
    void processSpecialKeys(int, int, int);
    
    // Static normal keyboard callback dispacher
    static void processNormalKeysDispach (unsigned char key, int x, int y) { engine_id_to_engine[ENGINE_ID]->processNormalKeys(key, x, y); };
    // Normal keyboard input callback
    void processNormalKeys(unsigned char, int, int);
    
    // Static hero movement animation dispacher
    static void heroMovementTimerDispach (int value) { engine_id_to_engine[ENGINE_ID]->heroMovementTimer(value); };
    // Hero movement animation timer
    void heroMovementTimer (int);
    
    // Loads an area by ID
    void loadArea(int);
    
    // Loader for all textures
    bool loadTextures();
    // Loads npc textures
    bool loadNPCTextures();
    // Loads hero textures
    bool loadHeroTextures();
    // Loads background texture
    bool loadBackgroundTexture();
    // Loads the background battle texture
    bool loadBattleBackgroundTexture();
    // Loads current monster textures
    bool loadMonsterTextures();
    // Loads Game Over Texture
    bool loadGameOverTexture();
    
    // Loads current area's mask
    bool loadAreaMask();
    
    // Loads a bmp texture
    bool loadTGA(TextureImage*, string);
    
    // Draws Hero
    void drawHero();
    // Draws NPCs above hero
    void drawNPCsAboveHero();
    // Draws NPCs below hero
    void drawNPCsBelowHero();
    // Draws area background
    void drawAreaBackground();
    // Draws the HUD
    void drawHUD();
    // Draw an NPC's text box
    void drawSpeechBox();
    // Helper method to draw a string on the screen
    void drawString( float x, float y, void *font, char *string ); 
    // Draws the battle menu
    void drawBattleMenu();
    // Draws the enemy in a fight
    void drawEnemy();
    // Draws the hero in a fight
    void drawHeroBattle();
    
    // Returns a random int, given a maximum int
    int getRandomInt(int);    
    
    // Starts a battle with a random enemy
    void startRandomBattle();
    // Loads current area's valid monster ID list
    void loadCurrentMonsterIDs();
    
    // The current game state
    GameState* gameState;
    
    // The Hero
    Hero* hero;
    
    // The current area
    Area* currentArea;
    
    // NPC's on the screen
    vector<NPC*> npcs;

    //the current speech to output
    string speech;
    
    //Text object
    TextDialog* textDialog;
    
    //boolean to say if someone is talking
    bool displaySpeech;   
    
    //a boolean that sets if we are in a battle
    bool inBattle;
    
    //boolean that states if the game is over
    bool gameOver;
    
    // Steps taken until next fight will occur
    int stepsUntilNextBattle;
    
    //this tells you which menu option is selected in the battle menu
    int battleArrow; 
    
    bool yourTurn;
    
    // Current enemy hero is fighting
    Enemy* currEnemy;
    // vector of monster IDs that are valid for current area
    vector<string> currentAreaMonsterIDs;
    
    // Current loaded backgrounnd texture
    TextureImage backgroundTexture[1];
    // Hero textures
    TextureImage heroTextures[13];
    // NPC textures
    vector<TextureImage> npcTextures;
    // Current monster textures
    TextureImage monsterTextures[1];
    
    // Current area Mask
    CImg<int> mask;
    
    // Functions which determine if the hero may move in a certain direction
    bool canHeroMoveRight();
    bool canHeroMoveLeft();
    bool canHeroMoveUp();
    bool canHeroMoveDown();
    
    // Functions which move hero in a certain direction
    void moveHeroRight();
    void moveHeroLeft();
    void moveHeroUp();
    void moveHeroDown();
    
    // Function which determines if there is an npc to interact with (-1 if none)
    int canHeroInteractWithNPC();
    
    // When hero is moving, user inputs are disabled
    bool heroIsMoving;
    
    //perform your attack, return true if enemy killed.
    bool doAttack();
    
    //enemy attacks
    void enemyAttack();
    
    // Static attack dispacher
    static void attackTimerDispatch (int value) { engine_id_to_engine[ENGINE_ID]->attackTimer(value); };
    
    //this is your attack timer.  
    void attackTimer(int value);
    
    // Static attack dispacher
    static void enemyAttackTimerDispatch (int value) { engine_id_to_engine[ENGINE_ID]->enemyAttackTimer(value); };
    
    //this is the enemyAttackTimer
    void enemyAttackTimer(int value);
    
    //end the battle in victory
    void endBattleVictory();
    
    //generic end battle
    void endBattle();
    
    //run away
    void endBattleRun();
    
    //you lose
    void endBattleDead();
    
    // Static endBattle dispatcher
    static void endBattle(int value);
    
    // Possible hero orientations
    enum HeroDirection { FACING_NORTH, FACING_SOUTH, FACING_EAST, FACING_WEST };
    HeroDirection heroDirection;
    
    // Possible hero stances
    enum HeroStance { NORMAL_STANCE, RIGHT_STANCE, LEFT_STANCE };
    HeroStance heroStance;
    HeroStance nextStance;
    
    // Grid location of Hero, indexed from bottom left of grid
    int heroPositionX, heroPositionY;
    
    // Fractional grid location of Hero, used in movement animation between cells
    double heroAnimationX, heroAnimationY;
    // Fractional grid locations used for animating battles
    double heroBattleAnimationX, enemyBattleAnimationX;
    // Enum describing movement of currently moving character in battle screen
    enum BattleAnimationDirection { MOVING_RIGHT, MOVING_LEFT };
    
    // Initilize openGL settings
    void initializeOpenGLSettings();
    // Initialize openGL projection settings
    void initializeOpenGLProjectionSettings();
    // Initialize openGL callback functions
    void initializeOpenGLCallbacks();
    
    //sound effect manager
    SoundManager* soundManager;

    
    public:
        // Default constructor
        Engine();
        // Default destructor
        ~Engine();
        // Start Engine
        void run(int, char**);
};
