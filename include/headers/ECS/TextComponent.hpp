#pragma once

#include <headers/ECS/TransformComponent.hpp>
#include <headers/ResourceManager.hpp>

class TextComponent : public Component {
private:
    TransformComponent* m_trans;
    std::string m_text;
    FontID m_id;
    bool m_render;
    SDL_Texture* m_texture;
    SDL_Rect m_destRect;

public:
    TextComponent(const FontID& id, const std::string& text, const bool& render = true);
    virtual ~TextComponent();

    char getFirstChar();

    void init() override;
    void update() override;
    void render() override;

    void setText();
    void eraseFirstChar();
};
