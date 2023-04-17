#pragma once

#include <map>
#include <string>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

enum SpriteID {
    player = 0,
    enemy,
    bullet_player,
    bullet_enemy,
    gameplay_bg,
    main_menu_bg,
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