#include "Pawn.h"
#include "GameEngine.h"
#include <iostream>
#include "GameObjects.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "PlayerController.h"
#include "GroupLabels.h"

Pawn::Pawn()
{
	Start();
}

void Pawn::Start()
{
	auto& m_player = GameEngine::manager.AddEntity();

	m_player.AddComponent<TransformComponent>(0, 0);
	m_player.AddComponent<SpriteComponent>("../Assets/graphics/Ship2.bmp", false);
	m_player.AddComponent<PlayerController>();

	std::cout << "Pawn Initialized" << std::endl;
	std::cout << "Pawn test" << std::endl;
}
