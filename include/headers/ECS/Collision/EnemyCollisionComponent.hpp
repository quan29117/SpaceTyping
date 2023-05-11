/*******************************************************************//*
 * Component class for Enemy Collision
 * 
 * Include:     EnemyTextComponent reference for game logic
 *              Override method onHit()
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/Collision/CollisionComponent.hpp>
#include <headers/ECS/Text/EnemyTextComponent.hpp>

class EnemyCollisionComponent : public CollisionComponent {
private:
    EnemyTextComponent* text;

public:
    EnemyCollisionComponent(const Vector2D& destSize);
    virtual ~EnemyCollisionComponent();

    void init()                       override;
    void onHit(const CollisionID& id) override;
    void onHitP(Entity* enemy) override;
};