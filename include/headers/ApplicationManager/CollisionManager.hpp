/*******************************************************************//*
 * Class for managing the collision detection of all game entities.
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/ECS.hpp>
#include <headers/ECS/Collision/CollisionComponent.hpp>

// using CollisionGroup = std::vector <CollisionComponent*>;
using EGroup = std::vector<Entity*>;

class CollisionManager {
private:
    // CollisionComponent* player;
    Entity* player;

//Pointer to EntityGroup
    // CollisionGroup enemy_group; 
    // CollisionGroup BP_E_group;  
    // CollisionGroup BP_B_group;  
    // CollisionGroup BE_group;    

    EGroup* enemy_group; //reference to GEnemy
    EGroup* BP_E_group;  //reference to GBulletPlayer_E
    EGroup* BP_B_group;  //reference to GBulletPlayer_B
    EGroup* BE_group;    //reference to GBulletEnemy

public:
    CollisionManager(Entity* p);
    virtual ~CollisionManager();

    void update();
    
    void CollisionPlayer();
    void CollisionBulletPlayer();
    
};