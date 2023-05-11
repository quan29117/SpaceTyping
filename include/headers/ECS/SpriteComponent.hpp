/*******************************************************************//*
 * Sprite Component for Graphic.
 *
 *********************************************************************/

#pragma once

#include <headers/ApplicationManager/ResourceManager.hpp>
#include <headers/ECS/TransformComponent.hpp>

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
    virtual ~SpriteComponent();

    SDL_FRect getRect();

    void init()   override;
    void update() override;
    void render() override;
};