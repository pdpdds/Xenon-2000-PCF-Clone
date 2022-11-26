//#include "ProjectileComponent.h"
//
//ProjectileComponent::ProjectileComponent(int range, int speed)
//{
//	m_range = range;
//	m_speed = speed;
//}
//
//ProjectileComponent::~ProjectileComponent()
//{
//	
//}
//
//void ProjectileComponent::Init()
//{
//	m_transformComponent = &entity->GetComponent<TransformComponent>();
//}
//
//void ProjectileComponent::Update()
//{
//	m_distance += m_speed;
//
//	//If the distance traveled is greater than the projectile range, destroy the projectile
//	if (m_distance > m_range)
//	{
//		entity->Destroy();
//	}
//
//	
//
//	//TODO: Destroy projectile when out of bounds
//}
//
