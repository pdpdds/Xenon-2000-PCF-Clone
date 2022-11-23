#include "GameEngine.h"
#include "Player.h"
#include <iostream>

int main(int argc, char ** argv)
{
    GameEngine engine;

    engine.Init("Xenon 2000 - Engenho Irreal 5", 1024, 800, false);
    Player* player = new Player();
    engine.Run();
    

    return 0;
}
