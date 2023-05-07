#include <headers/Structs.hpp>

#include <SDL2/SDL_image.h>
#include <headers/Global.hpp>
#include <headers/Application.hpp>

#include <headers/ECS/SpriteComponent.hpp>

//---------------------------------------Collision----------------------------------------
bool Collision::AABB(Entity& e1, Entity& e2) {
    if (e1.isAlive() && e2.isAlive()) {
        SDL_FRect rec1 = e1.getComponent<SpriteComponent>().getHitBox(),
                  rec2 = e2.getComponent<SpriteComponent>().getHitBox();
                  
        if (
            rec1.x + rec1.w >= rec2.x &&
            rec2.x + rec2.w >= rec1.x &&
            rec1.y + rec1.h >= rec2.y &&
            rec2.y + rec2.h >= rec1.y
        )   return true;
    }
    
    return false;
}

//-------------------------------------TextureManager-------------------------------------
SDL_Texture* TextureManager::loadTexture(const std::string& fileName) {
    SDL_Surface* img = IMG_Load((PATH_BEGIN_IMAGE + fileName).c_str());
    if (img == nullptr)
        std::cout << "Unable to load file " << fileName << '\n';

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Application::getRenderer(), img);
    if (texture == nullptr)
        std::cout << "Unable to create texture " << fileName << '\n';
    
    SDL_FreeSurface(img);

    return texture;
}

void TextureManager::render(SDL_Texture* texture, const SDL_Rect* src, const SDL_FRect* dest) {
    SDL_RenderCopyF(Application::getRenderer(), texture, src, dest);
}

//--------------------------------------FontManager---------------------------------------
TTF_Font* FontManager::loadFont(const std::string& fileName, const int& size) {
    TTF_Font* font = TTF_OpenFont((PATH_BEGIN_FONT + fileName).c_str(), size);
    if (font == nullptr)
        std::cout << "Unable to load file " << fileName << '\n';

    return font;
}

//--------------------------------------AudioManager--------------------------------------
MusicID AudioManager::m_currentMusic = none_music;

void AudioManager::setVolume(const int& volume) {
    Mix_VolumeMusic(volume);
}

Mix_Music* AudioManager::loadMusic(const std::string& fileName) {
    Mix_Music* music = Mix_LoadMUS((PATH_BEGIN_AUDIO + fileName).c_str());
    if (music == nullptr)
        std::cout << "Unable to load file " << fileName << '\n';

    return music;
}

void AudioManager::playMusic(const MusicID& musicID) {
    stopMusic();
    m_currentMusic = musicID;
    Mix_PlayMusic(Application::getResourceManager()->getMusic(musicID), 0);
}

void AudioManager::stopMusic() {
    if (Mix_PlayingMusic() != 0)
        Mix_HaltMusic();
    m_currentMusic = none_music;
}

void AudioManager::loopMusic() {
    if (Mix_PlayingMusic() == 0 && m_currentMusic != none_music)
        playMusic(m_currentMusic);
}

Mix_Chunk* AudioManager::loadSound(const std::string& fileName) {
    Mix_Chunk* sound = Mix_LoadWAV((PATH_BEGIN_AUDIO + fileName).c_str());
    if (sound == nullptr)
        std::cout << "Unable to load file " << fileName << '\n';

    return sound;
}

void AudioManager::playSound(const SoundID& soundID) {
    Mix_PlayChannel(-1, Application::getResourceManager()->getSound(soundID), 0);
}

    