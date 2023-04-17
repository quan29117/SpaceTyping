#pragma once

#include <headers/ECS/TransformComponent.hpp>
#include <headers/ResourceManager.hpp>

class TextComponent : public Component {
private:
    TransformComponent* m_trans;
    std::string m_text;
    FontID id;
    SDL_Texture* m_texture;
    SDL_Rect m_destRect;

public:
    TextComponent(const FontID& id, const std::string& text);
    virtual ~TextComponent();

    void init() override;
    void update() override;
    void render() override;

    void setText();
};
