#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

//ID is size_t
using ComponentID = std::size_t;

//func put into place wherever used
inline ComponentID getComponentTypeID() {
	//static so counts
	static ComponentID lastID = 0;
	return lastID++;
}

//so the same type has the same ID each time
template <typename T>
inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

//See if object has this component
using ComponentBitSet = std::bitset<maxComponents>;
//See how many/which components the object has
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public: 
	Entity * entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	
	virtual ~Component() {}
};

class Entity {

private:
	bool active = true;
	//dynamic size array
	std::vector < std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void update() {

		//for all components, update
		for (auto& c : components) c->update();
		

	}
	void draw() {
		for (auto& c : components) c->draw();
	}
	bool isActive() const { return active; }

	void destroy() { active = false; }

	template <typename T> 
	bool hasComponent() const {
		return componentBitSet[getComponentID<T>];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T> 
	T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
		//example as can used
		//gameObject.getComponent<PositionComponent>().setXPos(25);
	}
};

class Manager {
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update() {
		for (auto& e : entities) e->update();
	}
	void draw() {
		for (auto& e : entities) e->draw();
	}
	//remove entities at each frame as needed
	void refresh() {
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
			[](const std::unique_ptr<Entity> &mEntity) 
		//the remove_if function
		{
			return !mEntity->isActive();
		}),
		std::end(entities));

	}

	Entity& addEntity() {
		Entity* e = new Entity();
		//initialize the ptr to e
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};