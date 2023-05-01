#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class EntityManager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getUniqueComponentTypeID() {
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept {
    static_assert (std::is_base_of<Component, T>::value, "Doesn't inherit from Component\n");
    static ComponentID typeID = getUniqueComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
using ComponentBitSet = std::bitset <maxComponents>;
using ComponentArray = std::array <Component*, maxComponents>;

constexpr std::size_t maxGroups = 32;
using GroupBitSet = std::bitset <maxGroups>;

class Component {
public:
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void render() {}

    virtual ~Component() {}
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

    bool hasGroup(const Group& mGroup) noexcept;
    void addGroup(const Group& mGroup) noexcept;
    void delGroup(const Group& mGroup) noexcept;
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
};