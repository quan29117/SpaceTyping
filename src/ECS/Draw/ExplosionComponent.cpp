/*******************************************************************//*
 * Implementation of the ExplosionComponent class.
 *
 *********************************************************************/

#include <headers/ECS/Draw/ExplosionComponent.hpp>

#include <headers/ApplicationManager/ExplosionManager.hpp>

ExplosionComponent::ExplosionComponent() {}

ExplosionComponent::~ExplosionComponent() {}

void ExplosionComponent::init() {
    if (entity->hasComponent<TransformComponent>()) {
        transform = &entity->getComponent<TransformComponent>();
    }
    else std::cout << "No TransformComponent\n";
}

void ExplosionComponent::update() {
    if (!entity->isAlive())
        ExplosionManager::createExplosion(transform->getPosition());
}

void ExplosionComponent::render() {}
            
