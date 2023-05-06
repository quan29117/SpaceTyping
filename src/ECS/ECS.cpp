#include <headers/ECS/ECS.hpp>
#include <iostream>

//----------------------------------------Entity----------------------------------------
Entity::Entity(EntityManager& man)
    : manager(man), alive (true)
{}

Entity::~Entity() {}

bool Entity::isAlive() {
    return alive;
}

EntityManager& Entity::getManager() {
    return manager;
}

void Entity::destroy() {
    alive = false;
}

void Entity::update() {
    for (auto& c : components)
        c->update();
}

void Entity::render() {
    for (auto& c : components)
        c->render();
}

bool Entity::hasGroup(const Group& mGroup) noexcept {
    return groupBitSet[mGroup];
}

void Entity::addGroup(const Group& mGroup) noexcept {
    groupBitSet[mGroup] = true;
    manager.addToGroup(this, mGroup);
}

void Entity::delGroup(const Group& mGroup) noexcept {
    groupBitSet[mGroup] = false;
}

//-------------------------------------EntityManager-------------------------------------
void EntityManager::update() {
    for (auto& e : entities)
        e->update();
    this->refresh();
}

void EntityManager::render() {
    for (auto& e : entities)
        e->render();
}

void EntityManager::refresh() {
    for (int i = 0; i < maxGroups; i++) {
        auto& v = groupedEntities[i];

        v.erase(std::remove_if(v.begin(), v.end(),
            [i](Entity* mEntity)
        {
            return !mEntity->isAlive() || !mEntity->hasGroup(i);
        }),
            v.end());
    }

    entities.erase(std::remove_if(entities.begin(), entities.end(),
        [](const std::unique_ptr<Entity> &m_Entity)
    {
        return !m_Entity->isAlive();
    }),
        entities.end());
}

Entity& EntityManager::addEntity() {
    Entity* e = new Entity(*this);
    std::unique_ptr<Entity> uPtr {e};
    entities.emplace_back(std::move(uPtr));
    return *e;
}

void EntityManager::addToGroup(Entity* mEntity, const Group& mGroup) {
    groupedEntities[mGroup].emplace_back(mEntity);
}

std::vector<Entity*>& EntityManager::getEntitesByGroup(const Group& mGroup) {
    return groupedEntities[mGroup];
}