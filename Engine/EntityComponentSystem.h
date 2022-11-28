#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Pawn;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

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

public:
	~Component()
	{
		Destroy();
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

class GameObject
{
public:
	Entity* m_entity;

	virtual void Start() {}
	virtual void Update() {}
};

class Entity
{
private:
	Manager* m_manager = nullptr;
	bool m_isActive = true;
	std::vector<std::unique_ptr<Component>> m_components;

	ComponentArray m_componentArray;
	ComponentBitSet m_componentBitSet;
	GroupBitSet m_groupBiset;

public:
	Entity() = default;
	Entity(Manager* manager) : m_manager(manager) {}
	~Entity()
	{
		Destroy();
	}

	virtual void Init() 
	{
		for (int i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Init();
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Update();
		}

		RefreshComponents();
	}

	virtual void Draw() 
	{
		for (int i = 0; i < m_components.size(); ++i)
		{
			m_components[i]->Draw();
		}
	}

	void RefreshComponents()
	{
		m_components.erase(std::remove_if(std::begin(m_components), std::end(m_components),
			[](const std::unique_ptr<Component>& mComponent)
			{
				return !mComponent->IsActive();
			}),
			std::end(m_components));
	}

	//void Instantiate(Entity& entity, class Vector2D position);
	
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

	//Check if entity has group
	bool HasGroup(Group group) { return m_groupBiset[group]; }

	//Add self to the group
	void AddGroup(Group group);

	//Remove from  group bitset
	void DeleteGroup(Group group) { m_groupBiset[false]; }

	//Check if entity has components
	template <typename T> bool HasComponent() const
	{;
	return m_componentBitSet[GetComponentTypeID<T>];
	}

	//Add Component
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

		delete c;
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
		m_entities.clear();
	}

	void Init()
	{
		for (int i = 0; i < m_entities.size(); ++i)
		{
			m_entities[i]->Init();
		}
	}

	void Update()
	{
		for (int i = 0; i < m_entities.size(); ++i) 
		{
			m_entities[i]->Update();
		}
	}

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
		/*for (auto i(0u); i < maxGroups; i++)
		{
			auto& j(m_groupedEntities[i]);
			j.erase(std::remove_if(std::begin(j), std::end(j),
				[i](Entity* mEntity)
				{
					return !mEntity->IsActive() || !mEntity->HasGroup(i);
				}),
				std::end(j));
		}*/

		m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->IsActive();
			}),
			std::end(m_entities));
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

	template <typename T, typename... TArgs> T* CreateEntity(TArgs&& ...mArgs) 
	{
		//T* obj = new T(std::forward(mArgs));
		T* obj(new T(std::forward<TArgs>(mArgs)...));
		std::unique_ptr<Entity> uPtr{ obj };
		m_entities.emplace_back(std::move(uPtr));
		obj->Init();

		return obj;

		delete obj;
	}

};