/*******************************************************************//*
 * Core component bag class for Entity Component System (ECS).
 * Including EntityManager class, Entity class and Component Class
 * 
 * Reference: https://viblo.asia/p/entity-component-system-la-gi-oOVlYLPBZ8W
 *********************************************************************/

#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class EntityManager;

enum EntityGroup : short {
	GEnemy,
	GBulletPlayer_B,	//BulletPlayer to defeat BulletEnemy
	GBulletPlayer_E,	//BulletPlayer to defeat Enemy
	GBulletEnemy,
};

using ComponentID = unsigned short;
using Group = unsigned short;

inline ComponentID getUniqueComponentTypeID() {
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() {
    static_assert (std::is_base_of<Component, T>::value, "Doesn't inherit from Component\n");
    static ComponentID typeID = getUniqueComponentTypeID();
    return typeID;
}

constexpr unsigned short maxComponents = 16;
using ComponentBitSet = std::bitset <maxComponents>;
using ComponentArray = std::array <Component*, maxComponents>;

constexpr unsigned short maxGroups = 16;
using GroupBitSet = std::bitset <maxGroups>;

//Abstract Component class
class Component {
private:


public:
    Entity* entity;

    Component() {}
    virtual ~Component() {}

    virtual void init()   = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};

class Entity {
private:
    EntityManager& manager;

    bool alive;
    std::vector <std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;

    GroupBitSet groupBitSet;

public:
    Entity(EntityManager& man);
    virtual ~Entity();

    bool isAlive();
    EntityManager& getManager();

    void destroy();
    void update();
    void render();

    template <typename T>
    bool hasComponent() {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs... mArgs) {
        T* comp = new T (std::forward<TArgs> (mArgs)...);
        comp->entity = this;
        std::unique_ptr<Component> uPtr {comp};
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = comp;
        componentBitSet[getComponentTypeID<T>()] = true;

        comp->init();

        return *comp;
    }

    template <typename T>
    T& getComponent() {
        auto ptr (componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*> (ptr);
    }

    bool hasGroup(const Group& mGroup);
    void addGroup(const Group& mGroup);
    void delGroup(const Group& mGroup);
};

class EntityManager {
private:
    std::vector <std::unique_ptr<Entity>> entities;
    std::array <std::vector<Entity*>, maxGroups> groupedEntities;

public:
    void update();
    void render();
    void refresh();

    Entity& addEntity();

    void addToGroup(Entity* mEntity, const Group& mGroup);
    std::vector<Entity*>& getEntitesByGroup(const Group& mGroup);

    void clear();
};