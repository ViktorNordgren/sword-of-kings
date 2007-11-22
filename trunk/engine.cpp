/*
* Engine.cpp
*/

#include <GL/glut.h>

#include "common.h"
#include "hero.h"
#include "engine.h"

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
}

/*
* Default destructor
*/
Engine::~Engine()
{
    delete hero;
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
			heroPositionX--;
			break;
			
        // Equivalent to pressing Right arrow key
		case 'd':
		case 'D':
			heroPositionX++;
			break;
			
        // Equivalent to pressing Up arrow key
		case 'w':
		case 'W':
			heroPositionY++;
			break;
			
        // Equivalent to pressing Down arrow key
		case 's':
		case 'S':
			heroPositionY--;
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
	glClear(GL_COLOR_BUFFER_BIT);

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

	glutMainLoop();
}
