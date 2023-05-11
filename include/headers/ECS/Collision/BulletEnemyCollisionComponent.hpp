/*******************************************************************//*
 * Component class for BulletEnemy Collision
 * 
 * Include:     TextComponent reference for game logic
 *              Override method onHit()
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/Collision/CollisionComponent.hpp>
#include <headers/ECS/Text/BulletEnemyTextComponent.hpp>

class BulletEnemyCollisionComponent : public CollisionComponent {
private:
    BulletEnemyTextComponent* text;

public:
    BulletEnemyCollisionComponent(const Vector2D& destSize);
    virtual ~BulletEnemyCollisionComponent();

    int getRemainingSize();

    void init()                       override;
    void onHit(const CollisionID& id) override;

    void onHitP(const int& cnt) override;
};