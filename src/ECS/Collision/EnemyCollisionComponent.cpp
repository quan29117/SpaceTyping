/*******************************************************************//*
 * Implementation of the EnemyCollisionComponent class.
 *
 *********************************************************************/

#include <headers/ECS/Collision/EnemyCollisionComponent.hpp>

#include <headers/ApplicationState/PlayState.hpp>

EnemyCollisionComponent::EnemyCollisionComponent(const Vector2D& destSize) {
    m_collision.w = destSize.x;
    m_collision.h = destSize.y;
}

EnemyCollisionComponent::~EnemyCollisionComponent() {
    std::cout << "Delete enemy\n";
}

void EnemyCollisionComponent::init() {
//Transform reference
    if (entity->hasComponent<TransformComponent>()) {
        transform = &entity->getComponent<TransformComponent>();
        m_collision.x = transform->getPosition().x;
        m_collision.y = transform->getPosition().y;
    }
    else std::cout << "No TransformComponent in Enemy\n";
//Text reference
    if (entity->hasComponent<EnemyTextComponent>())
        text = &entity->getComponent<EnemyTextComponent>();
    else std::cout << "No TextComponent in Enemy\n";
}

void EnemyCollisionComponent::onHit(const CollisionID& id) {
    switch(id) {
        case player_collision:
            entity->destroy();
            break;

        case BP_E_collision:
            text->Shot();
            break;
        
        default:
            break;
    }    
}

void EnemyCollisionComponent::onHitP(Entity* enemy) {}
