#include <headers/ResourceManager.hpp>

#include <iostream>
#include <headers/Structs.hpp>
#include <headers/Global.hpp>


void ResourceManager::addTexture(const TextureID& id, const std::string& fileName) {
    if (textures.find(id) == textures.end())
        textures[id] = TextureManager::loadTexture(fileName);
    else std::cout << "Texture ID: " << id << " has already existed\n";
}

SDL_Texture* ResourceManager::getTexture(const TextureID& id) {
    if (textures.find(id) == textures.end()) {
        std::cout << "No texture ID: " << id << " existed\n";
        return nullptr;
    }
    else return textures[id];
}

void ResourceManager::addFont(const FontID& id, const std::string& fileName, const int& size) {
    if (fonts.find(id) == fonts.end())
        fonts[id] = TTF_OpenFont((PATH_BEGIN_FONT + fileName).c_str(), size);
    else std::cout << "Font ID: " << id << " has already existed\n";
}

TTF_Font* ResourceManager::getFont(const FontID& id) {
    if (fonts.find(id) == fonts.end()) {
        std::cout << "No font ID: " << id << " existed\n";
        return nullptr;
    }
    else return fonts[id];
}

void ResourceManager::clear() {
    for (auto &x : textures) {
        SDL_DestroyTexture(x.second);
        x.second = nullptr;
    }
    while (!textures.empty()) textures.erase(textures.begin());

    for (auto& x : fonts) {
        TTF_CloseFont(x.second);
        x.second = nullptr;
    }
    while (!fonts.empty()) fonts.erase(fonts.begin());
}