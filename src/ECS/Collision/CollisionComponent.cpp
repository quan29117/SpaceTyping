/*******************************************************************//*
 * Implementation of the CollisionComponent class.
 *
 *********************************************************************/

#include <headers/ECS/Collision/CollisionComponent.hpp>

CollisionComponent::CollisionComponent() {}

CollisionComponent::~CollisionComponent() {}

SDL_FRect CollisionComponent::getHitBox() {
    return m_collision;
}

void CollisionComponent::init() {}

void CollisionComponent::update() {
    m_collision.x = transform->getPosition().x;
    m_collision.y = transform->getPosition().y;
}

void CollisionComponent::render () {}