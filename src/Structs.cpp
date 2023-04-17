#include <headers/Structs.hpp>

#include <headers/Game.hpp>
#include <headers/Global.hpp>
#include <headers/ECS/SpriteComponent.hpp>

//---------------------------------TextureManager---------------------------------
SDL_Texture* TextureManager::loadTexture(const std::string& fileName) {
    SDL_Surface* img = IMG_Load((PATH_BEGIN_IMAGE + fileName).c_str());
    if (img == nullptr)
        std::cout << "Unable to load file " << fileName << std::endl;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getRenderer(), img);
    if (texture == nullptr)
        std::cout << "Unable to create texture " << fileName << std::endl;
    
    SDL_FreeSurface(img);

    return texture;
}

void TextureManager::render(SDL_Texture* texture, const SDL_FRect* dest) {
    SDL_RenderCopyF(Game::getRenderer(), texture, nullptr, dest);
}

//-----------------------------------Collision------------------------------------
bool Collision::AABB(const SDL_FRect& rec1, const SDL_FRect& rec2) {
    if (
        rec1.x + rec1.w >= rec2.x &&
        rec2.x + rec2.w >= rec1.x &&
        rec1.y + rec1.h >= rec2.y &&
        rec2.y + rec2.h >= rec1.y
    )   return true;
    
    return false;
}

bool Collision::AABB_t(Entity& e1, Entity& e2) {
    if (e1.isAlive() && e2.isAlive()) {
        SDL_FRect rec1 = e1.getComponent<SpriteComponent>().getHitBox(), rec2 = e2.getComponent<SpriteComponent>().getHitBox();
        if (
            rec1.x + rec1.w >= rec2.x &&
            rec2.x + rec2.w >= rec1.x &&
            rec1.y + rec1.h >= rec2.y &&
            rec2.y + rec2.h >= rec1.y
        )   return true;
    }
    
    return false;
}
