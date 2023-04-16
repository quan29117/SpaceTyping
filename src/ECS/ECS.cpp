#include <headers/ECS/ECS.hpp>
#include <iostream>

//------------------------------------Entity------------------------------------
Entity::Entity() {
    alive = true;
}

Entity::~Entity() {

}

bool Entity::isAlive() {
    return alive;
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

//---------------------------------EntityManager---------------------------------
void EntityManager::update() {
    for (auto& e : entities)
        e->update();
}

void EntityManager::render() {
    for (auto& e : entities)
        e->render();
}

void EntityManager::refresh() {
    entities.erase(std::remove_if(entities.begin(), entities.end(),
        [](const std::unique_ptr<Entity> &m_Entity)
    {
        return m_Entity->isAlive() == false;
    }),
        entities.end());
}

Entity& EntityManager::addEntity() {
    Entity* e = new Entity();
    std::unique_ptr<Entity> uPtr {e};
    entities.emplace_back(std::move(uPtr));
    return *e;
}