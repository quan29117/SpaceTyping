/*******************************************************************//*
 * Implementation of the BulletEnemyCollisionComponent class.
 *
 *********************************************************************/

#include <headers/ECS/Collision/BulletEnemyCollisionComponent.hpp>

#include <headers/ApplicationState/PlayState.hpp>

BulletEnemyCollisionComponent::BulletEnemyCollisionComponent(const Vector2D& destSize) {
    m_collision.w = destSize.x;
    m_collision.h = destSize.y;
}

BulletEnemyCollisionComponent::~BulletEnemyCollisionComponent() {}

int BulletEnemyCollisionComponent::getRemainingSize() {
    return text->remainingSize();
}

void BulletEnemyCollisionComponent::init() {
//Transform reference
    if (entity->hasComponent<TransformComponent>()) {
        transform = &entity->getComponent<TransformComponent>();
        m_collision.x = transform->getPosition().x;
        m_collision.y = transform->getPosition().y;
    }
    else std::cout << "No TransformComponent in BulletEnemy\n";

//Text reference: BulletEnemy
    if (entity->hasComponent<BulletEnemyTextComponent>())
        text = &entity->getComponent<BulletEnemyTextComponent>();
    else std::cout << "No TextComponent in BulletEnemy\n";
}

void BulletEnemyCollisionComponent::onHit(const CollisionID& id) {
    switch (id)
    {
    case player_collision:
        entity->destroy();
        break;
    
    case BP_B_collision:
        text->Shot();
        break;

    default:
        std::cout << "Wrong Collision " << id << " to BulletEnemy\n";
        break;
    }
}

void BulletEnemyCollisionComponent::onHitP(const int& cnt) {}