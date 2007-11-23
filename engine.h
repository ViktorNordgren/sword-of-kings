/*
* Engine.h
*/

#include <map>
#include "hero.h"

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
    void processSpecialKeys(int key, int x, int y);
    
    // Static normal keyboard callback dispacher
    static void processNormalKeysDispach (unsigned char key, int x, int y) { engine_id_to_engine[ENGINE_ID]->processNormalKeys(key, x, y); };
    // Normal keyboard input callback
    void processNormalKeys(unsigned char key, int x, int y);
    
    // Draws Hero
    void drawHero();
    
    // Possible hero orientation
    enum HeroDirection { FACING_NORTH, FACING_SOUTH, FACING_EAST, FACING_WEST };
    HeroDirection heroDirection;
    
    // Grid location of Hero, indexed from bottom left of grid
    int heroPositionX, heroPositionY;
    
    // The Hero
    Hero * hero;
    
    public:
        // Default constructor
        Engine();
        // Default destructor
        ~Engine();
        // Initilize openGL settings
        void initializeOpenGLSettings();
        // Initialize openGL projection settings
        void initializeOpenGLProjectionSettings();
        // Initialize openGL callback functions
        void initializeOpenGLCallbacks();
        // Start Engine
        void run(int, char**);
};
