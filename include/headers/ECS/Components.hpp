/*******************************************************************//*
 * HeaderFile for including all the Component subclass
 * 
 *********************************************************************/
#pragma once

//Draw
#include <headers/ECS/Draw/TransformComponent.hpp>
#include <headers/ECS/Draw/SpriteComponent.hpp>
#include <headers/ECS/Draw/ExplosionComponent.hpp>
#include <headers/ECS/Draw/DeadAnimationComponent.hpp>

//Text
#include <headers/ECS/Text/EnemyTextComponent.hpp>
#include <headers/ECS/Text/BulletPlayerTextComponent.hpp>
#include <headers/ECS/Text/BulletEnemyTextComponent.hpp>

//Shoot
#include <headers/ECS/Shoot/PlayerShootComponent.hpp>
#include <headers/ECS/Shoot/EnemyShootComponent.hpp>

//Collision
#include <headers/ECS/Collision/PlayerCollisionComponent.hpp>
#include <headers/ECS/Collision/EnemyCollisionComponent.hpp>
#include <headers/ECS/Collision/BulletPlayerCollisionComponent.hpp>
#include <headers/ECS/Collision/BulletEnemyCollisionComponent.hpp>

//Else
#include <headers/ECS/ProgressComponent.hpp>