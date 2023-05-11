/*******************************************************************//*
 * Component class for BulletPlayer Collision
 * 
 * Include:     TextComponent reference for game logic
 *              Override method onHit()
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/Collision/CollisionComponent.hpp>
#include <headers/ECS/Text/BulletPlayerTextComponent.hpp>

class BulletPlayerCollisionComponent : public CollisionComponent {
private:
    BulletPlayerTextComponent* text;
    CollisionID m_id;

public:
    BulletPlayerCollisionComponent(const Vector2D& destSize, const CollisionID& id);
    virtual ~BulletPlayerCollisionComponent();

    void init()                       override;
    void onHit(const CollisionID& id) override;
    
    void onHitP(Entity* enemy) override;
};