/*
* Engine.cpp
*/

#include "engine.h"
#include <GL/glut.h>

/*
* Class Engine
*/

/*
* Default constructor
*/
Engine::Engine()
{
}

/*
* Default destructor
*/
Engine::~Engine()
{
}

/*
*	The main display function.
*/
void Engine::display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// DRAW STUFF HERE.

	glutSwapBuffers();
}

/*
* Engine initialization
*/
void Engine::init(int argc, char** argv)
{
    // Initialize glut
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    
    glutInitWindowPosition(0, 0);
	glutCreateWindow("Sword of Kings");

	glutDisplayFunc(display);
	//glutTimerFunc(0, gravityTimer, 1 );

	//init();

	glutMainLoop();
}
