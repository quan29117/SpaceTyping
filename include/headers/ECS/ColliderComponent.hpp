#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <headers/ECS/SpriteComponent.hpp>

class ColliderComponent : public Component {
private:
    SDL_FRect m_collider;
    std::string m_tag;
    TransformComponent* m_trans;

public:
    ColliderComponent(const std::string& tag);
    virtual ~ColliderComponent() {}

    SDL_FRect getCollider();

    void init()   override;
    void update() override;
    void render() override {}
};