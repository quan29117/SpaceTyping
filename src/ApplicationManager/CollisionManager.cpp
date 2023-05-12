/*******************************************************************//*
 * Implementation of the CollisionManager class.
 *
 *********************************************************************/

#include <headers/ApplicationManager/CollisionManager.hpp>

#include <headers/ApplicationState/PlayState.hpp>
#include <headers/ApplicationManager/ExplosionManager.hpp>

#include <headers/Math/Collision.hpp>
#include <headers/ECS/Collision/PlayerCollisionComponent.hpp>
#include <headers/ECS/Collision/EnemyCollisionComponent.hpp>
#include <headers/ECS/Collision/BulletPlayerCollisionComponent.hpp>
#include <headers/ECS/Collision/BulletEnemyCollisionComponent.hpp>

CollisionManager::CollisionManager(Entity* p) {
    player = p;
}

CollisionManager::~CollisionManager() {}

void CollisionManager::update() {
    CollisionPlayer();
    CollisionBulletPlayer();
}

void CollisionManager::CollisionPlayer() {
    for (Entity* E : PlayState::getEntityManager()->getEntitesByGroup(GEnemy)) {
        if (Collision::AABB(player->getComponent<PlayerCollisionComponent>().getHitBox(), 
                                 E->getComponent<EnemyCollisionComponent>().getHitBox())) 
        {
            int char_count = E->getComponent<EnemyCollisionComponent>().getRemainingSize();
            player->getComponent<PlayerCollisionComponent>().onHitP(char_count);
			E->getComponent<EnemyCollisionComponent>().onHit(player_collision);
        }
    }

    for (Entity* BE : PlayState::getEntityManager()->getEntitesByGroup(GBulletEnemy)) {
        if (Collision::AABB(player->getComponent<PlayerCollisionComponent>().getHitBox(), 
                                BE->getComponent<BulletEnemyCollisionComponent>().getHitBox()))
        {
            int char_count = BE->getComponent<BulletEnemyCollisionComponent>().getRemainingSize();
            player->getComponent<PlayerCollisionComponent>().onHitP(char_count);
			BE->getComponent<BulletEnemyCollisionComponent>().onHit(player_collision);
        }
    }
}

void CollisionManager::CollisionBulletPlayer() {
    for (Entity* BP : PlayState::getEntityManager()->getEntitesByGroup(GBulletPlayer_E)) 
        for (Entity* E : PlayState::getEntityManager()->getEntitesByGroup(GEnemy))
            if (Collision::AABB(BP->getComponent<BulletPlayerCollisionComponent>().getHitBox(), 
                                 E->getComponent<EnemyCollisionComponent>().getHitBox()))
            {
                BP->getComponent<BulletPlayerCollisionComponent>().onHit(enemy_collision);
                E->getComponent<EnemyCollisionComponent>().onHit(BP_E_collision);
            }
    
    for (Entity* BP : PlayState::getEntityManager()->getEntitesByGroup(GBulletPlayer_B))
        for (Entity* BE : PlayState::getEntityManager()->getEntitesByGroup(GBulletEnemy))
            if (Collision::AABB(BP->getComponent<BulletPlayerCollisionComponent>().getHitBox(),
                                BE->getComponent<BulletEnemyCollisionComponent>().getHitBox()))
            {
                BP->getComponent<BulletPlayerCollisionComponent>().onHit(BE_collision);
                BE->getComponent<BulletEnemyCollisionComponent>().onHit(BP_B_collision);
            }
}