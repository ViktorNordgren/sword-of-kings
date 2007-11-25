/*
* Engine.cpp
*/

#include "common.h"
#include "engine.h"

#include <iostream>
#include <sstream>

using namespace std;

/***************************************
* Class Engine
***************************************/

// Static variables need to be 'implemented' here to preferent undefined reference
std::map<int, Engine*> Engine::engine_id_to_engine;
const int Engine::ENGINE_ID;
string teststring = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi.";

/*
* Default constructor
*/
Engine::Engine()
{
    // Create hero
    hero = new Hero(/*"Hero", 1, "heropicture.bmp"*/);
    
    heroPositionX = 0;
    heroPositionY = 0;
    heroAnimationY = 0;
    heroAnimationX = 0;
    heroDirection = FACING_SOUTH;
    heroStance = NORMAL_STANCE;
    nextStance = RIGHT_STANCE;
    heroIsMoving = false;
    soundManager = new SoundManager();
    // Create and load default area
    currentArea = new Area();
    displaySpeech = false;
    speech = "";
    loadArea(1);
    gameState = new GameState();
    inBattle = false;
}

/*
* Default destructor
*/
Engine::~Engine()
{
    delete hero;
    delete currentArea;
    npcTextures.clear();
    delete soundManager;
    delete textDialog;
    delete gameState;
}

/*
* Loads the current area's clipping mask
*/
bool Engine::loadAreaMask()
{
    mask  = CImg<double>::get_load_png(currentArea->getImageMask().c_str());
}

/*
* Loads textures
*/
bool Engine::loadTextures()
{
    loadHeroTextures();
    
    loadBackgroundTexture();
    
    loadNPCTextures();
    
    return true;
}

/*
* Loads NPC textures for current area
*/
bool Engine::loadNPCTextures()
{
    npcTextures.clear();
    for (int i = 0; i < npcs.size(); i++)
    {
        TextureImage npcTexture;
        loadTGA(&npcTexture, npcs.at(i)->getTexture());
        npcTextures.push_back(npcTexture);
    }
}

/*
* Loads hero textures
*/
bool Engine::loadHeroTextures()
{
    loadTGA(&heroTextures[0], hero->getSouthNormalTexture());
    loadTGA(&heroTextures[1], hero->getSouthRightTexture());
    loadTGA(&heroTextures[2], hero->getSouthLeftTexture());
    loadTGA(&heroTextures[3], hero->getNorthNormalTexture());
    loadTGA(&heroTextures[4], hero->getNorthRightTexture());
    loadTGA(&heroTextures[5], hero->getNorthLeftTexture());
    loadTGA(&heroTextures[6], hero->getEastNormalTexture());
    loadTGA(&heroTextures[7], hero->getEastRightTexture());
    loadTGA(&heroTextures[8], hero->getEastLeftTexture());
    loadTGA(&heroTextures[9], hero->getWestNormalTexture());
    loadTGA(&heroTextures[10], hero->getWestRightTexture());
    loadTGA(&heroTextures[11], hero->getWestLeftTexture());

    return true;
}

/*
* Loads background texture
*/
bool Engine::loadBackgroundTexture()
{
    if (!loadTGA(&backgroundTexture[0], currentArea->getMainTexture()))
    {
        return false;
    }
    
    return true;
}

/*
* Loads a TGA texture
*/
bool Engine::loadTGA(TextureImage* texture, string filename)
{
    GLubyte TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    GLubyte TGAcompare[12];
    GLubyte header[6];
    GLuint bytesPerPixel;
    GLuint imageSize;
    GLuint temp;
    GLuint type = GL_RGBA;
    
    FILE * file = fopen(filename.c_str(), "rb");
    
    if (file == NULL || fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||
        memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||
        fread(header, 1, sizeof(header), file) != sizeof(header))
    {
        if (file == NULL)
            return false;
        else
        {
            fclose(file);
            return false;
        }
    }
    
    texture->width = header[1] * 256 + header[0];
    texture->height = header[3] * 256 + header[2];
    
    if (texture->width <= 0 || texture->height <= 0 || (header[4] != 24 && header[4] != 32))
    {
        fclose(file);
        return false;
    }
    
    texture->bpp = header[4];
    bytesPerPixel = texture->bpp / 8;
    imageSize = texture->width * texture->height * bytesPerPixel;
    
    texture->imageData = (GLubyte*)malloc(imageSize);
    
    if (texture->imageData == NULL || fread(texture->imageData, 1, imageSize, file) != imageSize)
    {
        if (texture->imageData != NULL)
            free(texture->imageData);
            
        fclose(file);
        return false;
    }
    
    for (GLuint i = 0; i < int(imageSize); i += bytesPerPixel)
    {
        temp = texture->imageData[i];
        texture->imageData[i] = texture->imageData[i + 2];
        texture->imageData[i + 2] = temp;
    }
    
    fclose(file);
    
    glGenTextures(1, &texture[0].texID);
    
    glBindTexture (GL_TEXTURE_2D, texture[0].texID);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if (texture[0].bpp == 24)
    {
        type = GL_RGB;
    }
    
    glTexImage2D (GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);
    
    return true;
}

/*
* Loads an area by ID
*/
void Engine::loadArea(int id)
{
    delete currentArea;
    currentArea = new Area();
    Parser::getArea(currentArea, id);
    loadBackgroundTexture();
    npcs.clear();
    npcs = currentArea->getNPCs();
    loadNPCTextures();
    loadAreaMask();
}

/*
* Determine if hero can interact with an NPC in the direction that he's facing.
* Returns the index of the NPC in the npcs vector; returns -1 if no NPC available.
*/
int Engine::canHeroInteractWithNPC()
{
    NPC * npc;
    
    for (int i = 0; i < npcs.size(); i++)
    {
        npc = npcs.at(i);
        Point npcPos;

        switch (heroDirection)
        {
            case FACING_NORTH:
                
                // Check if an NPC is immediately to the north
                npcPos = npc->getLocation();
                if (heroPositionX < npcPos.x + npcs.at(i)->getWidth() && 
                    heroPositionX + hero->getWidth() > npcPos.x &&
                    heroPositionY + 1 == npcPos.y )
                {
                    return i;
                }
                break;
                
            case FACING_SOUTH:
                
                // Check if an NPC is immediately to the south
                npcPos = npc->getLocation();
                if (heroPositionX < npcPos.x + npcs.at(i)->getWidth() && 
                    heroPositionX + hero->getWidth() > npcPos.x &&
                    heroPositionY - 1 == npcPos.y )
                {
                    return i;
                }
                break;
                
            case FACING_EAST:

                // Check if an NPC is immediately to the east
                Point npcPos = npcs.at(i)->getLocation();
                if ( heroPositionX + hero->getWidth() == npcPos.x && heroPositionY == npcPos.y )
                {
                    return i;
                }
                break;
                
            case FACING_WEST:
                
                // Check if an NPC is immediately to the west
                npcPos = npc->getLocation();
                if ( heroPositionX - 1 == npcPos.x + npcs.at(i)->getWidth() - 1 && heroPositionY == npcPos.y )
                {
                    return i;
                }
                break;
        }
    }

    return -1;
}
/*
* Determine if hero can move right
*/
bool Engine::canHeroMoveRight()
{
    heroDirection = FACING_EAST;

    int newRightPosition = heroPositionX + hero->getWidth();
    
    // The grid block to the right is solid, cannot walk past it.
    if ((int)(mask.pix4d (newRightPosition, GRID_HEIGHT - heroPositionY - 1, 0, 0, 255)) <= 0)
        return false;
        
    // Check if an NPC is blocking the way
    for (int i = 0; i < npcs.size(); i++)
    {
        Point npcPos = npcs.at(i)->getLocation();
        if ( newRightPosition == npcPos.x && heroPositionY == npcPos.y )
        {
            return false;
        }
    }
    
    return true;
}

/*
* Determine if hero can move left
*/
bool Engine::canHeroMoveLeft()
{       
    heroDirection = FACING_WEST;

    int newLeftPosition = heroPositionX - 1;

    // The grid block to the left is solid, cannot walk past it.
    if ((int)(mask.pix4d (newLeftPosition, GRID_HEIGHT - heroPositionY - 1, 0, 0, 255)) <= 0)
        return false;
        
    // Check if an NPC is blocking the way
    for (int i = 0; i < npcs.size(); i++)
    {
        Point npcPos = npcs.at(i)->getLocation();
        if ( newLeftPosition == npcPos.x + npcs.at(i)->getWidth() - 1 && heroPositionY == npcPos.y )
        {
            return false;
        }
    }
    
    return true;
}

/*
* Determine if hero can move up
*/
bool Engine::canHeroMoveUp()
{
    heroDirection = FACING_NORTH;    

    int newUpPosition = heroPositionY + 1;

    // The grid block above is solid, cannot walk past it.
    if ((int)(mask.pix4d (heroPositionX, GRID_HEIGHT - newUpPosition - 1, 0, 0, 255)) <= 0)
        return false;
        
    // Check if an NPC is blocking the way
    for (int i = 0; i < npcs.size(); i++)
    {
        Point npcPos = npcs.at(i)->getLocation();
        if (heroPositionX < npcPos.x + npcs.at(i)->getWidth() && 
            heroPositionX + hero->getWidth() > npcPos.x &&
            newUpPosition == npcPos.y )
        {
            return false;
        }
    }
        
    return true;
}

/*
* Determine if hero can move down
*/
bool Engine::canHeroMoveDown()
{
    heroDirection = FACING_SOUTH;    

    int newDownPosition = heroPositionY - 1;

    // The grid block below is solid, cannot walk past it.
    if ((int)(mask.pix4d (heroPositionX, GRID_HEIGHT - newDownPosition - 1, 0, 0, 255)) <= 0)
        return false;
        
    // Check if an NPC is blocking the way
    for (int i = 0; i < npcs.size(); i++)
    {
        Point npcPos = npcs.at(i)->getLocation();
        if (heroPositionX < npcPos.x + npcs.at(i)->getWidth() && 
            heroPositionX + hero->getWidth() > npcPos.x &&
            newDownPosition == npcPos.y )
        {
            return false;
        }
    }
        
    return true;
}

/*
* Move hero 1 unit right
*/
void Engine::moveHeroRight()
{
    heroDirection = FACING_EAST;
    
    // If we are at the right edge of the map, load the area to the east if possible.
    if (heroPositionX + hero->getWidth() >= GRID_WIDTH && !heroIsMoving)
    {
        if (currentArea->canMoveEast())
        {
            loadArea(currentArea->getEast());
            Point startingPoint = currentArea->getEntryWest();
            heroPositionX = startingPoint.x;
            heroPositionY = startingPoint.y;
        }
    }
    else if (!heroIsMoving)
    {
        heroIsMoving = true;
        glutTimerFunc(0, heroMovementTimerDispach, FACING_EAST);
        soundManager->playSound(STEP);
    }
}

/*
* Move hero 1 unit left
*/
void Engine::moveHeroLeft()
{
    heroDirection = FACING_WEST;
    
    // If we are at the left edge of the map, load the area to the west if possible.
    if (heroPositionX <= 0 && !heroIsMoving)
    {
        if (currentArea->canMoveWest())
        {
            loadArea(currentArea->getWest());
            Point startingPoint = currentArea->getEntryEast();
            heroPositionX = startingPoint.x;
            heroPositionY = startingPoint.y;
        }
    }
    else if (!heroIsMoving)
    {
        heroIsMoving = true;
        glutTimerFunc(0, heroMovementTimerDispach, FACING_WEST);
        soundManager->playSound(STEP);
    }
}

/*
* Move hero 1 unit up
*/
void Engine::moveHeroUp()
{
    heroDirection = FACING_NORTH;
    
    // If we are at the top edge of the map, load the area to the north if possible.
    if (heroPositionY + hero->getHeight() >= GRID_HEIGHT && !heroIsMoving)
    {
        if (currentArea->canMoveNorth())
        {
            loadArea(currentArea->getNorth());
            Point startingPoint = currentArea->getEntrySouth();
            heroPositionX = startingPoint.x;
            heroPositionY = startingPoint.y;
        }
    }
    else if (!heroIsMoving)
    {
        heroIsMoving = true;
        soundManager->playSound(STEP);
        glutTimerFunc(0, heroMovementTimerDispach, FACING_NORTH);
    }
}

/*
* Move hero 1 unit down
*/
void Engine::moveHeroDown()
{
    heroDirection = FACING_SOUTH;
    
    // If we are at the bottom edge of the map, load the area to the south if possible.
    if (heroPositionY <= 0 && !heroIsMoving)
    {
        if (currentArea->canMoveSouth())
        {
            loadArea(currentArea->getSouth());
            Point startingPoint = currentArea->getEntryNorth();
            heroPositionX = startingPoint.x;
            heroPositionY = startingPoint.y;
        }
    }
    else if (!heroIsMoving)
    {
        heroIsMoving = true;
        soundManager->playSound(STEP);
        glutTimerFunc(0, heroMovementTimerDispach, FACING_SOUTH);
    }
}

/*
* Hero movement animation timer
*/
void Engine::heroMovementTimer (int value)
{
    switch (value)
    {
        case FACING_EAST:
            
            if (heroAnimationX < HERO_MOVEMENT_AMOUNT - HERO_MOVEMENT_DISTANCE)
            {
                heroAnimationX += HERO_MOVEMENT_DISTANCE;
                
                if (heroAnimationX >= HERO_MOVEMENT_AMOUNT / 3.0)
                {
                    heroStance = nextStance;
                }
                
                glutTimerFunc (HERO_MOVEMENT_DELAY, heroMovementTimerDispach, value);
            }
            else
            {
                nextStance = ( heroStance == LEFT_STANCE ? RIGHT_STANCE : LEFT_STANCE);
                heroStance = NORMAL_STANCE;
                heroPositionX++;
                heroIsMoving = false;
                heroAnimationX = 0;
            }
            break;
        
        case FACING_WEST:
            
            if (-heroAnimationX < HERO_MOVEMENT_AMOUNT - HERO_MOVEMENT_DISTANCE)
            {
                heroAnimationX -= HERO_MOVEMENT_DISTANCE;
                
                if (-heroAnimationX >= HERO_MOVEMENT_AMOUNT / 3.0)
                {
                    heroStance = nextStance;
                }
                
                glutTimerFunc (HERO_MOVEMENT_DELAY, heroMovementTimerDispach, value);
            }
            else
            {
                nextStance = ( heroStance == LEFT_STANCE ? RIGHT_STANCE : LEFT_STANCE);
                heroStance = NORMAL_STANCE;
                heroPositionX--;
                heroIsMoving = false;
                heroAnimationX = 0;
            }
            break;
        
        case FACING_NORTH:
            
            if (heroAnimationY < HERO_MOVEMENT_AMOUNT - HERO_MOVEMENT_DISTANCE)
            {
                heroAnimationY += HERO_MOVEMENT_DISTANCE;
                
                if (heroAnimationY >= HERO_MOVEMENT_AMOUNT / 3.0)
                {
                    heroStance = nextStance;
                }
                
                glutTimerFunc (HERO_MOVEMENT_DELAY, heroMovementTimerDispach, value);
            }
            else
            {
                nextStance = ( heroStance == LEFT_STANCE ? RIGHT_STANCE : LEFT_STANCE);
                heroStance = NORMAL_STANCE;
                heroPositionY++;
                heroIsMoving = false;
                heroAnimationY = 0;
            }
            break;
        
        case FACING_SOUTH:
            
            if (-heroAnimationY < HERO_MOVEMENT_AMOUNT - HERO_MOVEMENT_DISTANCE)
            {
                heroAnimationY -= HERO_MOVEMENT_DISTANCE;
                
                if (-heroAnimationY >= HERO_MOVEMENT_AMOUNT / 3.0)
                {
                    heroStance = nextStance;
                }
                
                glutTimerFunc (HERO_MOVEMENT_DELAY, heroMovementTimerDispach, value);
            }
            else
            {
                nextStance = ( heroStance == LEFT_STANCE ? RIGHT_STANCE : LEFT_STANCE);
                heroStance = NORMAL_STANCE;
                heroPositionY--;
                heroIsMoving = false;
                heroAnimationY = 0;
            }
            break;
    }
    
    glutPostRedisplay();
}

/*
* Process normal keyboard inputs
*/
void Engine::processNormalKeys(unsigned char key, int x, int y)
{
    
	switch (key)
	{
        // Equivalent to pressing Left arrow key
		case 'a':
		case 'A':
            if(inBattle)
            {
                
            }
            else
            {
                if (!displaySpeech &&canHeroMoveLeft())
                {
                   moveHeroLeft();
                }
            }
			break;
			
        // Equivalent to pressing Right arrow key
		case 'd':
		case 'D':
            if(inBattle)
            {
                
            }
            else
            {
                if (!displaySpeech && canHeroMoveRight())
                {
                   moveHeroRight();
                }
            }
			break;
			
        // Equivalent to pressing Up arrow key
		case 'w':
		case 'W':
            if(inBattle)
            {
                if(battleArrow != 0)
                {
                    battleArrow--;
                    soundManager->playSound(MENUBEEP);
                }
            }
            else
            {
                if (!displaySpeech && canHeroMoveUp())
                {
                    moveHeroUp();
                }
            }
            break;
			
        // Equivalent to pressing Down arrow key
		case 's':
		case 'S':
            if(inBattle)
            {
                if(battleArrow != 2)
                {
                    battleArrow++;
                    soundManager->playSound(MENUBEEP);
                }
            }
            else
            {
                if (!displaySpeech && canHeroMoveDown())
                {
                   moveHeroDown();
                }
            }
			break;
		case 'b':
        case 'B':
            inBattle = !inBattle;
            if( inBattle )
                soundManager->playBattleMusic();
            else
                soundManager->playMusic();
            break;
		//space bar is pressed
		case 32:
            if(inBattle)
            {
                if(battleArrow == ATTACK)
                {
                    //attack code goes here
                }
                if(battleArrow == HEAL)
                {
                    //heal code goes here
                }
                if(battleArrow == RUN)
                {
                    //run code goes here
                }
            }
            else
            {
                int npcIndex = canHeroInteractWithNPC();
                if (npcIndex != -1)
                {
                    if(!displaySpeech)
                    {
                        if (textDialog != NULL)
                            delete textDialog;
                            
                        // Get the list of possible dialogs for the current NPC.
                        NPC * npc = npcs.at(npcIndex);
                        vector<Dialog> dialogs = npc->getDialogs();
                        
                        for (int i = 0; i < dialogs.size(); i++)
                        {
                            Dialog npcDialog = dialogs.at(i);
                            
                            if ( gameState->isConditionTrue(npcDialog.condition))
                            {
                                textDialog = new TextDialog(npc->getName() + ": " + npcDialog.text);
                                speech = textDialog->getNextDialog();
                                displaySpeech = true;
    
                                break;
                            }
                        }
                    }
                    else
                    {
                        if(textDialog->moreDialogs())
                        {
                            speech = textDialog->getNextDialog();
                        }
                        else
                        {
                            // DO ACTION
                            displaySpeech = false;
                        }
                    }
                }
            }
            break;
    }
    
    glutPostRedisplay();
}

/*
* Process special keyboard inputs (Up, Down, Left, Right, Etc.)
*/
void Engine::processSpecialKeys(int key, int x, int y)
{
    // Redirect arrow keys to their ASDW counterparts in processNormalKeys.
    // This is done to prevent duplication of key-handling logic/code.
    switch(key)
	{
		case GLUT_KEY_RIGHT:
			processNormalKeys('d', x, y);
			break;
		case GLUT_KEY_LEFT:
			processNormalKeys('a', x, y);
			break;
		case GLUT_KEY_UP:
			processNormalKeys('w', x, y);
			break;
		case GLUT_KEY_DOWN:
			processNormalKeys('s', x, y);
			break;
	}
}

/*
* Draws the area background
*/
void Engine::drawAreaBackground()
{
    glBindTexture(GL_TEXTURE_2D, backgroundTexture[0].texID);
    
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f,  0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(DEFAULT_WINDOW_WIDTH, 0.0f,  0.0f);
        glTexCoord2f(1.0f, 2.0f / 3.0f); glVertex3f(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,  0.0f);
        glTexCoord2f(0.0f, 2.0f / 3.0f); glVertex3f(0.0f, DEFAULT_WINDOW_HEIGHT,  0.0f);
    glEnd();
}

/*
* Draws all NPCs in the current area below the hero
*/
void Engine::drawNPCsBelowHero()
{
    // Make sure the number of npcTextures we have corresponds to the number
    // of NPCs that are actually in the scene.
    if (npcTextures.size() != npcs.size())
    {
        return;
    }
    
    for (int i = 0; i < npcTextures.size(); i++)
    {
        NPC * npc = npcs.at(i);
        Point npcPosition = npc->getLocation();
        
        if (npcPosition.y  >= heroPositionY)
        {
                continue;
        }
        
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
    	
    	
    	glLoadIdentity();
    	
    	gluOrtho2D(0.0, GRID_WIDTH, 0.0, GRID_HEIGHT);
    
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glBindTexture(GL_TEXTURE_2D, npcTextures.at(i).texID);
        
        int width = npc->getWidth();
        int height = npc->getHeight();
        
    	glBegin(GL_POLYGON);
    	   glTexCoord2f(0.0f, 0.0f);
    		glVertex2f(npcPosition.x, npcPosition.y);
    		glTexCoord2f(1.0f, 0.0f);
    		glVertex2f(npcPosition.x + width, npcPosition.y);
    		glTexCoord2f(1.0f, 1.0f);
    		glVertex2f(npcPosition.x + width, npcPosition.y + height);
    		glTexCoord2f(0.0f, 1.0f);
    		glVertex2f(npcPosition.x, npcPosition.y + height);
    	glEnd();
    
        glMatrixMode(GL_PROJECTION);
    	glPopMatrix(); 
    }
}

/*
* Draws all NPCs in the current area above the hero
*/
void Engine::drawNPCsAboveHero()
{
    // Make sure the number of npcTextures we have corresponds to the number
    // of NPCs that are actually in the scene.
    if (npcTextures.size() != npcs.size())
    {
        return;
    }
    
    for (int i = 0; i < npcTextures.size(); i++)
    {
        NPC * npc = npcs.at(i);
        Point npcPosition = npc->getLocation();
        
        if (npcPosition.y  < heroPositionY)
        {
                continue;
        }
        
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
    	
    	
    	glLoadIdentity();
    	
    	gluOrtho2D(0.0, GRID_WIDTH, 0.0, GRID_HEIGHT);
    
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glBindTexture(GL_TEXTURE_2D, npcTextures.at(i).texID);
        
        int width = npc->getWidth();
        int height = npc->getHeight();
        
    	glBegin(GL_POLYGON);
    	   glTexCoord2f(0.0f, 0.0f);
    		glVertex2f(npcPosition.x, npcPosition.y);
    		glTexCoord2f(1.0f, 0.0f);
    		glVertex2f(npcPosition.x + width, npcPosition.y);
    		glTexCoord2f(1.0f, 1.0f);
    		glVertex2f(npcPosition.x + width, npcPosition.y + height);
    		glTexCoord2f(0.0f, 1.0f);
    		glVertex2f(npcPosition.x, npcPosition.y + height);
    	glEnd();
    
        glMatrixMode(GL_PROJECTION);
    	glPopMatrix(); 
    }
}

/*
* Draws the hero
*/
void Engine::drawHero()
{
    
    // To draw the hero, as with all characters, use the Grid system as our
    // 2D orthogonal view (since we deal with the grid when drawing characters,
    // not actual pixel dimentions.)
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
	
	
	glLoadIdentity();
	
	gluOrtho2D(0.0, GRID_WIDTH, 0.0, GRID_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // The hero's direction and footing determines which texture we shall use.
    // There are 12 possible textures, stored in the heroTextures array.
    switch (heroDirection)
    {
        case FACING_SOUTH:
            
            switch (heroStance)
            {
                case NORMAL_STANCE:
                    glBindTexture(GL_TEXTURE_2D, heroTextures[0].texID);
                    break;
                case RIGHT_STANCE:
                    glBindTexture(GL_TEXTURE_2D, heroTextures[1].texID);
                    break;
                case LEFT_STANCE:
                    glBindTexture(GL_TEXTURE_2D, heroTextures[2].texID);
                    break;
            }
            break;
            
        case FACING_NORTH:
            
            switch (heroStance)
            {
                case NORMAL_STANCE:
                    glBindTexture(GL_TEXTURE_2D, heroTextures[3].texID);
                    break;
                case RIGHT_STANCE:
                    glBindTexture(GL_TEXTURE_2D, heroTextures[4].texID);
                    break;
                case LEFT_STANCE:
                    glBindTexture(GL_TEXTURE_2D, heroTextures[5].texID);
                    break;
            }
            break;
            
        case FACING_EAST:
            
            switch (heroStance)
            {
                case NORMAL_STANCE:
                    glBindTexture(GL_TEXTURE_2D, heroTextures[6].texID);
                    break;
                case RIGHT_STANCE:
                    glBindTexture(GL_TEXTURE_2D, heroTextures[7].texID);
                    break;
                case LEFT_STANCE:
                    glBindTexture(GL_TEXTURE_2D, heroTextures[8].texID);
                    break;
            }
            break;
            
        case FACING_WEST:
            
            switch (heroStance)
            {
                case NORMAL_STANCE:
                    glBindTexture(GL_TEXTURE_2D, heroTextures[9].texID);
                    break;
                case RIGHT_STANCE:
                    glBindTexture(GL_TEXTURE_2D, heroTextures[10].texID);
                    break;
                case LEFT_STANCE:
                    glBindTexture(GL_TEXTURE_2D, heroTextures[11].texID);
                    break;
            }
            break;
    }

	glBegin(GL_POLYGON);
	   glTexCoord2f(0.0f, 0.0f);
		glVertex2f(heroPositionX + heroAnimationX, heroPositionY + heroAnimationY);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(heroPositionX + heroAnimationX + hero->getWidth(), heroPositionY + heroAnimationY);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(heroPositionX + heroAnimationX + hero->getWidth(), heroPositionY + heroAnimationY + hero->getHeight());
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(heroPositionX + heroAnimationX, heroPositionY + heroAnimationY + hero->getHeight());
	glEnd();

    glMatrixMode(GL_PROJECTION);
	glPopMatrix(); 
}

void Engine::drawHUD()
{
    //display the score
	std::stringstream ss;
	std::string str;
	ss << hero->getRemainingHitPoints() << "/" << hero->getTotalHitPoints();
	ss >> str;
	char health[9];
	strcpy( health, str.c_str() );
	glColor3f( 1.0, 1.0, 1.0 );
	drawString(DEFAULT_WINDOW_WIDTH - 70, DEFAULT_WINDOW_HEIGHT - 20, GLUT_BITMAP_TIMES_ROMAN_24, "Life:");
	drawString(DEFAULT_WINDOW_WIDTH - 70, DEFAULT_WINDOW_HEIGHT - 50, GLUT_BITMAP_TIMES_ROMAN_24, health);
}

void Engine::drawSpeechBox()
{
    
    glDisable(GL_TEXTURE_2D);
    //first draw the backround box
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f,  0.0f);
        glVertex3f(DEFAULT_WINDOW_WIDTH, 0.0f,  0.0f);
        glVertex3f(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT / 5,  0.0f);
        glVertex3f(0.0f, DEFAULT_WINDOW_HEIGHT / 5,  0.0f);
    glEnd();
    char speechChar[100];
	
    glEnable(GL_TEXTURE_2D);
    vector<string> words;
    vector<string> lines;
      Parser::tokenize(speech, words);

    int currLine = 0;
    int currNumChars;
    int LINE_LENGTH = 90; //length of line in chars
    int LINE_HEIGHT = 25;
    
    string line;
    for( int word = 0; word < words.size(); word++ )
    {
        if( line.length() + words[word].length() > LINE_LENGTH )
        {
            currLine++;
            lines.push_back(line);
            line = "";
        }
        line.append(" ");
        line.append(words[word]);
    }
    lines.push_back(line);
    glColor3f(1.0, 1.0, 1.0);
    for( int i = 0; i < lines.size(); i++ )
    {
        char speechChar[100];
        strcpy( speechChar, lines[i].c_str() );
        drawString(10.0f, DEFAULT_WINDOW_HEIGHT / 5 - LINE_HEIGHT * (i + 1), GLUT_BITMAP_TIMES_ROMAN_24,speechChar );
    }
    
    
}

//draw the battle system menu
void Engine::drawBattleMenu()
{
    
    //first draw the backround box
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f,  0.0f);
        glVertex3f(DEFAULT_WINDOW_WIDTH, 0.0f,  0.0f);
        glVertex3f(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT / 5,  0.0f);
        glVertex3f(0.0f, DEFAULT_WINDOW_HEIGHT / 5,  0.0f);
    glEnd();
    char speechChar[100];
	
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 1.0);
    //draw the 3 menu options
    drawString(30.0f, DEFAULT_WINDOW_HEIGHT / 5 - LINE_HEIGHT, GLUT_BITMAP_TIMES_ROMAN_24, "Attack" );
    drawString(30.0f, DEFAULT_WINDOW_HEIGHT / 5 - LINE_HEIGHT * 2, GLUT_BITMAP_TIMES_ROMAN_24, "Heal" );
    drawString(30.0f, DEFAULT_WINDOW_HEIGHT / 5 - LINE_HEIGHT * 3, GLUT_BITMAP_TIMES_ROMAN_24, "Run" );
    
    
    //draw the arrow
    
    glDisable(GL_TEXTURE_2D);
    
    glBegin(GL_POLYGON);
		glVertex2f(18.0f, DEFAULT_WINDOW_HEIGHT / 5 - LINE_HEIGHT + 1.0 - battleArrow * LINE_HEIGHT);
		glVertex2f(25.0f, DEFAULT_WINDOW_HEIGHT / 5 - LINE_HEIGHT / 2 - battleArrow * LINE_HEIGHT);
		glVertex2f(18.0f, DEFAULT_WINDOW_HEIGHT / 5 - 1.0 - battleArrow * LINE_HEIGHT);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(18.0f, DEFAULT_WINDOW_HEIGHT / 5 - LINE_HEIGHT / 3 - battleArrow * LINE_HEIGHT);
		glVertex2f(6.0f, DEFAULT_WINDOW_HEIGHT / 5 - LINE_HEIGHT / 3 - battleArrow * LINE_HEIGHT);
		glVertex2f(6.0f, DEFAULT_WINDOW_HEIGHT / 5 - LINE_HEIGHT * 2/3 - battleArrow * LINE_HEIGHT);
		glVertex2f(18.0f, DEFAULT_WINDOW_HEIGHT / 5 - LINE_HEIGHT * 2/3 - battleArrow * LINE_HEIGHT);
	glEnd();
	glEnable(GL_TEXTURE_2D);
}



//this is a method to make the output of strings much simpler
void Engine::drawString(float x, float y, void *font, char *string)
{  
    
	glDisable(GL_TEXTURE_2D);
	char *currChar;
	glRasterPos2f(x, y);
	//loop through the string and output each char
	for (currChar=string; *currChar; currChar++) 
	{
		glutBitmapCharacter(font, *currChar);
	}
	glEnable(GL_TEXTURE_2D);
        
}

/*
*	The main display function.
*/
void Engine::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if( !inBattle )
	{
        // Draw Background
    	drawAreaBackground();
    	
        // Draw NPCs above hero
        drawNPCsAboveHero();
    
        // Draw hero
        drawHero();
        
    	// Draw NPCs below hero
    	drawNPCsBelowHero();
        
        //Draw the heads up disply
        drawHUD();
        
        //display the speech box
        if( displaySpeech )
        {
            drawSpeechBox();
        }
    }
    if( inBattle )
    {
        drawBattleMenu();
    }

	glutSwapBuffers();
}

/*
* Initialize OpenGl configuration
*/
void Engine::initializeOpenGLSettings()
{
    // Colour to clear frame buffer with
    glClearColor(0.0, 0.0, 0.0, 0.0);

	// Enable alpha channel blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Enable texture mapping
	glEnable(GL_TEXTURE_2D);
	
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

/*
* Initialize OpenGl projection settings
*/
void Engine::initializeOpenGLProjectionSettings()
{
    // Set projection mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, DEFAULT_WINDOW_WIDTH, 0.0, DEFAULT_WINDOW_HEIGHT);
	
	// Set model view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
* Initialize OpenGL callback functions
*/
void Engine::initializeOpenGLCallbacks()
{
	glutKeyboardFunc( processNormalKeysDispach );
	glutSpecialFunc( processSpecialKeysDispach );
	glutMouseFunc(NULL);
	//glutReshapeFunc(reshapeHandler);
	//glutIdleFunc (idleHandler);
}

/*
* Begin engine
*/
void Engine::run(int argc, char** argv)
{
    // Initialize glut
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    
    glutInitWindowSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    glutInitWindowPosition(0, 0);
	glutCreateWindow(GAME_TITLE);
	
    engine_id_to_engine[ENGINE_ID] = this;

	glutDisplayFunc(displayDispach);
	//glutTimerFunc(0, gravityTimer, 1 );

	initializeOpenGLSettings();
	
	initializeOpenGLProjectionSettings();
	
	initializeOpenGLCallbacks();
	
	if (!loadTextures())
	{
       return;
    }
    
    loadAreaMask();
    
    soundManager->playMusic();

	glutMainLoop();
}
