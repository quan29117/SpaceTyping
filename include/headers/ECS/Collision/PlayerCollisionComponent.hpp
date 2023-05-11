/*******************************************************************//*
 * Component class for Player Collision
 * 
 * Include:     ProgressComponent reference for score - wrong count
 *              Override method onHit()
 *
 *********************************************************************/

#pragma once 

#include <headers/ECS/Collision/CollisionComponent.hpp>
#include <headers/ECS/ProgressComponent.hpp>

class PlayerCollisionComponent : public CollisionComponent {
private:
    ProgressComponent* progress;

public:
    PlayerCollisionComponent(const Vector2D& destSize);
    virtual ~PlayerCollisionComponent();

    void init()   override;
    void onHit(const CollisionID& id)  override;
    
    void onHitP(Entity* enemy) override;
};