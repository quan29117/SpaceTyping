#pragma once

#include <map>
#include <string>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

enum SpriteID {
    mouse = 0,
    button,
    player,
    enemy,
    bullet_player,
    bullet_enemy,
    play_bg,
    menu_bg,
    pause_bg,
};

enum FontID {
    yoster = 0,
    mariana,
};

class ResourceManager {
private:
    // EntityManager* manager;
    std::map <SpriteID, SDL_Texture*> textures;
    std::map <FontID, TTF_Font*> fonts;

public:
    ResourceManager() {}
    virtual ~ResourceManager() {}

    void addTexture(const SpriteID& id, const std::string& fileName);
    SDL_Texture* getTexture(const SpriteID& id);

    void addFont(const FontID& id, const std::string& fileName, const int& size);
    TTF_Font* getFont(const FontID& id);

    void clear();
};