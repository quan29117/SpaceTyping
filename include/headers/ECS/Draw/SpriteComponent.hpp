/*******************************************************************//*
 * Sprite Component for Graphic.
 *
 *********************************************************************/

#pragma once

#include <headers/ApplicationManager/ResourceManager.hpp>
#include <headers/ECS/Draw/TransformComponent.hpp>
#include <headers/Animation.hpp>

class SpriteComponent : public Component {
private:
    TransformComponent* transform;
    SDL_Texture*        m_texture;
    SDL_Rect            m_src;
    SDL_FRect           m_dest;

    bool                m_animated;
    unsigned int m_anim_index = 0, m_frames = 1, m_speed = 1;
    std::map<std::string, Animation> animations;

public:
    SpriteComponent(const TextureID& id, const SDL_Rect& src, const Vector2D& destSize, const bool& animated = false);
    virtual ~SpriteComponent();

    SDL_FRect getRect();
    bool isEndAnimation();

    void init()   override;
    void update() override;
    void render() override;

    void addAnimation(const std::string& name, const unsigned int& i, const unsigned int& f, const unsigned int& s);
    void playAnimation(const std::string& name);
};