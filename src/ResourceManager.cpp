#include <headers/ResourceManager.hpp>

ResourceManager::~ResourceManager() {
    for (auto &x : textures)
        SDL_DestroyTexture(x.second);
}

void ResourceManager::addTexture(const SpriteID& id, const std::string& fileName) {
    if (textures.find(id) == textures.end())
        textures[id] = TextureManager::loadTexture(fileName);
    else std::cout << "Texture ID: " << id << " has already existed\n";
}

SDL_Texture* ResourceManager::getTexture(const SpriteID& id) {
    if (textures.find(id) == textures.end()) {
        std::cout << "No texture ID: " << id << " existed\n";
        return nullptr;
    }
    else return textures[id];
}