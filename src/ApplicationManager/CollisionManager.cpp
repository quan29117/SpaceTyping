/*******************************************************************//*
 * Implementation of the CollisionManager class.
 *
 *********************************************************************/

#include <headers/ApplicationManager/CollisionManager.hpp>

#include <headers/Math/Collision.hpp>
//Collision
//Text
#include <headers/ECS/ProgressComponent.hpp>

CollisionManager::CollisionManager() {
    player = nullptr;
}

CollisionManager::~CollisionManager() {

}

void CollisionManager::update() {
    CollisionPlayer(enemy_group);
    // CollisionPlayer(BE_group);
    // CollisionBulletPlayer(BP_E_collision);
    // CollisionBulletPlayer(BP_E_collision);

    refresh(enemy_group);
}

void CollisionManager::refresh(CollisionGroup& group) {
    group.erase(std::remove_if(group.begin(), group.end(),
        [](CollisionComponent* component)
    {
        return component->isDestroyed();
    }),
        group.end());
}

void CollisionManager::addCollision(const CollisionID& id, CollisionComponent* component) {
    switch (id) {
        case player_collision:
            if (player == nullptr)
                player = component;
            else std::cout << "PlayerCollisionComponent has been existed in CollisionManager\n";
            break;

        case enemy_collision:
            enemy_group.push_back(component);
            break;

        case BP_E_collision:
            BP_E_group.push_back(component);
            break;

        case BP_B_collision:
            BP_B_group.push_back(component);
            break;

        case BE_collision:
            BE_group.push_back(component);
            break;
    }
}

void CollisionManager::CollisionPlayer(CollisionGroup& group) {
    for (CollisionComponent* e : group) {
        if (checkCollisionBoundingRect(player, e)) {
            player->onHitP(e->entity);
			e->onHit(player_collision);
        }
    }
}

void CollisionManager::CollisionBulletPlayer(const CollisionID& id_enemy) {
    CollisionGroup groupSrc, groupDest;
    CollisionID id_bullet_player;

    switch (id_enemy) {
        case enemy_collision:
            groupSrc  = BP_E_group;
            groupDest = enemy_group;
            id_bullet_player = BP_E_collision;
            break;
        
        case BE_collision:
            groupSrc  = BP_B_group;
            groupDest = BE_group;
            id_bullet_player = BP_B_collision;
            break;
        
        default:
            break;
    }

    for (CollisionComponent* eSrc : groupSrc) 
        for (CollisionComponent* eDest : groupDest)
            if (checkCollisionBoundingRect(eSrc, eDest)) {
                eSrc->onHit(id_enemy);
                eDest->onHit(id_bullet_player);
            }
}

bool CollisionManager::checkCollisionBoundingRect(CollisionComponent* checkSrc, CollisionComponent* checkDest) {
    SDL_FRect srcRect = checkSrc->getHitBox();
    SDL_FRect destRect = checkDest->getHitBox();

    if (Collision::AABB(srcRect, destRect))
        return true;
    return false;
}