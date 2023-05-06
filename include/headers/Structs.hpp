#pragma once

#include <SDL2/SDL_rect.h>
#include <headers/ResourceManager.hpp>
#include <headers/ECS/ECS.hpp>

struct Collision {
    static bool AABB(Entity& e1, Entity& e2);
};

struct TextureManager {
    static SDL_Texture* loadTexture(const std::string& fileName);
    static void render(SDL_Texture* texture, const SDL_FRect* dest, const SDL_Rect* src = nullptr);
};

struct FontManager {
    static TTF_Font* loadFont(const std::string& fileName, const int& size);
};

struct AudioManager {
    static void setVolume(const int& volume);

    static Mix_Music* loadMusic(const std::string& fileName);
    static void playMusic(const MusicID& musicID);
    static void stopMusic();
    static void loopMusic();
    
    static Mix_Chunk* loadSound(const std::string& fileName);
    static void playSound(const SoundID& soundID);

private:
    static MusicID m_currentMusic;
};