/*
*
*/

#include "engine.h"

int main(int argc, char** argv)
{
   
    Engine * engine = new Engine();
    
    engine->run(argc, argv);
    
    delete engine;

    return 0;
}
