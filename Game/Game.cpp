#include "GameEngine.h"
#include "Player.h"
#include "GameManager.h"
#include "Vector2D.h"
#include <iostream>
#include "Companion.h"

int main(int argc, char ** argv)
{
    GameEngine engine;

    //Engine Init
    engine.Init("Xenon 2000 - Engenho Irreal 5", 1024, 800, false);

    /*
    * Declare variables / objects here --------------------------
    */

	GameManager::GetInstance()->CreateLevel();
    Player* player = GameManager::GetManager()->CreateEntity<Player>();
    GameManager::GetManager()->CreateEntity<Companion>(player);
    

    /*
    * -------------------------------------------------
    */
     
    //Engine Loop
    engine.Run();

    return 0;
}
