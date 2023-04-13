#pragma once

#include <SDL2/SDL.h>
#include <headers/Structs.hpp>
#include <headers/ECS/TransformComponent.hpp>

class SpriteComponent : public Component {
private:
    TransformComponent* m_trans;
    SDL_Texture* m_texture;
    SDL_FRect m_destRect;

public:
    SpriteComponent(const std::string& fileName, const float& des_w, const float& des_h);
    virtual ~SpriteComponent();

    void init()   override;
    void update() override;
    void render() override;

};