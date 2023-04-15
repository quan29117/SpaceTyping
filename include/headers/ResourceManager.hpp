#pragma once

#include <map>
#include <string>
#include <headers/Structs.hpp>

enum SpriteID {
    player = 0,
    enemy,
    bullet_player,
    bullet_enemy,
    gameplay_bg,
    main_menu_bg,
};

class ResourceManager {
private:
    // EntityManager* manager;
    std::map <SpriteID, SDL_Texture*> textures;

public:
    ResourceManager() {}
    virtual ~ResourceManager();

    void addTexture (const SpriteID& id, const std::string& fileName);
    SDL_Texture* getTexture(const SpriteID& id);
};