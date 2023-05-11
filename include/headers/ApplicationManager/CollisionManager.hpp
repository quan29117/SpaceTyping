/*******************************************************************//*
 * Class for managing the collision detection of all game entities.
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/ECS.hpp>
#include <headers/ECS/Collision/CollisionComponent.hpp>

using CollisionGroup = std::vector <CollisionComponent*>;

class CollisionManager {
private:
    CollisionComponent* player;

//Pointer to EntityGroup
    CollisionGroup enemy_group; //pointer to GEnemy
    CollisionGroup BP_E_group;  //pointer to GBulletPlayer_E
    CollisionGroup BP_B_group;  //pointer to GBulletPlayer_B
    CollisionGroup BE_group;    //pointer to GBulletEnemy
    
public:
    CollisionManager();
    virtual ~CollisionManager();

    void update();
    void refresh(CollisionGroup& group);

    void addCollision(const CollisionID& id, CollisionComponent* component);
    
    void CollisionPlayer(CollisionGroup& group);
    void CollisionBulletPlayer(const CollisionID& id_bullet_player);
    bool checkCollisionBoundingRect(CollisionComponent* checkSrc, CollisionComponent* checkDest);
};