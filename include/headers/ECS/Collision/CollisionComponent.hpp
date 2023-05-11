/*******************************************************************//*
 * Abstract CollisionComponent class
 * 
 * Include:     Hit Box
 *              TransformComponent reference to update Hit Box
 *              Method onHit()
 * 
 * CollisionComponent subclasses must override the pure virtual methods 
 * to satisfy the main game loop
 *
 *********************************************************************/

#pragma once

#include <SDL2/SDL_rect.h>
#include <headers/ECS/TransformComponent.hpp>

enum CollisionID : short {
    player_collision = 0,
    enemy_collision,
    BP_E_collision,                 //BulletPlayer_E
    BP_B_collision,                 //BulletPlayer_B
    BE_collision,                   //BulletEnemy
};

class CollisionComponent : public Component {
protected:
    TransformComponent* transform;
    SDL_FRect m_collision;
    bool m_destroyed;
    
public:
    CollisionComponent();
    virtual ~CollisionComponent();

    SDL_FRect getHitBox();
    bool isDestroyed();

    void init()   override;
    void update() override;
    void render() override;

    void destroy();

    virtual void onHit(const CollisionID& id) = 0;

//This abstract method is only for PlayerCollisionComponent as need to get char_count
    virtual void onHitP(Entity* enemy) = 0;
};