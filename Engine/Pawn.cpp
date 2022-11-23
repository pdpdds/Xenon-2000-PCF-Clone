#include "Pawn.h"
#include "GameEngine.h"
#include <iostream>
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "PlayerController.h"
#include "Vector2D.h"
#include "GroupLabels.h"

Pawn::Pawn()
{
	Init();
}

void Pawn::Init()
{
	/*auto& m_player = GameEngine::manager.AddEntity();

	m_player.AddComponent<TransformComponent>(0, 0);
	m_player.AddComponent<SpriteComponent>("../Assets/graphics/Ship2.bmp", false);
	m_player.AddComponent<PlayerController>();
	m_player.AddGroup(Groups::GROUP_PLAYERS);*/

	std::cout << "Pawn Initialized" << std::endl;
}
