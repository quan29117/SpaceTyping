#pragma once

#include <headers/Game.hpp>

struct TextureManager {
    static SDL_Texture* loadTexture(const std::string& fileName);
    static void render(SDL_Texture* texture, const SDL_FRect* dest);
};

struct Collision {
    static bool AABB(const SDL_FRect& rec1, const SDL_FRect& rec2);
};