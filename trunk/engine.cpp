/*
* Engine.cpp
*/

#include "common.h"
#include "engine.h"

#include <iostream>

/***************************************
* Class Engine
***************************************/

// Static variables need to be 'implemented' here to preferent undefined reference
std::map<int, Engine*> Engine::engine_id_to_engine;
const int Engine::ENGINE_ID;

/*
* Default constructor
*/
Engine::Engine()
{
    heroPositionX = 0;
    heroPositionY = 0;
    heroDirection = FACING_EAST;
    
    // Create hero
    hero = new Hero("Hero", 1, "heropicture.bmp");
    
    // Create area
    currentArea = new Area();
    Parser::getArea(currentArea, "1");
    
}

/*
* Default destructor
*/
Engine::~Engine()
{
    delete hero;
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
    if (!loadTGA(&textures[0], currentArea->getMainTexture()))
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
* Determine if hero can move right
*/
bool Engine::canHeroMoveRight()
{
    /*
    heroPositionX = 0;
    heroPositionY = 0;
    GRID_WIDTH
    GRID_HEGIHT
    hero->getWidth()
    hero->getHeight()
    */
    
    // We've hit the right edge of the map
    if (heroPositionX + hero->getWidth() >= GRID_WIDTH)
        return false; 
    
    // The grid block to the right is solid, cannot walk past it.
    int newRightPosition = heroPositionX + hero->getWidth();
    if ((int)(mask.pix1d (newRightPosition, GRID_HEIGHT - heroPositionY - 1, 0, 0)) <= 0)
        return false; 
    
    return true;
}

/*
* Determine if hero can move left
*/
bool Engine::canHeroMoveLeft()
{
    // We've hit the left edge of the map
    if (heroPositionX <= 0)
        return false; 
        
    // The grid block to the left is solid, cannot walk past it.
    int newLeftPosition = heroPositionX - 1;
    if ((int)(mask.pix1d (newLeftPosition, GRID_HEIGHT - heroPositionY - 1, 0, 0)) <= 0)
        return false; 
    
    return true;
}

/*
* Determine if hero can move up
*/
bool Engine::canHeroMoveUp()
{
    // We've hit the top edge of the map
    if (heroPositionY + hero->getHeight() >= GRID_HEIGHT)
        return false; 
        
    // The grid block above is solid, cannot walk past it.
    int newUpPosition = heroPositionY + 1;
    if ((int)(mask.pix1d (heroPositionX, GRID_HEIGHT - newUpPosition - 1, 0, 0)) <= 0)
        return false; 
        
    return true;
}

/*
* Determine if hero can move down
*/
bool Engine::canHeroMoveDown()
{
    // We've hit the bottom edge of the map
    if (heroPositionY <= 0)
        return false; 
        
    // The grid block below is solid, cannot walk past it.
    int newDownPosition = heroPositionY - 1;
    if ((int)(mask.pix1d (heroPositionX, GRID_HEIGHT - newDownPosition - 1, 0, 0)) <= 0)
        return false; 
        
    return true;
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
            if (canHeroMoveLeft())
            {
                heroPositionX--;
            }
			break;
			
        // Equivalent to pressing Right arrow key
		case 'd':
		case 'D':
            if (canHeroMoveRight())
            {
                heroPositionX++;
            }
			break;
			
        // Equivalent to pressing Up arrow key
		case 'w':
		case 'W':
            if (canHeroMoveUp())
            {
                heroPositionY++;
            }
            break;
			
        // Equivalent to pressing Down arrow key
		case 's':
		case 'S':
            if (canHeroMoveDown())
            {
                heroPositionY--;
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
    glBindTexture(GL_TEXTURE_2D, textures[0].texID);
    
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f,  0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(DEFAULT_WINDOW_WIDTH, 0.0f,  0.0f);
        glTexCoord2f(1.0f, 2.0f / 3.0f); glVertex3f(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,  0.0f);
        glTexCoord2f(0.0f, 2.0f / 3.0f); glVertex3f(0.0f, DEFAULT_WINDOW_HEIGHT,  0.0f);
    glEnd();
}

/*
* Draws the hero
*/
void Engine::drawHero()
{
    glColor3f(1.0, 1.0, 1.0); // Temp
    // Texure will depend on heroDirection state. (east, west, etc.)
    
    // To draw the hero, as with all characters, use the Grid system as our
    // 2D orthogonal view (since we deal with the grid when drawing characters,
    // not actual pixel dimentions.)
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	gluOrtho2D(0.0, GRID_WIDTH, 0.0, GRID_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glBegin(GL_POLYGON);
		glVertex2f(heroPositionX, heroPositionY);
		glVertex2f(heroPositionX, heroPositionY + hero->getHeight());
		glVertex2f(heroPositionX + hero->getWidth(), heroPositionY + hero->getHeight());
		glVertex2f(heroPositionX + hero->getWidth(), heroPositionY);
	glEnd();

    glMatrixMode(GL_PROJECTION);
	glPopMatrix(); 
}

/*
*	The main display function.
*/
void Engine::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Draw Background
	drawAreaBackground();

    // Draw hero
    drawHero();

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
	
	glShadeModel(GL_SMOOTH);
	
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

	glutMainLoop();
}
