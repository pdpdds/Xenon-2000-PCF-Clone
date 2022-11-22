#include "GameEngine.h"
#include <iostream>

int main(int argc, char ** argv)
{
    GameEngine engine;

    engine.Init("Xenon 2000 - Engenho Irreal 5", 1024, 800, false);
    engine.Run();

    

    return 0;
}
