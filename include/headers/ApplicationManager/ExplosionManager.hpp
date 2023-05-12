/*******************************************************************//*
 * Struct for managing the explosion animation when enemy dead.
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/ECS.hpp>
#include <headers/Math/Vector2D.hpp>

struct ExplosionManager {
    static Entity& createExplosion(const Vector2D& pos);
};