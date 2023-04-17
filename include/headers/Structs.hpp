#pragma once

#include <string>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <headers/ECS/ECS.hpp>

struct TextureManager {
    static SDL_Texture* loadTexture(const std::string& fileName);
    static void render(SDL_Texture* texture, const SDL_FRect* dest);
};

struct Collision {
    static bool AABB(const SDL_FRect& rec1, const SDL_FRect& rec2);
    static bool AABB_t(Entity& e1, Entity& e2);
};