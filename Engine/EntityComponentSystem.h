#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID() 
{ 
	static ComponentID lastID = 0;
	return lastID++;
}


template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

//Max components an entity is able to hold
constexpr std::size_t m_maxComponents = 32;

/*
* Allows us to check if an entity has a selection of components,
* By generating the bitset and passing it in,
* If it matches the signature of the entity we know that we have all the components needed
*/
using ComponentBitSet = std::bitset <m_maxComponents>;

//Array of Components, length of our max components
using ComponentArray = std::array<Component*, m_maxComponents>;

class Component
{
public:
	//virtual ~Component();

	Entity* m_entity;

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}
};

class Entity
{
private:
	bool m_isActive = true;
	std::vector<std::unique_ptr<Component>> m_components;

	ComponentArray m_componentArray;
	ComponentBitSet m_componentBitSet;

public:
	void Update()
	{
		//Loop through all of its components and call their update
		for (auto& c : m_components)
		{
			c->Update();
		}
	}

	void Draw() 
	{
		//Loop through all of its components and call their draw functions
		for (auto& c : m_components)
		{
			c->Draw();
		}
	}

	//Remove inactive entities from the game
	void Destroy() { m_isActive = false; }

	bool IsActive() const { return m_isActive; }

	//Check if entity has components
	template <typename T> bool HasComponent() const
	{;
	return m_componentBitSet[GetComponentTypeID<T>];
	}

	//Add Component
	template <typename T, typename... TArgs> T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->m_entity = this;
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

public:
	void Update()
	{
		//Update all entities
		for (auto& e : m_entities)
		{
			e->Update();
		}
	}

	void Draw()
	{
		//Draw all entities
		for (auto& e : m_entities)
		{
			e->Draw();
		}
	}

	//Move through entities and remove ones that don't exist
	void Refresh()
	{
		m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->IsActive();
			}),
			std::end(m_entities));
	}

	//Add Entity
	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		m_entities.emplace_back(std::move(uPtr));

		return *e;
	}
};