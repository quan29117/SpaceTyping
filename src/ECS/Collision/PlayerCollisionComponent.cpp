/*******************************************************************//*
 * Implementation of the PlayerCollisionComponent class.
 *
 *********************************************************************/

#include <headers/ECS/Collision/PlayerCollisionComponent.hpp>

#include <headers/ECS/Text/TextComponent.hpp>
#include <headers/ApplicationState/PlayState.hpp>

PlayerCollisionComponent::PlayerCollisionComponent(const Vector2D& destSize) {
    m_collision.w = destSize.x;
    m_collision.h = destSize.y;
}

PlayerCollisionComponent::~PlayerCollisionComponent() {
    
}

void PlayerCollisionComponent::init() {
//Transform reference
    if (entity->hasComponent<TransformComponent>()) {
        transform = &entity->getComponent<TransformComponent>();
        m_collision.x = transform->getPosition().x;
        m_collision.y = transform->getPosition().y;
    }
    else std::cout << "No TransformComponent in Player\n";

//Progress reference
    if (entity->hasComponent<ProgressComponent>())
        progress = &entity->getComponent<ProgressComponent>();
    else std::cout << "No ProgressComponent in Player\n";
}

void PlayerCollisionComponent::onHit(const CollisionID& id) {}

void PlayerCollisionComponent::onHitP(const int& cnt) {
    progress->decreaseScore(cnt * 10);
    progress->increaseWT(cnt);
}

