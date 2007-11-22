/*
*
*/

#include <GL/glut.h>

#include <cstdlib>
#include <iostream>
using namespace std;

#include "engine.h"

int main(int argc, char** argv)
{
    cout << "Test" << endl;
    
    Engine * engine = new Engine();
    
    engine->init(argc, argv);
    
    /*    
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);
	glutWindowID = glutCreateWindow("Sword of Kings");

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 1 );

	init();

	glutMainLoop();
    */

    return 0;
}
