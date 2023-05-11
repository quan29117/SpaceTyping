/*******************************************************************//*
 * Implementation of the BulletPlayerCollisionComponent class.
 *
 *********************************************************************/

#include <headers/ECS/Collision/BulletPlayerCollisionComponent.hpp>

#include <headers/ApplicationState/PlayState.hpp>

BulletPlayerCollisionComponent::BulletPlayerCollisionComponent(const Vector2D& destSize, const CollisionID& id) {
    m_collision.w = destSize.x;
    m_collision.h = destSize.y;

    m_id = id;
}

BulletPlayerCollisionComponent::~BulletPlayerCollisionComponent() {}

void BulletPlayerCollisionComponent::init() {
//Transform reference
    if (entity->hasComponent<TransformComponent>()) {
        transform = &entity->getComponent<TransformComponent>();
        m_collision.x = transform->getPosition().x;
        m_collision.y = transform->getPosition().y;
    }
    else std::cout << "No TransformComponent in BulletPlayer\n";

//Text reference: BulletPlayer
    if (entity->hasComponent<BulletPlayerTextComponent>())
        text = &entity->getComponent<BulletPlayerTextComponent>();
    else std::cout << "No TextComponent in BulletPlayer\n";
}

void BulletPlayerCollisionComponent::onHit(const CollisionID& id) {
    if (id == enemy_collision || id == BE_collision)
        text->Shot();
}

void BulletPlayerCollisionComponent::onHitP(const int& cnt) {}