#include "GameEngine.h"
#include "Player.h"
#include "LevelManager.h"
#include "Vector2D.h"
#include <iostream>

int main(int argc, char ** argv)
{
    GameEngine engine;

    //Engine Init
    engine.Init("Xenon 2000 - Engenho Irreal 5", 1024, 800, false);

    /*
    * Declare variables / objects here --------------------------
    */
   /* LevelManager lvlManager = LevelManager(&GameEngine::manager);

    Player* player = new Player();

    lvlManager.Instantiate(player, Vector2D(50.f, 50.f));*/

    GameEngine::manager.CreateEntity<Player>();

    /*
    * -------------------------------------------------
    */
     
    //Engine Loop
    engine.Run();

    return 0;
}
