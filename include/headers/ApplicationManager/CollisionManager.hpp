/*******************************************************************//*
 * Class for managing the collision detection of all game entities.
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/ECS.hpp>
#include <headers/ECS/Collision/CollisionComponent.hpp>

using EGroup = std::vector<Entity*>;

class CollisionManager {
private:
    Entity* player;

public:
    CollisionManager(Entity* p);
    virtual ~CollisionManager();

    void update();
    
    void CollisionPlayer();
    void CollisionBulletPlayer();
    
};