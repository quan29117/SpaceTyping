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
        fonts[id] = FontManager::loadFont(fileName, size);
    else std::cout << "Font ID: " << id << " has already existed\n";
}

TTF_Font* ResourceManager::getFont(const FontID& id) {
    if (fonts.find(id) == fonts.end()) {
        std::cout << "No font ID: " << id << " existed\n";
        return nullptr;
    }
    else return fonts[id];
}

void ResourceManager::addMusic(const MusicID& id, const std::string& fileName) {
    if (musics.find(id) == musics.end())
        musics[id] = AudioManager::loadMusic(fileName);
    else std::cout << "Music ID: " << id << " has already existed\n";
}

Mix_Music* ResourceManager::getMusic(const MusicID& id) {
    if (musics.find(id) == musics.end()) {
        std::cout << "No music ID: " << id << " existed\n";
        return nullptr;
    }
    else return musics[id];
}

void ResourceManager::addSound(const SoundID& id, const std::string& fileName) {
    if (sounds.find(id) == sounds.end())
        sounds[id] = AudioManager::loadSound(fileName);
    else std::cout << "Sound ID: " << id << " has already existed\n";
}

Mix_Chunk* ResourceManager::getSound(const SoundID& id) {
    if (sounds.find(id) == sounds.end()) {
        std::cout << "No sound ID: " << id << " existed\n";
        return nullptr;
    }
    else return sounds[id];
}

void ResourceManager::clear() {
    for (auto &x : textures) {
        SDL_DestroyTexture(x.second);
        if (x.second == nullptr) std::cout << "nope ";
        x.second = nullptr;
    }
    while (!textures.empty()) {
        // SDL_DestroyTexture(textures.begin()->second);
        // textures.begin()->second = nullptr;
        textures.erase(textures.begin());
    }

    while (!fonts.empty()) {
        TTF_CloseFont(fonts.begin()->second);
        fonts.begin()->second = nullptr;
        fonts.erase(fonts.begin());
    }

    while (!musics.empty()) {
        Mix_FreeMusic(musics.begin()->second);
        musics.begin()->second = nullptr;
        musics.erase(musics.begin());
    }

    while (!sounds.empty()) {
        Mix_FreeChunk(sounds.begin()->second);
        sounds.begin()->second = nullptr;
        sounds.erase(sounds.begin());
    }
}