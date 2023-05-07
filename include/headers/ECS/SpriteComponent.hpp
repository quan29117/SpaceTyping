#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <headers/ECS/TransformComponent.hpp>
#include <headers/ResourceManager.hpp>

class SpriteComponent : public Component {
private:
    TransformComponent* transform;
    SDL_Texture*        m_texture;
    SDL_Rect            m_src;
    SDL_FRect           m_dest;

    bool                m_animated;
    short               m_animation_speed;

public:
    SpriteComponent(const TextureID& id, const SDL_Rect& src, const Vector2D& destSize, const bool& animated = false);
    virtual ~SpriteComponent() {}

    SDL_FRect getHitBox();

    void init()   override;
    void update() override;
    void render() override;
};