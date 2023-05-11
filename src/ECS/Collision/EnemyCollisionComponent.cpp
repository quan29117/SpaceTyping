/*******************************************************************//*
 * Implementation of the EnemyCollisionComponent class.
 *
 *********************************************************************/

#include <headers/ECS/Collision/EnemyCollisionComponent.hpp>

#include <headers/ApplicationState/PlayState.hpp>

EnemyCollisionComponent::EnemyCollisionComponent(const Vector2D& destSize) {
    m_collision.w = destSize.x;
    m_collision.h = destSize.y;

    m_destroyed = false;
}

EnemyCollisionComponent::~EnemyCollisionComponent() {

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

//Add collision to CollisionManager
    PlayState::getCollisionManager()->addCollision(enemy_collision, this);
}

void EnemyCollisionComponent::onHit(const CollisionID& id) {
    switch(id) {
        case player_collision:
            m_destroyed = true;
            entity->destroy();
            std::cout << "Enemy " << m_destroyed << "\n";
            break;

        case BP_E_collision:
            text->Shot();
            break;
        
        default:
            break;
    }    
}

void EnemyCollisionComponent::onHitP(Entity* enemy) {}