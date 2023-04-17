#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <headers/ECS/TransformComponent.hpp>
#include <headers/ResourceManager.hpp>

class SpriteComponent : public Component {
private:
    TransformComponent* m_trans;
    SDL_Texture* m_texture;
    SDL_FRect m_destRect;

public:
    SpriteComponent(const SpriteID& id, const float& des_w, const float& des_h);
    virtual ~SpriteComponent();

    SDL_FRect getHitBox();

    void init()   override;
    void update() override;
    void render() override;
};