#include "Player.h"
#include "GameEngine.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "PlayerController.h"
#include "Vector2D.h"
#include "GroupLabels.h"

Player::Player()
{
	Init();
}

void Player::Init()
{
	__super::Init();
	
	auto& m_player = GameEngine::manager.AddEntity();

	m_player.AddComponent<TransformComponent>(0, 0);
	m_player.AddComponent<SpriteComponent>("../Assets/graphics/Ship2.bmp", false);
	m_player.AddComponent<PlayerController>();
	m_player.AddGroup(Groups::GROUP_PLAYERS);

}
