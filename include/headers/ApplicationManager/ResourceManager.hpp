/*******************************************************************//*
 * Class for archiving and managing resources
 * Including: images, fonts, musics and sounds
 *
 *********************************************************************/

#pragma once

#include <map>
#include <string>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

enum TextureID : short {
    mouse = 0,
    button,
    player,
    enemy,
    bullet_player,
    bullet_enemy,
    menu_bg,
    play_bg,
    pause_bg,
    result_bg1,
    result_bg2,
    game_name,
    pause_title,
    board,
    explosion
};

enum FontID : short {
    yoster = 0,
    pixel_30,
    pixel_80
};

enum MusicID : short {
    none_music = -1,
    menu_bgm = 0,
    play_bgm,
    result_victory_bgm,
    result_defeated_bgm,
};

enum SoundID : short {
    player_shoot = 0,
    enemy_shoot,
    button_hover,
    explosion_sound
};

class ResourceManager {
private:
    std::map <TextureID, SDL_Texture*> textures;
    std::map <FontID, TTF_Font*> fonts;
    std::map <MusicID, Mix_Music*> musics;
    std::map <SoundID, Mix_Chunk*> sounds;

public:
    ResourceManager();
    virtual ~ResourceManager();

    void addTexture(const TextureID& id, const std::string& fileName);
    SDL_Texture* getTexture(const TextureID& id);

    void addFont(const FontID& id, const std::string& fileName, const int& size);
    TTF_Font* getFont(const FontID& id);

    void addMusic(const MusicID& id, const std::string& fileName);
    Mix_Music* getMusic(const MusicID& id);

    void addSound(const SoundID& id, const std::string& fileName);
    Mix_Chunk* getSound(const SoundID& id);

    void clear();
};