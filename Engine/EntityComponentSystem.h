#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <map>

class Component;
class Pawn;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

enum class Tag 
{
	Enemy,
	Player,
	Projectile,
	EnemyProjectile,
	Pickup,
	Asteroid
};

inline ComponentID GetNewComponentTypeID() 
{ 
	static ComponentID lastID = 0u;
	return lastID++;
}


template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetNewComponentTypeID();
	return typeID;
}

//Max components an entity is able to hold
constexpr std::size_t maxComponents = 32;

//Max groups
constexpr std::size_t maxGroups = 32;

/*
* Allows us to check if an entity has a selection of components,
* By generating the bitset and passing it in,
* If it matches the signature of the entity we know that we have all the components needed
*/
using ComponentBitSet = std::bitset <maxComponents>;

using GroupBitSet = std::bitset <maxGroups>;

//Array of Components, length of our max components
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
private:
	bool m_isActive = true;

protected:
	bool m_destroyed = false;

public:
	virtual ~Component()
	{
		
	}

	Entity* entity;

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	//Remove inactive components from the game
	virtual void Destroy()
	{
		m_isActive = false;
	}

	//Check if component is active
	bool IsActive() const
	{
		return m_isActive;
	}
};

class Entity
{
private:
	Manager* m_manager = nullptr;
	bool m_isActive = true;
	std::vector<std::unique_ptr<Component>> m_components;
	std::string m_name;
	Tag m_tag;

	ComponentArray m_componentArray;
	ComponentBitSet m_componentBitSet;
	GroupBitSet m_groupBiset;

public:

	bool m_destroyed = false;

	Entity() = default;

	Entity(Manager* manager) : m_manager(manager) 
	{

	}

	virtual ~Entity()
	{
		
	}

	//Initializes Entity
	virtual void Init() 
	{

		for (int i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Init();
		}
	}

	//Updates Entity and Components
	virtual void Update()
	{
		for (int i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Update();
		}

		RefreshComponents();
	}

	//Draws Entity
	virtual void Draw() 
	{
		for (int i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Draw();
		}
	}

	//Checks for inactive components
	void RefreshComponents()
	{
		m_components.erase(std::remove_if(std::begin(m_components), std::end(m_components),
			[](const std::unique_ptr<Component>& mComponent)
			{
				return !mComponent->IsActive();
			}),
			std::end(m_components));
	}
	
	//Remove inactive entities from the game
	virtual void Destroy() 
	{ 
		m_isActive = false; 

	}

	//Check if entity is active
	bool IsActive() const 
	{ 
		return m_isActive; 
	}

	virtual void BeginOverlap(Entity* otherEntity)
	{

	}

	virtual void EndOverlap(Entity* otherEntity)
	{

	}



	void SetName(std::string inName)
	{
		m_name = inName;
	}

	virtual void TakeDamage(float damage)
	{

	}
	inline std::string GetName() { return m_name; }

	///// Set the entity tag filter for this entity, eg. Tag::Enemy 
	///// @param Player.
	///// @param Enemy.
	///// @param Projectile.
	void SetTag(Tag inTag)
	{
		m_tag = inTag;
	}

	/// Returns the tag of this entity
	inline Tag GetTag() { return m_tag; }


	//Check if entity has group 
	bool HasGroup(Group group) { return m_groupBiset[group]; }

	//Add self to the group
	void AddGroup(Group group);

	//Remove from group bitset
	void DeleteGroup(Group group) { m_groupBiset[false]; }

	//Check if the entity has components
	template <typename T> bool HasComponent() const
	{;
	return m_componentBitSet[GetComponentTypeID<T>];
	}

	//Add New Specified Component
	template <typename T, typename... TArgs> T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		//Add to component vector
		m_components.emplace_back(std::move(uPtr));

		//When we add position component, it will always be put in the same position in the array
		m_componentArray[GetComponentTypeID<T>()] = c;
		m_componentBitSet[GetComponentTypeID<T>()] = true;

		c->Init();

		return *c;
	}

	//Get Component
	template <typename T> T& GetComponent() const 
	{
		//Set pointer to a position in our pointer array
		auto ptr(m_componentArray[GetComponentTypeID<T>()]);

		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> m_entities;
	std::array<std::vector<Entity*>, maxGroups> m_groupedEntities;

public:
	~Manager()
	{

	}

	//Initializes Entities
	void Init()
	{
		for (int i = 0; i < m_entities.size(); ++i)
		{
			m_entities[i]->Init();
		}
	}

	//Updates Entities
	void Update()
	{
		for (int i = 0; i < m_entities.size(); ++i) 
		{
			m_entities[i]->Update();
		}
	}

	//Draws Entities
	void Draw()
	{
		for (int i = 0; i < m_entities.size(); ++i)
		{
			m_entities[i]->Draw();
		}
	}

	//Move through entities and remove ones that don't exist
	void Refresh()
	{
		for (int i = 0; i < m_entities.size(); ++i)
		{
			m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
				[](const std::unique_ptr<Entity>& mEntity)
				{
					return !mEntity->IsActive();
				}),
				std::end(m_entities));
		}
	}
	
	//Add entity to group
	void AddToGroup(Entity* entity, Group group)
	{
		m_groupedEntities[group].emplace_back(entity);
	}

	//List of entities inside a group
	std::vector<Entity*>& GetGroup(Group group)
	{
		return m_groupedEntities[group];
	}

	//Create an Entity and add it to the entities vector
	template <typename T, typename... TArgs> T* CreateEntity(TArgs&& ...mArgs) 
	{
		T* obj(new T(std::forward<TArgs>(mArgs)...));
		std::unique_ptr<Entity> uPtr{ obj };
		m_entities.emplace_back(std::move(uPtr));
		obj->Init();

		return obj;
	}
};