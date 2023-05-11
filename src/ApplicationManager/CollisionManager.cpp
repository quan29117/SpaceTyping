/*******************************************************************//*
 * Implementation of the CollisionManager class.
 *
 *********************************************************************/

#include <headers/ApplicationManager/CollisionManager.hpp>

#include <headers/Math/Collision.hpp>
#include <headers/ECS/Collision/PlayerCollisionComponent.hpp>
#include <headers/ECS/Collision/EnemyCollisionComponent.hpp>
#include <headers/ECS/Collision/BulletPlayerCollisionComponent.hpp>
#include <headers/ECS/Collision/BulletEnemyCollisionComponent.hpp>
#include <headers/ECS/ProgressComponent.hpp>

CollisionManager::CollisionManager(Entity* p) {
    player = p;

    enemy_group = &p->getManager().getEntitesByGroup(GEnemy);
    BP_E_group  = &p->getManager().getEntitesByGroup(GBulletPlayer_E);
    BP_B_group  = &p->getManager().getEntitesByGroup(GBulletPlayer_B);
    BE_group    = &p->getManager().getEntitesByGroup(GBulletEnemy);
}

CollisionManager::~CollisionManager() {}

void CollisionManager::update() {
    CollisionPlayer();
    CollisionBulletPlayer();
}

void CollisionManager::CollisionPlayer() {
    for (Entity* e : *enemy_group) {
        if (Collision::AABB(player->getComponent<PlayerCollisionComponent>().getHitBox(), 
                            e->getComponent<EnemyCollisionComponent>().getHitBox())) 
        {
            player->getComponent<PlayerCollisionComponent>().onHitP(e);
			e->getComponent<EnemyCollisionComponent>().onHit(player_collision);
        }
    }
}

void CollisionManager::CollisionBulletPlayer() {
    for (Entity* eSrc : *BP_E_group) 
        for (Entity* eDest : *enemy_group)
            if (Collision::AABB(eSrc->getComponent<BulletPlayerCollisionComponent>().getHitBox(), 
                                eDest->getComponent<EnemyCollisionComponent>().getHitBox()))
            {
                eSrc->getComponent<BulletPlayerCollisionComponent>().onHit(enemy_collision);
                eDest->getComponent<EnemyCollisionComponent>().onHit(BP_E_collision);
            }
    
    for (Entity* eSrc : *BP_B_group) 
        for (Entity* eDest : *BE_group)
            if (Collision::AABB(eSrc->getComponent<BulletPlayerCollisionComponent>().getHitBox(),
                                eDest->getComponent<BulletEnemyCollisionComponent>().getHitBox()))
            {
                // eSrc->getComponent<BulletPlayerCollisionComponent>().onHit(BE_collision);
                // eDest->getComponent<BulletEnemyCollisionComponent>().onHit(BP_B_collision);
            }
}