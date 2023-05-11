/*******************************************************************//*
 * Struct contains static method which check Collision
 *
 *********************************************************************/

#pragma once

#include <SDL2/SDL_rect.h>

struct Collision {
    static bool AABB(const SDL_FRect& rec1, const SDL_FRect& rec2);
};